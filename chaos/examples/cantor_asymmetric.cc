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

  for (int i = 0; i < 7; i++) {
    ImageWriteView2d view(img2d, Range2d::FromOffsetAndSize(
      inches_to_pixels(1), inches_to_pixels(1+1.5*i), inches_to_pixels(10), inches_to_pixels(1)));
    BarImageWriter img1d(view);
    DrawCantor1d(img1d, Cantor1dOptions{.removal_start_ratio=(1.0/4.0), .removal_end_ratio=(2.0/4.0), .max_iterations=i});
  }
  WritePgm(img2d, "cantor_asymmetric.pgm");
  return 0;
}
