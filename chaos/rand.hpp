// Copyright (c) 2025 Greg Prisament
// See LICENSE file.
#ifndef __CHAOS_RAND_HPP__
#define __CHAOS_RAND_HPP__

#include <random>

namespace chaos {

template <typename ValueT>
class Random {
  public:
    Random() : device_(), gen_(device_()), dist_(0, 1) {}
    explicit Random(unsigned int seed) : gen_(seed), dist_(0, 1) {}
    double ZeroToOne() {
      return dist_(gen_);
    }
  private:
   std::random_device device_;
   std::mt19937 gen_;
   std::uniform_real_distribution<ValueT> dist_;
};

} // namespace chaos

#endif  // __CHAOS_RAND_HPP__
