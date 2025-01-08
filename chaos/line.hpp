// Copyright (c) 2025 Greg Prisament
// See LICENSE file.
#ifndef __CHAOS_LINE_HPP__
#define __CHAOS_LINE_HPP__

#include "range.hpp"
#include "image.hpp"
#include "point.hpp"
#include "utils.hpp"

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

struct Polar {
  double r;
  double theta;
};
struct Arc {
  Polar p0;
  Polar p1;
};

// A LineWriterPolarArc can draw arcs in polar coordinates.
template <Image2dWritable UnderlyingImageT>
class LineWriterPolarArc {
  public:
    using underlying_type = UnderlyingImageT;
    using pixel_type = typename underlying_type::pixel_type;
    LineWriterPolarArc(underlying_type& underlying, double inner_r, double outer_r) : underlying_(&underlying), inner_r_(inner_r), outer_r_(outer_r) {
      // Width is reported as the size of the circle that encompasses the
      // full underlying image. This way maximum resolution is achieved, even
      // at the edges of the image. 
      double d = sqrt(underlying_->width()*underlying_->width() + underlying_->height()*underlying_->height());
      // std::cout << "d " << d << std::endl;
      width_ = int(M_PI*d);
      // std::cout << "width " << width_ << std::endl;
    }

    // TODO: handle wrapping
    void DrawArcRecursive(Arc arc, pixel_type value) {
      // std::cout << "Drawing arc " << arc.p0.r << " " << arc.p0.theta << " " << arc.p1.r << " " << arc.p1.theta << std::endl;
      Point2 p0 = Cartesian(arc.p0);
      Point2 p1 = Cartesian(arc.p1);
      if (Dist(p0, p1) < 1.0) {
        SafeWrite(*underlying_, int(p0.x), int(p0.y), value);
        return;
      }
      double avg_r = (arc.p0.r + arc.p1.r)/2;
      double avg_theta = (arc.p0.theta + arc.p1.theta)/2;
      DrawArcRecursive(Arc{
        Polar{arc.p0.r, arc.p0.theta},
        Polar{avg_r, avg_theta}
      }, value);
      DrawArcRecursive(Arc{
        Polar{arc.p0.r, avg_theta},
        Polar{avg_r, arc.p1.theta}
      }, value);
      DrawArcRecursive(Arc{
        Polar{avg_r, arc.p0.theta},
        Polar{arc.p1.r, avg_theta}
      }, value);
      DrawArcRecursive(Arc{
        Polar{avg_r, avg_theta},
        Polar{arc.p1.r, arc.p1.theta}
      }, value);
    }

    void DrawLine(Line1d line, pixel_type value) {
      Arc arc = {Polar{
          .r = inner_r_,
          .theta = 2*M_PI*line.x0/width()
        }, Polar{
          .r = outer_r_,
          .theta = 2*M_PI*line.x1/width()
        }
      };
      DrawArcRecursive(arc, value);
    }

    int width() const {
      return width_;
    }
  private:
    Point2 Cartesian(Polar polar) {
      return Point2{
        polar.r*cos(polar.theta) + underlying_->width()/2,
        polar.r*sin(polar.theta) + underlying_->height()/2,
      };
    }
    underlying_type* underlying_;
    int width_;
    double inner_r_;
    double outer_r_;
};

} // namespace chaos

#endif // __CHAOS_LINE_HPP__
