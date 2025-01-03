// Copyright (c) 2024 Greg Prisament
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
  Image2d<bool> img(kRes*12, kRes*12);

  ImageWriteView2d view(img, Range2d::FromOffsetAndSize(
    (14400-13122)/2, (14400-13122)/2, 13122, 13122));
  DrawCantor2d(view, Cantor2dOptions{.max_iterations=6});
  WriteBlackWhitePgm(img, "cantor_dust.pgm");
  return 0;
}
