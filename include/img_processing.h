#pragma once

#include "../include/key.h"
#include <vector>

namespace cieucs {
namespace img_processing {

using Data = std::vector<unsigned char>;

void readImage(const char *i_path, Data &o_data_red, Data &o_data_green,
               Data &o_data_blue, size_t &o_width, size_t &o_height);

void writeImage(const char *i_path, const Data &i_data_red,
                const Data &i_data_green, const Data &i_data_blue,
                const size_t &i_width, const size_t &i_height);

} // namespace img_processing
} // namespace cieucs