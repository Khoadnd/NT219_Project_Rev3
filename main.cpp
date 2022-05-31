#include "include/chaotic_systems.h"
#include "include/decode.h"
#include "include/encode.h"
#include "include/helper.h"
#include "include/img_processing.h"
#include <algorithm>
#include <iostream>

int main() {
  cieucs::img_processing::Data data_red, data_green, data_blue;
  cieucs::img_processing::Data data_red_scrambled, data_green_scrambled,
      data_blue_scrambled;

  size_t width, height;
  cieucs::img_processing::readImage("image.jpg", data_red, data_green,
                                    data_blue, width, height);

  cieucs::encode::setKey();

  cieucs::encode::scramble(data_red, data_green, data_blue, data_red_scrambled,
                           data_green_scrambled, data_blue_scrambled, width,
                           height);

  cieucs::encode::encode(data_red_scrambled, data_green_scrambled,
                         data_blue_scrambled, data_red, data_green, data_blue,
                         width, height);

  cieucs::decode::setKey();

  cieucs::decode::decode(data_red, data_green, data_blue, data_red_scrambled,
                         data_green_scrambled, data_blue_scrambled, width,
                         height);

  cieucs::decode::unscramble(data_red_scrambled, data_green_scrambled,
                             data_blue_scrambled, data_red, data_green,
                             data_blue, width, height);

  return 0;
}