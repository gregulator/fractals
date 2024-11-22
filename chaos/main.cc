// Copyright (c) 2024 Greg Prisament
// See LICENSE file.

#include "image.hpp"
#include "cantor/cantor.hpp"

#include <iostream>

using namespace chaos;

int main(void) {
  // Rgb8 c;
  // c.r = 1;
  // c.g = 2;
  // c.b = 3;
  // c.v[0]*=2;
  // c.v[1]*=2;
  // c.v[2]*=2;
  // std::cout << (int)c.r << (int)c.g << (int)c.b << std::endl;

  Image2d<bool> img2d(243, 10);
  BarImageWriter<bool> img1d(img2d);
  DrawCantor1d(img1d, Cantor1dOptions{.max_iterations=0});

  for (int y = 0; y < img2d.height(); y++) {
    for (int x = 0 ; x < img2d.width(); x++) {
      std::cout << int(img2d.read(x, y));
    }
    std::cout << std::endl;
  }

  return 0;
}
