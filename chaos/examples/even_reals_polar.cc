// Copyright (c) 2025 Greg Prisament
// See LICENSE file.

#include "image.hpp"
#include "pgm.hpp"
#include "cantor/cantor.hpp"

#include <iostream>

using namespace chaos;

constexpr int kRes = 1024;

int inches_to_pixels(double inches) {
  return int(inches*kRes);
}

int main(void) {
  Image2d<bool> canvas(kRes*12, kRes*12);

  for (int i = 0; i < 7; i++) {
    ImageWriteView2d view(canvas, Range2d::FromOffsetAndSize(
      inches_to_pixels(1), inches_to_pixels(1), inches_to_pixels(10), inches_to_pixels(10)));
    LineWriterPolarArc writer(view, inches_to_pixels(i/2.0), inches_to_pixels((i+1)/2.0));
    DrawMultiGapCantor1d(writer, MultiGapCantor1dOptions{
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
  WriteBlackWhitePgm(canvas, "even_reals_polar.pgm");
  return 0;
}
