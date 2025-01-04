// Copyright (c) 2025 Greg Prisament
// See LICENSE file.

#include "image.hpp"
#include "pgm.hpp"
#include "cantor/cantor.hpp"

#include <iostream>

using namespace chaos;

constexpr int kRes = 1200;

int inches_to_pixels(double inches) {
  return int(inches*kRes);
}

int main(void) {
  Image2d<bool> img2d(kRes*12, kRes*12);

  ImageWriteView2d view(img2d, Range2d::FromOffsetAndSize(
    (14400-13122)/2, 0, 13122, 14400));
  PlotImageWriter<decltype(view), double> img1d(view, 1);
  DrawDevilsStaircase1d(img1d, DevilsStaircase1dOptions{
      .max_iterations=9,
      .min_y = 0,
      .max_y = 13122-1
  });
  WriteBlackWhitePgm(img2d, "devils_staircase.pgm");
  return 0;
}
