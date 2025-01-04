// Copyright (c) 2025 Greg Prisament
// See LICENSE file.

#include "image.hpp"
#include "pgm.hpp"
#include "cantor/cantor.hpp"

#include <iostream>

using namespace chaos;

constexpr int kRes = 1200;
constexpr int kSeed = 200;

int inches_to_pixels(double inches) {
  return int(inches*kRes);
}

int main(void) {
  Image2d<uint8_t> canvas(kRes*12, kRes*12);

  ImageWriteView2d view(canvas, Range2d::FromOffsetAndSize(
    inches_to_pixels(1), inches_to_pixels(1), inches_to_pixels(10), inches_to_pixels(10)));
  AdditiveWriter2d writer(view, 16);
  DrawCantor2d(writer, Cantor2dOptions{.draw_all_iterations=true, .max_iterations=7, .seed = kSeed, .probability=(4.0/9.0)});
  WritePgm(canvas, "random_cantor_dust_quilt.pgm");
  return 0;
}
