// Copyright (c) 2024 Greg Prisament
// See LICENSE file.
#ifndef __CHAOS_UTILS_HPP__
#define __CHAOS_UTILS_HPP__

#include <fstream>

#include "image.hpp"

namespace chaos {

template <Image1dWritable ImageT>
void SafeWrite(ImageT& image, int x, typename ImageT::pixel_type p) {
  if (x < 0 || x >= image.width()) {
    return;
  }
  image.write(x, p);
}

} // namespace chaos

#endif  // __CHAOS_UTILS_HPP__
