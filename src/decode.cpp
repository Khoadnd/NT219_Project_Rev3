
#include "../include/decode.h"
#include "../include/chaotic_systems.h"
#include "../include/helper.h"
#include "../include/img_processing.h"

#include <algorithm>
#include <cassert>

namespace cieucs {
namespace decode {

static key::Key G_KEY;
static bool G_KEY_SET = false;
static bool G_DECODED = false;

void setKey() {
  G_KEY = key::Key();
  G_KEY_SET = true;
}

void unscramble(const img_processing::Data &i_data_red,
                const img_processing::Data &i_data_green,
                const img_processing::Data &i_data_blue,
                img_processing::Data &o_data_red,
                img_processing::Data &o_data_green,
                img_processing::Data &o_data_blue, const size_t &i_width,
                const size_t &i_height) {
  assert(G_KEY_SET && G_DECODED);

  const size_t &size = i_width * i_height;

  o_data_red.resize(i_data_red.size());
  o_data_green.resize(i_data_green.size());
  o_data_blue.resize(i_data_blue.size());

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

  for (size_t i = 0; i < size; ++i) {
    assert(i < size);
    assert(x_eq_indexes[i] < size);
    assert(y_eq_indexes[i] < size);
    assert(z_eq_indexes[i] < size);
    o_data_red[x_eq_indexes[i]] = i_data_red[i];
    o_data_green[y_eq_indexes[i]] = i_data_green[i];
    o_data_blue[z_eq_indexes[i]] = i_data_blue[i];
  }

  img_processing::writeImage("img_unscramble.jpg", o_data_red, o_data_green,
                             o_data_blue, i_width, i_height);

  resetState();
}

void decode(const img_processing::Data &i_data_red,
            const img_processing::Data &i_data_green,
            const img_processing::Data &i_data_blue,
            img_processing::Data &o_data_red,
            img_processing::Data &o_data_green,
            img_processing::Data &o_data_blue, const size_t &i_width,
            const size_t &i_height) {
  assert(G_KEY_SET);

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

  img_processing::writeImage("img_decode.jpg", o_data_red, o_data_green,
                             o_data_blue, i_width, i_height);

  G_DECODED = true;
}

void resetState() {
  G_DECODED = false;
  G_KEY_SET = false;
  G_KEY = {};
}

} // namespace decode
} // namespace cieucs