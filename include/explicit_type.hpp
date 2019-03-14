// Copyright (C) 2017 - 2018 Mariusz Jaskółka.
//
// Use, modification, and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef jm4r_EXPLICIT_TYPE_H
#define jm4r_EXPLICIT_TYPE_H

#include <type_traits>
#include <utility>

namespace mj {

template <typename T, typename Tag> class explicit_type {
public:
  using value_type = typename std::remove_const<T>::type;

public:
  explicit_type() : value_{} {}
  explicit explicit_type(const value_type &v) : value_(v) {}
  explicit explicit_type(value_type &&v) : value_{std::move(v)} {}
  explicit_type(const explicit_type &) = default;
  explicit_type(explicit_type &&) = default;
  explicit_type &operator=(const explicit_type &) = default;
  explicit_type &operator=(explicit_type &&) = default;
  bool operator==(explicit_type v) { return v.value_ == value_; }
  bool operator!=(explicit_type v) { return v.value_ != value_; }

  //logical operators:
  friend bool operator==(const value_type &v1, const explicit_type &v2) {
    return v1 == v2.value_;
  }
  friend bool operator==(const explicit_type &v1, const value_type &v2) {
    return v1.value_ == v2;
  }
  friend bool operator!=(const value_type &v1, const explicit_type &v2) {
    return v1 != v2.value_;
  }
  friend bool operator!=(const explicit_type &v1, const value_type &v2) {
    return v1.value_ != v2;
  }
  friend bool operator<(const value_type &v1, const explicit_type &v2) {
    return v1 < v2.value_;
  }
  friend bool operator<(const explicit_type &v1, const value_type &v2) {
    return v1.value_ < v2;
  }
  friend bool operator<=(const value_type &v1, const explicit_type &v2) {
    return v1 <= v2.value_;
  }
  friend bool operator<=(const explicit_type &v1, const value_type &v2) {
    return v1.value_ <= v2;
  }
  friend bool operator>(const value_type &v1, const explicit_type &v2) {
    return v1 > v2.value_;
  }
  friend bool operator>(const explicit_type &v1, const value_type &v2) {
    return v1.value_ > v2;
  }
  friend bool operator>=(const value_type &v1, const explicit_type &v2) {
    return v1 >= v2.value_;
  }
  friend bool operator>=(const explicit_type &v1, const value_type &v2) {
    return v1.value_ >= v2;
  }
  
  //arithmetic operators:
  friend explicit_type operator+(const explicit_type &v1, const explicit_type &v2) {
    return explicit_type{v1.value_ + v2.value_};
  }
  friend explicit_type operator-(const explicit_type &v1, const explicit_type &v2) {
    return explicit_type{v1.value_ - v2.value_};
  }
  friend explicit_type operator*(const value_type &v1, const explicit_type &v2) {
    return explicit_type{v1 * v2.value_};
  }
  friend explicit_type operator*(const explicit_type &v1, const value_type &v2) {
    return explicit_type{v1.value_ * v2};
  }
  friend explicit_type operator/(const explicit_type &v1, const value_type &v2) {
    return explicit_type{v1.value_ / v2};
  }
  friend value_type operator/(const explicit_type &v1, const explicit_type &v2) {
    return v1.value_ / v2.value_;
  }
  friend value_type operator%(const explicit_type &v1, const value_type &v2) {
    return value_type{v1.value_ % v2};
  }
  
  //bit operators:
  friend explicit_type operator<<(const explicit_type &v1, const value_type &v2) {
    return explicit_type{v1.value_ << v2};
  }
  friend explicit_type operator<<(const explicit_type &v1, const explicit_type &v2) {
    return explicit_type{v1.value_ << v2.value_};
  }
  friend explicit_type operator>>(const explicit_type &v1, const value_type &v2) {
    return explicit_type{v1.value_ >> v2};
  }
  friend explicit_type operator>>(const explicit_type &v1, const explicit_type &v2) {
    return explicit_type{v1.value_ >> v2.value_};
  }
  friend explicit_type operator&(const explicit_type &v1, const value_type &v2) {
    return explicit_type{v1.value_ & v2};
  }
  friend explicit_type operator&(const value_type &v1, const explicit_type &v2) {
    return explicit_type{v1 & v2.value_};
  }
  friend explicit_type operator&(const explicit_type &v1, const explicit_type &v2) {
    return explicit_type{v1.value_ & v2.value_};
  }
  friend explicit_type operator|(const explicit_type &v1, const value_type &v2) {
    return explicit_type{v1.value_ | v2};
  }
  friend explicit_type operator|(const value_type &v1, const explicit_type &v2) {
    return explicit_type{v1 | v2.value_};
  }
  friend explicit_type operator|(const explicit_type &v1, const explicit_type &v2) {
    return explicit_type{v1.value_ | v2.value_};
  }
  friend explicit_type operator^(const explicit_type &v1, const value_type &v2) {
    return explicit_type{v1.value_ ^ v2};
  }
  friend explicit_type operator^(const value_type &v1, const explicit_type &v2) {
    return explicit_type{v1 ^ v2.value_};
  }
  friend explicit_type operator^(const explicit_type &v1, const explicit_type &v2) {
    return explicit_type{v1.value_ ^ v2.value_};
  }
  
  //one argument operators:
  friend explicit_type operator~(const explicit_type &v1) {
    return explicit_type{~v1.value_};
  }
  friend explicit_type operator!(const explicit_type &v1) {
    return explicit_type{!v1.value_};
  }
  friend explicit_type operator+(const explicit_type &v1) {
    return explicit_type{+v1.value_};
  }
  friend explicit_type operator-(const explicit_type &v1) {
    return explicit_type{-v1.value_};
  }
  
  //mutating operators:
  friend void operator+=(explicit_type &v1, const explicit_type &v2) {
    v1.value_ += v2.value_;
  }
  friend void operator-=(explicit_type &v1, const explicit_type &v2) {
    v1.value_ -= v2.value_;
  }
  friend void operator*=(explicit_type &v1, const value_type &v2) {
    v1.value_ *= v2;
  }
  friend void operator/=(explicit_type &v1, const value_type &v2) {
    v1.value_ /= v2;
  }
  friend void operator%=(explicit_type &v1, const value_type &v2) {
    v1.value_ %= v2;
  }
  friend void operator<<=(explicit_type &v1, const value_type &v2) {
    v1.value_ <<= v2;
  }
  friend void operator>>=(explicit_type &v1, const value_type &v2) {
    v1.value_ >>= v2;
  }
  friend void operator&=(explicit_type &v1, const value_type &v2) {
    v1.value_ &= v2;
  }
  friend void operator|=(explicit_type &v1, const value_type &v2) {
    v1.value_ |= v2;
  }
  friend void operator^=(explicit_type &v1, const value_type &v2) {
    v1.value_ ^= v2;
  }

  explicit operator value_type() { return value_; }
  const value_type *operator->() const & { return &value_; }
  value_type *operator->() & { return &value_; }

  const value_type& operator*() const & { return value_; }
  value_type& operator*() & { return value_; }

private:
  value_type value_;
};
}  // namespace mj

#endif // jm4r_EXPLICIT_TYPE_H
