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

  for (int j = 1; j < 8; j++) {
    Image1d<bool> img(280);
    DrawCantor1d(img, Cantor1dOptions{.max_iterations=j, .removal_ratio=1.0/6.0});

    for (int i = 0; i < img.width(); i++) {
      std::cout << int(img.read(i));
    }
    std::cout << std::endl;
  }

  return 0;
}
