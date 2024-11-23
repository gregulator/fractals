// Copyright (c) 2024 Greg Prisament
// See LICENSE file.
#ifndef __CHAOS_PGM_HPP__
#define __CHAOS_PGM_HPP__

#include <fstream>

#include "image.hpp"

namespace chaos {

template <Image2dReadable ImageT>
void WritePgm(const ImageT& image, const std::string& filename) {
  std::ofstream outfile;
  outfile.open(filename);
  outfile << "P2" << std::endl;
  outfile << int(image.width()) << " " << int(image.height()) << std::endl;
  outfile << "1" << std::endl;
  for (int y = 0; y < image.height(); y++) {
    for (int x = 0; x < image.width(); x++) {
      outfile << image.read(x, y) << " ";
    }
      outfile << std::endl;
  }
}

} // namespace chaos

#endif  // __CHAOS_PGM_HPP__
