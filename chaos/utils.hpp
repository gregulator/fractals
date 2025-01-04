// Copyright (c) 2024 Greg Prisament
// See LICENSE file.
#ifndef __CHAOS_UTILS_HPP__
#define __CHAOS_UTILS_HPP__

#include "image.hpp"

#include <algorithm>

namespace chaos {

template <typename ValueT>
ValueT Lerp(ValueT a, ValueT b, double t) {
  return ValueT(a + (b - a)*t);
}

template <Image1dWritable ImageT>
void SafeWrite(ImageT& image, int x, typename ImageT::pixel_type p) {
  if (x < 0 || x >= image.width()) {
    return;
  }
  image.write(x, p);
}

template <Image2dWritable ImageT>
void SafeWrite(ImageT& image, int x, int y, typename ImageT::pixel_type p) {
  if (x < 0 || x >= image.width()) {
    return;
  }
  if (y < 0 || y >= image.height()) {
    return;
  }
  image.write(x, y, p);
}

template <Image1dReadable SourceImageT, Image1dWritable DestImageT>
void SafeCopy(const SourceImageT& source, DestImageT& dest) {
  int width = std::min(source.width(), dest.width());
  for (int x = 0; x < width; x++) {
    dest.write(x, source.read(x));
  }
}

} // namespace chaos

#endif  // __CHAOS_UTILS_HPP__
