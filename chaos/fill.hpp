// Copyright (c) 2025 Greg Prisament
// See LICENSE file.
#ifndef __CHAOS_FILL_HPP__
#define __CHAOS_FILL_HPP__

#include "image.hpp"
#include "range.hpp"

#include <algorithm>

namespace chaos {

template <Image1dWritable ImageT>
void Fill(ImageT& image, typename ImageT::pixel_type p) {
  for (int x = 0; x < image.width(); x++) {
    image.write(x, p);
  }
}

template <Image1dWritable ImageT>
void Fill(ImageT& image, int x0, int x1, typename ImageT::pixel_type p) {
  int x0_ = std::max(0, x0);
  int x1_ = std::min(image.width(), x1);
  for (int x = x0_; x < x1_; x++) {
    image.write(x, p);
  }
}

template <Image2dWritable ImageT>
void Fill(ImageT& image, typename ImageT::pixel_type p) {
  for (int y = 0; y < image.height(); y++) {
    for (int x = 0; x < image.width(); x++) {
      image.write(x, y, p);
    }
  }
}

template <Image2dWritable ImageT>
void Fill(ImageT& image, Range2d range, typename ImageT::pixel_type p) {
  int x0 = std::max(0, range.x0);
  int y0 = std::max(0, range.y0);
  int x1 = std::min(image.width(), range.x1);
  int y1 = std::min(image.height(), range.y1);
  for (int y = y0; y < y1; y++) {
    for (int x = x0; x < x1; x++) {
      image.write(x, y, p);
    }
  }
}

} // namespace chaos

#endif  // __CHAOS_FILL_HPP__
