#pragma once

#include <algorithm>
#include <numeric>
#include <vector>

namespace cieucs {
namespace helper {

template <typename T>
void sort_indexes(const std::vector<T> &v, std::vector<size_t> &out) {
  out.resize(v.size());
  std::iota(out.begin(), out.end(), 0);
  std::sort(out.begin(), out.end(),
            [&v](size_t i1, size_t i2) { return v[i1] < v[i2]; });
}

} // namespace helper
} // namespace cieucs