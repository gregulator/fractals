// Copyright (c) 2024 Greg Prisament
// See LICENSE file.
#ifndef __CHAOS_IMAGE_H__
#define __CHAOS_IMAGE_H__

#include <cstdint>
#include <concepts>
#include <vector>

template <typename ImageT>
concept Image1dWritable = requires(ImageT i, typename ImageT::pixel_type p) {
  i.write(0, p);
  {i.width()} -> std::convertible_to<int>;
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
    pixel_type read(int x, int y) {
      return data_[y*width_ + x];
    }
    int width() {
      return width_;
    }
    int height() {
      return height_;
    }
  private:
    int width_;
    int height_;
    std::vector<pixel_type> data_;
};

template <typename PixelT>
class BarImageWriter {
  public:
    using pixel_type = PixelT;
    explicit BarImageWriter(Image2d<PixelT>& underlying) : underlying_(&underlying) {}
    void write(int x, pixel_type value) {
      for (int y = 0; y < underlying_->height(); y++) {
        underlying_->write(x, y, value);
      }
    }
    int width() {
      return underlying_->width();
    }
  private:
    Image2d<PixelT>* underlying_;
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

#endif // __CHAOS_IMAGE_H__
