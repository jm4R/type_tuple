// Copyright (C) 2017 - 2018 Andrzej Krzemienski.
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

  friend bool operator==(const value_type &v1, const explicit_type &v2) {
    return v1 == v2.value_;
  }
  friend bool operator!=(const value_type &v1, const explicit_type &v2) {
    return v1 != v2.value_;
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
