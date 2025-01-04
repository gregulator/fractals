// Copyright (c) 2025 Greg Prisament
// See LICENSE file.

#include "image.hpp"
#include "pgm.hpp"
#include "cantor/cantor.hpp"

#include <iostream>

using namespace chaos;

constexpr int kRes = 1200;
constexpr int kSeed = 7;

int inches_to_pixels(double inches) {
  return int(inches*kRes);
}

int main(void) {
  Image2d<bool> img(kRes*12, kRes*12);

  ImageWriteView2d view(img, Range2d::FromOffsetAndSize(
    inches_to_pixels(1), inches_to_pixels(1), inches_to_pixels(10), inches_to_pixels(10)));
  DrawCantor2d(view, Cantor2dOptions{.max_iterations=7, .seed = kSeed, .probability=(3.0/5.0)});
  WriteBlackWhitePgm(img, "random_cantor_dust.pgm");
  return 0;
}
