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
