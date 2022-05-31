#include "../include/chaotic_systems.h"

#include <cassert>
#include <cmath>

namespace cieucs {
namespace chaotic {

static constexpr size_t G_P1 = 150000;
static constexpr size_t G_P2 = 150000;
static constexpr size_t G_P3 = 150000;

void genLorenz(DoubleVec &o_x, DoubleVec &o_y, DoubleVec &o_z,
               const size_t &i_size, const key::Key &i_key) {
  double x = i_key.lorenz.x0;
  double y = i_key.lorenz.y0;
  double z = i_key.lorenz.z0;
  double dx = 0;
  double dy = 0;
  double dz = 0;

  o_x.reserve(i_size);
  o_y.reserve(i_size);
  o_z.reserve(i_size);

  o_x.push_back(x);
  o_y.push_back(y);
  o_z.push_back(z);

  float dt = 0.01f;

  for (size_t i = 1; i < i_size; ++i) {
    dx = x + dt * (i_key.lorenz.a * (y - x));
    dy = y + dt * ((i_key.lorenz.b - z) * x - y);
    dz = z + dt * (x * y - i_key.lorenz.c * z);

    x = dx;
    y = dy;
    z = dz;

    o_x.push_back(x);
    o_y.push_back(y);
    o_z.push_back(z);
  }
}

void equalizeLorenz(const DoubleVec &i_x, const DoubleVec &i_y,
                    const DoubleVec &i_z, Vec &o_x, Vec &o_y, Vec &o_z,
                    const size_t &i_width, const size_t &i_height,
                    const size_t &i_size) {
  o_x.reserve(i_size);
  o_y.reserve(i_size);
  o_z.reserve(i_size);

  for (int i = 0; i < i_size; ++i) {
    o_x.push_back(static_cast<long long>(ceil(i_x[i] * G_P1)) % i_width);
    o_y.push_back(static_cast<long long>(ceil(i_y[i] * G_P2)) % i_height);
    o_z.push_back(static_cast<long long>(ceil(i_z[i] * G_P3)) % 256);
  }
}

void genRossler(DoubleVec &o_x, DoubleVec &o_y, DoubleVec &o_z,
                const size_t &i_size, const key::Key &i_key) {
  double x = i_key.rossler.x0;
  double y = i_key.rossler.y0;
  double z = i_key.rossler.z0;
  double dx = 0;
  double dy = 0;
  double dz = 0;

  o_x.reserve(i_size);
  o_y.reserve(i_size);
  o_z.reserve(i_size);

  o_x.push_back(x);
  o_y.push_back(y);
  o_z.push_back(z);

  float dt = 0.01f;

  for (size_t i = 1; i < i_size; ++i) {
    dx = x + dt * (-(y + z));
    dy = y + dt * (x + i_key.rossler.a * y);
    dz = z + dt * (i_key.rossler.b + z * (x - i_key.rossler.c));

    x = dx;
    y = dy;
    z = dz;

    o_x.push_back(x);
    o_y.push_back(y);
    o_z.push_back(z);
  }
}

void restrictRossler(const DoubleVec &i_x, const DoubleVec &i_y,
                     const DoubleVec &i_z, UcharVec &o_x, UcharVec &o_y,
                     UcharVec &o_z) {
  o_x.reserve(i_x.size());
  o_y.reserve(i_y.size());
  o_z.reserve(i_z.size());

  for (size_t i = 0; i < i_x.size(); ++i) {
    o_x.push_back(static_cast<unsigned char>(
        (static_cast<long long>(i_x[i] * 10e15)) % 256));
    o_y.push_back(static_cast<unsigned char>(
        (static_cast<long long>(i_y[i] * 10e15)) % 256));
    o_z.push_back(static_cast<unsigned char>(
        (static_cast<long long>(i_z[i] * 10e15)) % 256));
  }
}

void generateChaoticKey(const UcharVec &i_x, const UcharVec &i_y,
                        const UcharVec &i_z, UcharVec &o_key) {
  o_key.reserve(i_x.size());

  for (size_t i = 0; i < i_x.size(); ++i)
    o_key.push_back(i_x[i] ^ i_y[i] ^ i_z[i]);
}

} // namespace chaotic
} // namespace cieucs