// Copyright (C) 2017 - 2018 Andrzej Krzemienski.
//
// Use, modification, and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef jm4r_PROPERTIES_H
#define jm4r_PROPERTIES_H

#include <utility>

namespace mj {

template <typename T> class property_holder {
  using value_type = typename std::remove_const<T>::type;
  value_type val_;

protected:
  property_holder() = default;
  property_holder(const value_type &val) : val_{val} {}
  property_holder(value_type &&val) : val_{std::move(val)} {}
  value_type get() const { return val_; }
  value_type &get() { return val_; }
};

template <typename... Params>
class explicit_tuple : public property_holder<Params>... {
public:
  template <typename... Args>
  explicit_tuple(Args... args)
      : property_holder<Args>(std::forward<Args>(args))... {}

  template <typename T> T get() const { return property_holder<T>::get(); }
  template <typename T> T &get() { return property_holder<T>::get(); }
};

} // namespace mj

#endif // jm4r_PROPERTIES_H
