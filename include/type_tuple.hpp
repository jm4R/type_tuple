// Copyright (C) 2017 - 2018 Mariusz Jaskółka.
//
// Use, modification, and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef jm4r_type_tuple_H
#define jm4r_type_tuple_H

#include <utility>

namespace mj {

namespace detail {

template <typename T> class property_holder {
  using value_type = T;
  value_type val_;

protected:
  property_holder() = default;
  explicit property_holder(const value_type &val) : val_{val} {}
  explicit property_holder(value_type &&val) : val_{std::move(val)} {}
  value_type get() const { return val_; }
  value_type &get() { return val_; }
};

}

template <typename... Params>
class type_tuple : public detail::property_holder<Params>... {
public:
  template <typename... Args>
  explicit type_tuple(Args&&... args)
      : detail::property_holder<Args>(std::forward<Args>(args))... {}

  type_tuple(const type_tuple &) = default;
  type_tuple(type_tuple &) = default;
  type_tuple &operator=(const type_tuple &) = default;

  template <typename T> T get() const { return detail::property_holder<T>::get(); }
  template <typename T> T &get() { return detail::property_holder<T>::get(); }

  template <typename T> type_tuple &set(T &&val) {
    get<T>() = std::forward<T>(val);
    return *this;
  }

  template <typename... Args>
  void set(Args&&... args) {
      using expand = int[];
      expand{0, set_helper(std::forward<Args>(args))...};
  }

private:
  template <typename T> int set_helper(T &&val) {
    get<T>() = std::forward<T>(val);
    return 0;
  }
};

} // namespace mj

#endif // jm4r_type_tuple_H
