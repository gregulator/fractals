// Copyright (c) 2024 Greg Prisament
// See LICENSE file.

#include "image.hpp"
#include "pgm.hpp"
#include "cantor/cantor.hpp"

#include <iostream>

using namespace chaos;

constexpr int kRes = 600;

int inches_to_pixels(double inches) {
  return int(inches*kRes);
}

int main(void) {
  Image2d<uint8_t> canvas(kRes*12, kRes*12);

  Image1d<uint8_t> img1d(inches_to_pixels(10));
  for (int i = 0; i < 7; i++) {
    AdditiveWriter1d writer(img1d, 16);
    DrawCantor1d(writer, Cantor1dOptions{.removal_start_ratio=(1.0/4.0), .removal_end_ratio=(2.0/4.0), .max_iterations=i});
  }
  ImageWriteView2d view(canvas, Range2d::FromOffsetAndSize(
    inches_to_pixels(1), inches_to_pixels(1), inches_to_pixels(10), inches_to_pixels(10)));
  BarImageWriter bar_writer(view);
  SafeCopy(img1d, bar_writer);
  WritePgm(canvas, "cantor_asymmetric_2.pgm");
  return 0;
}
