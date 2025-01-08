// Copyright (c) 2025 Greg Prisament
// See LICENSE file.
#ifndef __CHAOS_POINT_HPP__
#define __CHAOS_POINT_HPP__

namespace chaos {

struct Point2 {
  Point2(double x_, double y_) : x(x_), y(y_) {}
  double x;
  double y;
};

inline double Dist(Point2 a, Point2 b) {
  double delta_x = b.x - a.x;
  double delta_y = b.y - a.y;
  return sqrt(delta_x*delta_x + delta_y*delta_y);
}

} // namespace chaos

#endif // __CHAOS_POINT_HPP__
