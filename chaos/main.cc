// Copyright (c) 2024 Greg Prisament
// See LICENSE file.

#include "image.hpp"
#include "pgm.hpp"
#include "cantor/cantor.hpp"

#include <iostream>

using namespace chaos;

int main(void) {
  Image2d<bool> img2d(1920, 1080);
  BarImageWriter<bool> img1d(img2d);
  DrawCantor1d(img1d, Cantor1dOptions{.max_iterations=8});
  WritePgm(img2d, "cantor.pgm");
  return 0;
}
