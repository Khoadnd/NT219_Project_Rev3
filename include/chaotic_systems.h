#pragma once
#include "key.h"
#include <vector>

namespace cieucs {
namespace chaotic {

using DoubleVec = std::vector<double>;
using Vec = std::vector<long long>;
using UcharVec = std::vector<unsigned char>;

void genLorenz(DoubleVec &o_x, DoubleVec &o_y, DoubleVec &o_z,
               const size_t &i_size = 256 * 256,
               const key::Key &i_key = key::Key());

void equalizeLorenz(const DoubleVec &i_x, const DoubleVec &i_y,
                    const DoubleVec &i_z, Vec &o_x, Vec &o_y, Vec &o_z,
                    const size_t &i_width = 256, const size_t &i_height = 256,
                    const size_t &i_size = 256 * 256);

void genRossler(DoubleVec &o_x, DoubleVec &o_y, DoubleVec &o_z,
                const size_t &i_size = 256 * 256,
                const key::Key &i_key = key::Key());

void restrictRossler(const DoubleVec &i_x, const DoubleVec &i_y,
                     const DoubleVec &i_z, UcharVec &o_x, UcharVec &o_y,
                     UcharVec &o_z);

void generateChaoticKey(const UcharVec &i_x, const UcharVec &i_y,
                        const UcharVec &i_z, UcharVec &o_key);

} // namespace chaotic
} // namespace cieucs
