#include "../include/key.h"

#include <boost/archive/binary_oarchive.hpp>
#include <cryptopp/filters.h>
#include <fstream>
#include <random>
#include <sstream>
#include <stdexcept>

#include <cryptopp/base64.h>

namespace cieucs {
namespace key {

void Key::genRandomKey() {
  srand(static_cast<unsigned>(time(nullptr)));

  real lo = real{"-1", 512};
  real hi = real{"1", 512};

  lorenz.x0.set(lo + rand() / (RAND_MAX / (hi - lo)));
  lorenz.y0.set(lo + rand() / (RAND_MAX / (hi - lo)));
  lorenz.z0.set(lo + rand() / (RAND_MAX / (hi - lo)));

  rossler.x0.set(lo + rand() / (RAND_MAX / (hi - lo)));
  rossler.y0.set(lo + rand() / (RAND_MAX / (hi - lo)));
  rossler.z0.set(lo + rand() / (RAND_MAX / (hi - lo)));

  // generate lorenz parameters
  lo.set("9.7");
  hi.set("37.4");
  lorenz.alpha.set(lo + rand() / (RAND_MAX / (hi - lo)));

  lo.set("25.6");
  hi.set("94.8");
  lorenz.rho.set(lo + rand() / (RAND_MAX / (hi - lo)));

  lo.set("2.6");
  hi.set("8.4");
  lorenz.beta.set(lo + rand() / (RAND_MAX / (hi - lo)));

  // generate rossler parameters
  lo.set("0.2");
  hi.set("0.38");
  rossler.alpha.set(lo + rand() / (RAND_MAX / (hi - lo)));
  rossler.beta.set(lo + rand() / (RAND_MAX / (hi - lo)));

  lo.set("4.3");
  hi.set("5.3");
  rossler.gamma.set(lo + rand() / (RAND_MAX / (hi - lo)));

  writeKey("key.key");
}

void Key::writeKey(const char *o_keyPath) {

  std::ofstream key_file(o_keyPath);

  std::stringstream ss;

  ss << "Lorenz attractor parameters:" << std::endl;
  ss << "alpha = " << lorenz.alpha.to_string() << std::endl;
  ss << "rho = " << lorenz.rho.to_string() << std::endl;
  ss << "beta = " << lorenz.beta.to_string() << std::endl;
  ss << "x0 = " << lorenz.x0.to_string() << std::endl;
  ss << "y0 = " << lorenz.y0.to_string() << std::endl;
  ss << "z0 = " << lorenz.z0.to_string() << std::endl;

  ss << std::endl;

  ss << "Rossler attractor parameters:" << std::endl;
  ss << "alpha = " << rossler.alpha.to_string() << std::endl;
  ss << "beta = " << rossler.beta.to_string() << std::endl;
  ss << "gamma = " << rossler.gamma.to_string() << std::endl;
  ss << "x0 = " << rossler.x0.to_string() << std::endl;
  ss << "y0 = " << rossler.y0.to_string() << std::endl;
  ss << "z0 = " << rossler.z0.to_string() << std::endl;

  // uncomment to encode key to base64
  // std::string data;
  // CryptoPP::StringSource source(
  //     ss.str(), true,
  //     new CryptoPP::Base64Encoder(new CryptoPP::StringSink(data)));

  // key_file << data;
  key_file << ss.str();

  key_file.close();
}

void Key::readKey(const char *i_keyPath) {

  std::ifstream key_file(i_keyPath);

  if (!key_file.is_open())
    throw new std::runtime_error("Error: cannot open key file");

  std::string line = "", buf = "";
  std::string data = "";

  // uncomment to decode key from base64
  // while (std::getline(key_file, line)) {
  //   CryptoPP::StringSource source(
  //       line, true, new CryptoPP::Base64Decoder(new
  //       CryptoPP::StringSink(buf)));
  //   data += buf;
  //   line.clear();
  //   buf.clear();
  // }

  while (std::getline(key_file, line)) {
    data += line + "\n";
    line.clear();
  }

  key_file.close();

  std::stringstream ss(data);
  while (std::getline(ss, line)) {

    if (line.find("Lorenz attractor parameters:") != std::string::npos) {

      std::getline(ss, line);
      lorenz.alpha.set(line.substr(line.find("alpha = ") + 8));

      std::getline(ss, line);
      lorenz.rho.set(line.substr(line.find("rho = ") + 6));

      std::getline(ss, line);
      lorenz.beta.set(line.substr(line.find("beta = ") + 7));

      std::getline(ss, line);
      lorenz.x0.set(line.substr(line.find("x0 = ") + 5));

      std::getline(ss, line);
      lorenz.y0.set(line.substr(line.find("y0 = ") + 5));

      std::getline(ss, line);
      lorenz.z0.set(line.substr(line.find("z0 = ") + 5));

    } else if (line.find("Rossler attractor parameters:") !=
               std::string::npos) {

      std::getline(ss, line);
      rossler.alpha.set(line.substr(line.find("alpha = ") + 8));

      std::getline(ss, line);
      rossler.beta.set(line.substr(line.find("beta = ") + 7));

      std::getline(ss, line);
      rossler.gamma.set(line.substr(line.find("gamma = ") + 8));

      std::getline(ss, line);
      rossler.x0.set(line.substr(line.find("x0 = ") + 5));

      std::getline(ss, line);
      rossler.y0.set(line.substr(line.find("y0 = ") + 5));

      std::getline(ss, line);
      rossler.z0.set(line.substr(line.find("z0 = ") + 5));
    }
  }
}

} // namespace key
} // namespace cieucs