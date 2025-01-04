// Copyright (c) 2025 Greg Prisament
// See LICENSE file.
#ifndef __CHAOS_LINE_HPP__
#define __CHAOS_LINE_HPP__

#include "range.hpp"
#include "image.hpp"

#include <cstdint>
#include <concepts>
#include <vector>
#include <iostream>

namespace chaos {

// Represents a line segment.
using Line1d = Range<double>;

// Concept Line1dDrawable is satisfied by types that can have line segments
// drawn on them.
template <typename DrawableT>
concept Line1dDrawable = requires(DrawableT d) {
  d.DrawLine(Line1d(0), 1);
  {d.width()} -> std::convertible_to<int>;
};

// A LineWriter1d can draw lines on an Image1d.
template <Image1dWritable UnderlyingImageT>
class LineWriter1d {
  public:
    using underlying_type = UnderlyingImageT;
    using pixel_type = typename underlying_type::pixel_type;
    LineWriter1d(underlying_type& underlying) : underlying_(&underlying) {}
    void DrawLine(Line1d line, pixel_type value) {
      int x0 = std::max(0, int(line.x0+0.5));
      int x1 = std::min(int(line.x1+0.5), width());
      for (int x = x0; x < x1; x++) {
        underlying_->write(x, value);
      }
    }
    int width() const {
      return underlying_->width();
    }
  private:
    underlying_type* underlying_;
};

} // namespace chaos

#endif // __CHAOS_LINE_HPP__
