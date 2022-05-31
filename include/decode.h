#pragma once

#include "img_processing.h"
#include <vector>

namespace cieucs {
namespace decode {

void setKey();

void unscramble(const img_processing::Data &i_data_red,
                const img_processing::Data &i_data_green,
                const img_processing::Data &i_data_blue,
                img_processing::Data &o_data_red,
                img_processing::Data &o_data_green,
                img_processing::Data &o_data_blue, const size_t &i_width = 256,
                const size_t &i_height = 256);

void decode(const img_processing::Data &i_data_red,
            const img_processing::Data &i_data_green,
            const img_processing::Data &i_data_blue,
            img_processing::Data &o_data_red,
            img_processing::Data &o_data_green,
            img_processing::Data &o_data_blue, const size_t &i_width = 256,
            const size_t &i_height = 256);

void resetState();

} // namespace decode
} // namespace cieucs