#pragma once
#include <mp++/mp++.hpp>

namespace cieucs {
namespace key {

using real = mppp::real;
using namespace mppp::literals;
struct Key {
  // Lorenz attractor parameters
  struct Lorenz {
    real alpha = real{"10", 512};
    real rho = real{"28", 512};
    real beta = real{8 / 3_q1, 512};
    real x0 = real{"1.1", 512};
    real y0 = real{"1.3", 512};
    real z0 = real{"1.5", 512};
  } lorenz;

  // Rossler attractor parameters
  struct Rossler {
    real alpha = real{"0.2", 512};
    real beta = real{"0.2", 512};
    real gamma = real{"5.7", 512};
    real x0 = real{"1.0", 512};
    real y0 = real{"1.0", 512};
    real z0 = real{"1.0", 512};
  } rossler;

  void genRandomKey();
  void writeKey(const char *o_keyPath);
  void readKey(const char *i_keyPath);
};

} // namespace key
} // namespace cieucs