// Copyright (c) 2024 Greg Prisament
// See LICENSE file.
#ifndef __CHAOS_IMAGE_H__
#define __CHAOS_IMAGE_H__

#include "range.hpp"

#include <cstdint>
#include <concepts>
#include <vector>

namespace chaos {

template <typename ImageT>
concept Image1dWritable = requires(ImageT i, typename ImageT::pixel_type p) {
  i.write(0, p);
  {i.width()} -> std::convertible_to<int>;
};

template <typename ImageT>
concept Image1dReadable = requires(ImageT i, typename ImageT::pixel_type p) {
  p = i.read(0);
  {i.width()} -> std::convertible_to<int>;
};

template <typename ImageT>
concept Image2dReadable = requires(ImageT i, typename ImageT::pixel_type p) {
  p = i.read(0, 0);
  {i.width()} -> std::convertible_to<int>;
  {i.height()} -> std::convertible_to<int>;
};

template <typename ImageT>
concept Image2dWritable = requires(ImageT i, typename ImageT::pixel_type p) {
  i.write(0, 0, p);
  {i.width()} -> std::convertible_to<int>;
  {i.height()} -> std::convertible_to<int>;
};

template <typename PixelT>
class Image1d {
  public:
    using pixel_type = PixelT;
    explicit Image1d(int width) : data_(width) {}
    void write(int x, pixel_type value) {
      data_[x] = value;
    }
    pixel_type read(int x) {
      return data_[x];
    }
    int width() {
      return data_.size();
    }
  private:
    std::vector<pixel_type> data_;
};

template <typename PixelT>
class Image2d {
  public:
    using pixel_type = PixelT;
    explicit Image2d(int width, int height) : width_(width), height_(height), data_(width*height) {}
    void write(int x, int y, pixel_type value) {
      data_[y*width_ + x] = value;
    }
    pixel_type read(int x, int y) const {
      return data_[y*width_ + x];
    }
    int width() const {
      return width_;
    }
    int height() const {
      return height_;
    }
  private:
    int width_;
    int height_;
    std::vector<pixel_type> data_;
};

template <Image2dWritable UnderlyingImageT>
class ImageWriteView2d {
  public:
    using underlying_type = UnderlyingImageT;
    using pixel_type = typename UnderlyingImageT::pixel_type;
    explicit ImageWriteView2d(underlying_type& underlying, Range2d subrange) : underlying_(&underlying), subrange_(subrange) {}

    void write(int x, int y, pixel_type value) {
      underlying_->write(x + subrange_.x0, y + subrange_.y0, value);
    }
    pixel_type read(int x, int y) const {
      return underlying_->read(x + subrange_.x0, y + subrange_.y0);
    }
    int width() const {
      return subrange_.width();
    }
    int height() const {
      return subrange_.height();
    }
  private:
    underlying_type* underlying_;
    Range2d subrange_;
};

template <Image2dWritable UnderlyingImageT>
class BarImageWriter {
  public:
    using underlying_type = UnderlyingImageT;
    using pixel_type = typename underlying_type::pixel_type;
    explicit BarImageWriter(underlying_type& underlying) : underlying_(&underlying) {}
    void write(int x, pixel_type value) {
      for (int y = 0; y < underlying_->height(); y++) {
        underlying_->write(x, y, value);
      }
    }
    int width() {
      return underlying_->width();
    }
  private:
    underlying_type* underlying_;
};

struct Rgb8 {
  union {
    uint8_t v[3];
    struct {
      uint8_t r;
      uint8_t g;
      uint8_t b;
    };
  };
};

} // namespace chaos

#endif // __CHAOS_IMAGE_H__
