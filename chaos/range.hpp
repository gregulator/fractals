// Copyright (c) 2024 Greg Prisament
// See LICENSE file.
#ifndef __CHAOS_RANGE_HPP__
#define __CHAOS_RANGE_HPP__

namespace chaos {

struct Range2d {
  Range2d(int x0_, int y0_, int x1_, int y1_) : x0(x0_), y0(y0_), x1(x1_), y1(y1_) {}
  Range2d(int x1_, int y1_) : x0(0), y0(0), x1(x1_), y1(y1_) {}
  static Range2d FromOffsetAndSize(int x0, int y0, int width, int height) {
    return Range2d(x0, y0, x0+width, y0+height);
  }
  int x0;
  int y0;
  int x1;
  int y1;
  int width() const {return x1 - x0;}
  int height() const {return y1 - y0;}
};

} // namespace chaos

#endif // __CHAOS_RANGE_HPP__
