#pragma once

namespace cieucs {
namespace key {
struct Key {
  // Lorenz attractor parameters
  struct Lorenz {
    float a = 10.f;
    float b = 28.f;
    float c = 8.f / 3.f;
    float x0 = 1.1f;
    float y0 = 1.3f;
    float z0 = 1.5f;
  } lorenz;

  // Rossler attractor parameters
  struct Rossler {
    float a = 0.2f;
    float b = 0.2f;
    float c = 5.7f;
    float x0 = 1.f;
    float y0 = 1.f;
    float z0 = 1.f;
  } rossler;

  void genRandomKey();
  void writeKey(const char *&o_key_path);
  void readKey(const char *&i_key_path);
};

} // namespace key
} // namespace cieucs