
#include "../include/encode.h"
#include "../include/chaotic_systems.h"
#include "../include/helper.h"
#include "../include/img_processing.h"

#include <algorithm>
#include <cassert>

namespace cieucs {
namespace encode {

static key::Key G_KEY;
static bool G_KEY_SET = false;
static bool G_SCRAMBLED = false;

void setKey() {
  G_KEY = key::Key();
  G_KEY.genRandomKey();
  G_KEY.readKey("key.key");
  G_KEY_SET = true;
}

void setKey(const key::Key &key) {
  G_KEY = key;
  G_KEY_SET = true;
}

void setKey(const char *i_keyPath) {
  G_KEY = key::Key();
  G_KEY.readKey(i_keyPath);
  G_KEY_SET = true;
}

key::Key getKey() { return G_KEY; }

void scramble(const img_processing::Data &i_data_red,
              const img_processing::Data &i_data_green,
              const img_processing::Data &i_data_blue,
              img_processing::Data &o_data_red,
              img_processing::Data &o_data_green,
              img_processing::Data &o_data_blue, const size_t &i_width,
              const size_t &i_height) {
  assert(G_KEY_SET);

  const size_t &size = i_width * i_height;

  o_data_red.reserve(i_data_red.size());
  o_data_green.reserve(i_data_green.size());
  o_data_blue.reserve(i_data_blue.size());

  // step 2 gen lorenz and equalize it
  chaotic::DoubleVec x, y, z;
  chaotic::genLorenz(x, y, z, size, G_KEY);

  chaotic::Vec x_eq, y_eq, z_eq;
  chaotic::equalizeLorenz(x, y, z, x_eq, y_eq, z_eq, i_width, i_height, size);

  // step 3 sort indexes
  std::vector<size_t> x_eq_indexes, y_eq_indexes, z_eq_indexes;
  helper::sort_indexes(x_eq, x_eq_indexes);
  helper::sort_indexes(y_eq, y_eq_indexes);
  helper::sort_indexes(z_eq, z_eq_indexes);

  // step 4 scamble
  for (size_t i = 0; i < size; ++i) {
    o_data_red.push_back(i_data_red[x_eq_indexes[i]]);
    o_data_green.push_back(i_data_green[y_eq_indexes[i]]);
    o_data_blue.push_back(i_data_blue[z_eq_indexes[i]]);
  }
  img_processing::writeImage("img_scramble.jpg", o_data_red, o_data_green,
                             o_data_blue, i_width, i_height);

  G_SCRAMBLED = true;
}

void encode(const img_processing::Data &i_data_red,
            const img_processing::Data &i_data_green,
            const img_processing::Data &i_data_blue,
            img_processing::Data &o_data_red,
            img_processing::Data &o_data_green,
            img_processing::Data &o_data_blue, const size_t &i_width,
            const size_t &i_height) {
  assert(G_KEY_SET && G_SCRAMBLED);

  const size_t size = i_width * i_height;

  // gen chaotic key
  chaotic::DoubleVec x, y, z;
  chaotic::genRossler(x, y, z, size, G_KEY);

  chaotic::UcharVec x_restricted, y_restricted, z_restricted;
  chaotic::restrictRossler(x, y, z, x_restricted, y_restricted, z_restricted);

  chaotic::UcharVec chaoticKey;
  chaotic::generateChaoticKey(x_restricted, y_restricted, z_restricted,
                              chaoticKey);

  assert(chaoticKey.size() != 0);

  o_data_red.reserve(size);
  o_data_green.reserve(size);
  o_data_blue.reserve(size);

  for (size_t i = 0; i < size; ++i) {
    o_data_blue[i] = i_data_blue[i] ^ chaoticKey[i];
    o_data_green[i] = i_data_green[i] ^ chaoticKey[i];
    o_data_red[i] = i_data_red[i] ^ chaoticKey[i];
  }
  img_processing::writeImage("img_encode.jpg", o_data_red, o_data_green,
                             o_data_blue, i_width, i_height);

  resetState();
}

void resetState() {
  G_SCRAMBLED = false;
  // G_KEY_SET = false;
  // G_KEY = {};
}

} // namespace encode
} // namespace cieucs