#include "../include/img_processing.h"

#include <opencv2/imgcodecs.hpp>

namespace cieucs {
namespace img_processing {

void readImage(const char *i_path, Data &o_data_red, Data &o_data_green,
               Data &o_data_blue, size_t &o_width, size_t &o_height) {
  cv::Mat img = cv::imread(i_path, cv::IMREAD_COLOR);

  o_data_red.reserve(img.size().area());
  o_data_green.reserve(img.size().area());
  o_data_blue.reserve(img.size().area());

  for (size_t i = 0; i < img.size().area(); ++i) {
    o_data_red.push_back(img.data[i * 3 + 0]);
    o_data_green.push_back(img.data[i * 3 + 1]);
    o_data_blue.push_back(img.data[i * 3 + 2]);
  }

  o_width = img.size().width;
  o_height = img.size().height;

  img.release();
}

void writeImage(const char *i_path, const Data &i_data_red,
                const Data &i_data_green, const Data &i_data_blue,
                const size_t &i_width, const size_t &i_height) {
  cv::Mat img_r(i_height, i_width, CV_8UC1,
                const_cast<uchar *>(i_data_red.data()));
  cv::Mat img_g(i_height, i_width, CV_8UC1,
                const_cast<uchar *>(i_data_green.data()));
  cv::Mat img_b(i_height, i_width, CV_8UC1,
                const_cast<uchar *>(i_data_blue.data()));

  cv::Mat out;
  cv::merge(std::vector<cv::Mat>{img_r, img_g, img_b}, out);
  cv::imwrite(i_path, out);

  out.release();
  img_r.release();
  img_g.release();
  img_b.release();
}

} // namespace img_processing
} // namespace cieucs