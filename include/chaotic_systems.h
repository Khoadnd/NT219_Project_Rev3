#pragma once
#include "key.h"
#include <mp++/mp++.hpp>
#include <vector>

namespace cieucs {
namespace chaotic {
using real = mppp::real;

using RealVec = std::vector<real>;
// using int_t = mppp::integer<1>;
// using Vec = std::vector<long long>;
using Vec = std::vector<real>;
using UcharVec = std::vector<unsigned char>;

// using UcharVec = std::vector<unsigned char>;

void genLorenz(RealVec &o_x, RealVec &o_y, RealVec &o_z,
               const size_t &i_size = 256 * 256,
               const key::Key &i_key = key::Key());

void equalizeLorenz(const RealVec &i_x, const RealVec &i_y, const RealVec &i_z,
                    Vec &o_x, Vec &o_y, Vec &o_z, const size_t &i_width = 256,
                    const size_t &i_height = 256,
                    const size_t &i_size = 256 * 256);

void genRossler(RealVec &o_x, RealVec &o_y, RealVec &o_z,
                const size_t &i_size = 256 * 256,
                const key::Key &i_key = key::Key());

void restrictRossler(const RealVec &i_x, const RealVec &i_y, const RealVec &i_z,
                     UcharVec &o_x, UcharVec &o_y, UcharVec &o_z);

void generateChaoticKey(const UcharVec &i_x, const UcharVec &i_y,
                        const UcharVec &i_z, UcharVec &o_key);

} // namespace chaotic
} // namespace cieucs
