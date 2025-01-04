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

  for (int i = 0; i < 7; i++) {
    ImageWriteView2d view(img2d, Range2d::FromOffsetAndSize(
      (14400-13122)/2, inches_to_pixels(1+1.5*i), 13122, inches_to_pixels(1)));
    BarImageWriter img1d(view);
    DrawMultiGapCantor1d(img1d, MultiGapCantor1dOptions{
        .max_iterations=i,
        .segments = {
            Range<double>(0.0, 0.1), 
            Range<double>(0.2, 0.3), 
            Range<double>(0.4, 0.5), 
            Range<double>(0.6, 0.7), 
            Range<double>(0.8, 0.9), 
        }
    });
  }
  WriteBlackWhitePgm(img2d, "even_reals.pgm");
  return 0;
}
