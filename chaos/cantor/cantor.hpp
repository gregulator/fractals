// Copyright (c) 2024 Greg Prisament
// See LICENSE file.
#ifndef __CHAOS_CANTOR_CANTOR_HPP__
#define __CHAOS_CANTOR_CANTOR_HPP__

#include "utils.hpp"

#include <cstdint>
#include <limits>

namespace chaos {

struct Cantor1dOptions {
  int max_iterations = INT_MAX;
  double removal_start_ratio = (1.0/3.0);
  double removal_end_ratio = (2.0/3.0);
};

namespace internal {
template <Image1dWritable ImageT> 
void DrawCantor1d_Range(ImageT& dest, int iteration, double min_x, double max_x, const Cantor1dOptions& options) {
  if (iteration >= options.max_iterations) {
    for (int i = int(min_x+0.5); i < int(max_x+0.5); i++) {
      SafeWrite(dest, i, 1);
    }
    return;
  }
  if (max_x - min_x <= 1) {
    int p = int((min_x+ max_x)/2);
    SafeWrite(dest, p-1, 1);
    SafeWrite(dest, p, 1);
    SafeWrite(dest, p+1, 1);
    return;
  } else {
    DrawCantor1d_Range(dest, iteration+1, min_x, min_x + (max_x - min_x)*options.removal_start_ratio, options);
    DrawCantor1d_Range(dest, iteration+1, min_x + (max_x-min_x)*options.removal_end_ratio, max_x, options);
  }
}
}  // namespace internal

template <Image1dWritable ImageT> 
void DrawCantor1d(ImageT& dest, const Cantor1dOptions& options) {
  internal::DrawCantor1d_Range(dest, 0, 0, dest.width()-1, options);
}

} // namespace chaos

#endif // __CHAOS_CANTOR_CANTOR_HPP__
