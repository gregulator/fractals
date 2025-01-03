// Copyright (c) 2024 Greg Prisament
// See LICENSE file.
#ifndef __CHAOS_CANTOR_CANTOR_HPP__
#define __CHAOS_CANTOR_CANTOR_HPP__

#include "fill.hpp"
#include "point.hpp"
#include "utils.hpp"

#include <cstdint>
#include <limits>

namespace chaos {

// -----------------------------------------------------------------------------
// 1-D Cantor Set
// -----------------------------------------------------------------------------
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

// -----------------------------------------------------------------------------
// 2-D Cantor Dust
// -----------------------------------------------------------------------------
struct Cantor2dOptions {
  int max_iterations = INT_MAX;
};

namespace internal {
template <Image2dWritable ImageT> 
void DrawCantor2d_Range(ImageT& dest, int iteration, Point2 min, Point2 max, const Cantor2dOptions& options) {
  if (iteration >= options.max_iterations) {
    Fill(dest, Range2d(int(min.x), int(min.y), int(max.x), int(max.y)), 1);
    return;
  }
  if ((max.x - min.x <= 1) && (max.y - max.x) <= 1) {
    int x = int((min.x + max.x)/2);
    int y = int((min.y + max.y)/2);
    SafeWrite(dest, x, y, 1);
    return;
  } else {
    DrawCantor2d_Range(
      dest,
      iteration+1,
      Point2(min.x, min.y),
      Point2(min.x + (max.x - min.x)/3, min.y + (max.y - min.y)/3),
      options);
    DrawCantor2d_Range(
      dest,
      iteration+1,
      Point2(min.x + 2*(max.x - min.x)/3, min.y),
      Point2(max.x, min.y + (max.y - min.y)/3),
      options);
    DrawCantor2d_Range(
      dest,
      iteration+1,
      Point2(min.x, min.y + 2*(max.y - min.y)/3),
      Point2(min.x + (max.x - min.x)/3, max.y),
      options);
    DrawCantor2d_Range(
      dest,
      iteration+1,
      Point2(min.x + 2*(max.x - min.x)/3, min.y + 2*(max.y - min.y)/3),
      Point2(max.x, max.y),
      options);
  }
}

}  // namespace internal

template <Image2dWritable ImageT> 
void DrawCantor2d(ImageT& dest, const Cantor2dOptions& options) {
  internal::DrawCantor2d_Range(dest, 0, Point2(0, 0), Point2(dest.width(), dest.height()), options);
}

} // namespace chaos

#endif // __CHAOS_CANTOR_CANTOR_HPP__
