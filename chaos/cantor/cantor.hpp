// Copyright (c) 2024 Greg Prisament
// See LICENSE file.
#ifndef __CHAOS_CANTOR_CANTOR_HPP__
#define __CHAOS_CANTOR_CANTOR_HPP__

#include "fill.hpp"
#include "rand.hpp"
#include "line.hpp"
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
// Multi-gap 1-D Cantor Set
// -----------------------------------------------------------------------------
struct MultiGapCantor1dOptions {
  int max_iterations = INT_MAX;
  std::vector<Range<double>> segments;
};

namespace internal {
template <Line1dDrawable DrawT> 
void DrawMultiGapCantor1d_Range(DrawT& dest, int iteration, Line1d line, const MultiGapCantor1dOptions& options) {
  if ((iteration >= options.max_iterations) || (line.width() < 1.0)) {
    dest.DrawLine(line, 1);
    return;
  }
  for (auto& segment : options.segments) {
    DrawMultiGapCantor1d_Range(
        dest,
        iteration+1,
        Line1d(Lerp(line.x0, line.x1, segment.x0), Lerp(line.x0, line.x1, segment.x1)),
        options);
  }
}
}  // namespace internal

template <Line1dDrawable DrawT> 
void DrawMultiGapCantor1d(DrawT& dest, const MultiGapCantor1dOptions& options) {
  internal::DrawMultiGapCantor1d_Range(dest, 0, Line1d(dest.width()-1), options);
}

// -----------------------------------------------------------------------------
// Devil's Staircase
// -----------------------------------------------------------------------------
struct DevilsStaircase1dOptions {
  int max_iterations = INT_MAX;
  double min_y = 0;
  double max_y = 255;
};

namespace internal {
template <Image1dWritable ImageT> 
void DevilsStaircase1d_Range(ImageT& dest, int iteration, double min_x, double
                             max_x, double min_y, double max_y, const
                             DevilsStaircase1dOptions& options) {
  if (max_x - min_x <= 1) {
    int y = int((min_y+ max_y)/2);
    Fill(dest, int(min_x), int(max_x), y);
    return;
  } else if (iteration >= options.max_iterations) {
    for (int x = min_x; x < max_x; x++) {
      double t = (x - min_x) / (max_x - min_x);
      double y = min_y + t*(max_y-min_y);
      dest.write(x, y);
    }
    return;
  }
  if (max_x - min_x <= 1) {
    int y = int((min_y+ max_y)/2);
    Fill(dest, int(min_x), int(max_x), y);
    return;
  } else {
    double avg_y = (min_y + max_y)/2.0;
    double start_x = min_x + (max_x - min_x)/3.0;
    double end_x = min_x + 2*(max_x - min_x)/3.0;
    DevilsStaircase1d_Range(
        dest,
        iteration+1,
        min_x, start_x,
        min_y, avg_y,
        options);
    DevilsStaircase1d_Range(
        dest,
        iteration+1,
        end_x, max_x,
        avg_y, max_y,
        options);
    Fill(dest, int(start_x), int(end_x), int(avg_y));
  }
}
}  // namespace internal

template <Image1dWritable ImageT> 
void DrawDevilsStaircase1d(ImageT& dest, const DevilsStaircase1dOptions& options) {
  internal::DevilsStaircase1d_Range(dest, 0, 0, dest.width()-1, options.min_y, options.max_y, options);
}

// -----------------------------------------------------------------------------
// 2-D Cantor Dust
// -----------------------------------------------------------------------------
struct Cantor2dOptions {
  int max_iterations = INT_MAX;
  unsigned int seed = 0;
  std::optional<double> probability = std::nullopt;
  bool draw_all_iterations = false;
};

namespace internal {
template <Image2dWritable ImageT> 
void DrawCantor2d_Range(ImageT& dest, Random<double>& random, int iteration, Point2 min, Point2 max, const Cantor2dOptions& options) {
  if (iteration >= options.max_iterations) {
    Fill(dest, Range2d(int(min.x), int(min.y), int(max.x), int(max.y)), 1);
    return;
  }
  if ((max.x - min.x <= 1) && (max.y - min.y) <= 1) {
    int x = int((min.x + max.x)/2);
    int y = int((min.y + max.y)/2);
    SafeWrite(dest, x, y, 1);
    return;
  } else {
    for (int j = 0; j < 3; j++) {
      for (int i = 0; i < 3; i++) {
        bool draw = (i != 1 && j != 1);
        if (options.probability.has_value()) {
          draw = random.ZeroToOne() < *options.probability;
        }
        if (draw) {
          double x0 = min.x + i*(max.x - min.x)/3;
          double y0 = min.y + j*(max.y - min.y)/3;
          double x1 = min.x + (i+1)*(max.x - min.x)/3;
          double y1 = min.y + (j+1)*(max.y - min.y)/3;
          if (options.draw_all_iterations) {
            Fill(dest, Range2d(int(x0), int(y0), int(x1), int(y1)), 1);
          }
          DrawCantor2d_Range(
            dest,
            random,
            iteration+1,
            Point2(x0, y0),
            Point2(x1, y1),
            options);
        }
      }
    }
  }
}

}  // namespace internal

template <Image2dWritable ImageT> 
void DrawCantor2d(ImageT& dest, const Cantor2dOptions& options) {
  Random<double> random(options.seed);
  internal::DrawCantor2d_Range(dest, random, 0, Point2(0, 0), Point2(dest.width(), dest.height()), options);
}

} // namespace chaos

#endif // __CHAOS_CANTOR_CANTOR_HPP__
