#include "../include/key.h"

#include <cryptopp/filters.h>
#include <fstream>
#include <random>
#include <sstream>
#include <stdexcept>

#include <cryptopp/base64.h>

namespace cieucs {
namespace key {

void Key::genRandomKey() {

  double upperBound = 10.f;
  double lowerBound = -10.f;

  std::uniform_real_distribution<double> unif(lowerBound, upperBound);
  std::default_random_engine re(time(nullptr));

  lorenz.x0 = unif(re);
  lorenz.y0 = unif(re);
  lorenz.z0 = unif(re);

  rossler.x0 = unif(re);
  rossler.y0 = unif(re);
  rossler.z0 = unif(re);

  writeKey("key.key");
}

void Key::writeKey(const char *o_keyPath) {

  std::ofstream key_file(o_keyPath);

  std::stringstream ss;

  ss << "Lorenz attractor parameters:" << std::endl;
  ss << "a = " << lorenz.a << std::endl;
  ss << "b = " << lorenz.b << std::endl;
  ss << "c = " << lorenz.c << std::endl;
  ss << "x0 = " << lorenz.x0 << std::endl;
  ss << "y0 = " << lorenz.y0 << std::endl;
  ss << "z0 = " << lorenz.z0 << std::endl;

  ss << std::endl;

  ss << "Rossler attractor parameters:" << std::endl;
  ss << "a = " << rossler.a << std::endl;
  ss << "b = " << rossler.b << std::endl;
  ss << "c = " << rossler.c << std::endl;
  ss << "x0 = " << rossler.x0 << std::endl;
  ss << "y0 = " << rossler.y0 << std::endl;
  ss << "z0 = " << rossler.z0 << std::endl;

  std::string data;
  CryptoPP::StringSource source(
      ss.str(), true,
      new CryptoPP::Base64Encoder(new CryptoPP::StringSink(data)));

  key_file << data;

  key_file.close();
}

void Key::readKey(const char *i_keyPath) {

  std::ifstream key_file(i_keyPath);

  if (!key_file.is_open())
    throw new std::runtime_error("Error: cannot open key file");

  std::string line = "", buf = "";
  std::string data = "";

  while (std::getline(key_file, line)) {
    CryptoPP::StringSource source(
        line, true, new CryptoPP::Base64Decoder(new CryptoPP::StringSink(buf)));
    data += buf;
    line.clear();
    buf.clear();
  }

  key_file.close();

  std::stringstream ss(data);
  while (std::getline(ss, line)) {

    if (line.find("Lorenz attractor parameters:") != std::string::npos) {

      std::getline(ss, line);
      lorenz.a = std::stof(line.substr(line.find("a = ") + 4));

      std::getline(ss, line);
      lorenz.b = std::stof(line.substr(line.find("b = ") + 4));

      std::getline(ss, line);
      lorenz.c = std::stof(line.substr(line.find("c = ") + 4));

      std::getline(ss, line);
      lorenz.x0 = std::stof(line.substr(line.find("x0 = ") + 5));

      std::getline(ss, line);
      lorenz.y0 = std::stof(line.substr(line.find("y0 = ") + 5));

      std::getline(ss, line);
      lorenz.z0 = std::stof(line.substr(line.find("z0 = ") + 5));

    } else if (line.find("Rossler attractor parameters:") !=
               std::string::npos) {

      std::getline(ss, line);
      rossler.a = std::stof(line.substr(line.find("a = ") + 4));

      std::getline(ss, line);
      rossler.b = std::stof(line.substr(line.find("b = ") + 4));

      std::getline(ss, line);
      rossler.c = std::stof(line.substr(line.find("c = ") + 4));

      std::getline(ss, line);
      rossler.x0 = std::stof(line.substr(line.find("x0 = ") + 5));

      std::getline(ss, line);
      rossler.y0 = std::stof(line.substr(line.find("y0 = ") + 5));

      std::getline(ss, line);
      rossler.z0 = std::stof(line.substr(line.find("z0 = ") + 5));
    }
  }
}

} // namespace key
} // namespace cieucs