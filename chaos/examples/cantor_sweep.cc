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
  Image2d<bool> img2d(kRes*12, kRes*12);
  ImageWriteView2d view(img2d, Range2d::FromOffsetAndSize(
    inches_to_pixels(1), inches_to_pixels(1), inches_to_pixels(10), inches_to_pixels(10)));

  for (int y = 0; y < view.height(); y++) {
    double ratio = (double)y / (view.height());
    RowWriter1d row(view, y);
    DrawCantor1d(row, Cantor1dOptions{.removal_ratio=ratio});
  }
  WritePgm(img2d, "cantor_sweep.pgm");
  return 0;
}

