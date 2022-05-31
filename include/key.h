#pragma once

namespace cieucs {
namespace key {

struct Key {
  // Lorenz attractor parameters
  struct Lorenz {
    float a = 10.f;
    float b = 28.f;
    float c = 8.f / 3.f;
    double x0 = 1.1f;
    double y0 = 1.3f;
    double z0 = 1.5f;
  } lorenz;

  // Rossler attractor parameters
  struct Rossler {
    float a = 0.1f;
    float b = 0.1f;
    float c = 14.f;
    double x0 = 1.f;
    double y0 = 1.f;
    double z0 = 1.f;
  } rossler;

  void genRandomKey();
  void writeKey(const char *o_keyPath);
  void readKey(const char *i_keyPath);
};

} // namespace key
} // namespace cieucs