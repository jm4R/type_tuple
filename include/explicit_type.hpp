// Copyright (C) 2017 - 2019 Mariusz Jaskółka.
//
// Use, modification, and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef jm4r_EXPLICIT_TYPE_H
#define jm4r_EXPLICIT_TYPE_H

#include <type_traits>
#include <utility>

#if __cplusplus >= 201400L
#define MJ_CONSTEXPR14 constexpr
#else
#define MJ_CONSTEXPR14
#endif

namespace mj
{

template < typename T, typename Tag > class explicit_type
{
public:
    using value_type = T;

public:
    constexpr explicit_type() : value_{} {}
    constexpr explicit explicit_type(const value_type& v) : value_(v) {}
    constexpr explicit explicit_type(value_type&& v) noexcept(std::is_nothrow_move_constructible<T>::value) : value_{ std::move(v) } {}
    constexpr explicit_type(const explicit_type&) = default;
    constexpr explicit_type(explicit_type&&) noexcept(std::is_nothrow_move_constructible<T>::value) = default;
    MJ_CONSTEXPR14 explicit_type& operator=(const explicit_type&) = default;
    MJ_CONSTEXPR14 explicit_type& operator=(explicit_type&&) noexcept(std::is_nothrow_move_constructible<T>::value) = default;
    constexpr bool operator==(explicit_type v) const { return v.value_ == value_; }
    constexpr bool operator!=(explicit_type v) const { return v.value_ != value_; }

    // logical operators:
    friend constexpr bool operator==(const value_type& v1, const explicit_type& v2)
    {
        return v1 == v2.value_;
    }
    friend constexpr bool operator==(const explicit_type& v1, const value_type& v2)
    {
        return v1.value_ == v2;
    }
    friend constexpr bool operator!=(const value_type& v1, const explicit_type& v2)
    {
        return v1 != v2.value_;
    }
    friend constexpr bool operator!=(const explicit_type& v1, const value_type& v2)
    {
        return v1.value_ != v2;
    }
    friend constexpr bool operator<(const value_type& v1, const explicit_type& v2)
    {
        return v1 < v2.value_;
    }
    friend constexpr bool operator<(const explicit_type& v1, const value_type& v2)
    {
        return v1.value_ < v2;
    }
    friend constexpr bool operator<=(const value_type& v1, const explicit_type& v2)
    {
        return v1 <= v2.value_;
    }
    friend constexpr bool operator<=(const explicit_type& v1, const value_type& v2)
    {
        return v1.value_ <= v2;
    }
    friend constexpr bool operator>(const value_type& v1, const explicit_type& v2)
    {
        return v1 > v2.value_;
    }
    friend constexpr bool operator>(const explicit_type& v1, const value_type& v2)
    {
        return v1.value_ > v2;
    }
    friend constexpr bool operator>=(const value_type& v1, const explicit_type& v2)
    {
        return v1 >= v2.value_;
    }
    friend constexpr bool operator>=(const explicit_type& v1, const value_type& v2)
    {
        return v1.value_ >= v2;
    }

    // arithmetic operators:
    friend constexpr explicit_type operator+(
        const explicit_type& v1, const explicit_type& v2)
    {
        return explicit_type{ v1.value_ + v2.value_ };
    }
    friend constexpr explicit_type operator-(
        const explicit_type& v1, const explicit_type& v2)
    {
        return explicit_type{ v1.value_ - v2.value_ };
    }
    friend constexpr explicit_type operator*(
        const value_type& v1, const explicit_type& v2)
    {
        return explicit_type{ v1 * v2.value_ };
    }
    friend constexpr explicit_type operator*(
        const explicit_type& v1, const value_type& v2)
    {
        return explicit_type{ v1.value_ * v2 };
    }
    friend constexpr explicit_type operator/(
        const explicit_type& v1, const value_type& v2)
    {
        return explicit_type{ v1.value_ / v2 };
    }
    friend constexpr value_type operator/(
        const explicit_type& v1, const explicit_type& v2)
    {
        return v1.value_ / v2.value_;
    }
    friend constexpr value_type operator%(const explicit_type& v1, const value_type& v2)
    {
        return value_type{ v1.value_ % v2 };
    }

    // bit operators:
    friend constexpr explicit_type operator<<(
        const explicit_type& v1, const value_type& v2)
    {
        return explicit_type{ v1.value_ << v2 };
    }
    friend constexpr explicit_type operator<<(
        const explicit_type& v1, const explicit_type& v2)
    {
        return explicit_type{ v1.value_ << v2.value_ };
    }
    friend constexpr explicit_type operator>>(
        const explicit_type& v1, const value_type& v2)
    {
        return explicit_type{ v1.value_ >> v2 };
    }
    friend constexpr explicit_type operator>>(
        const explicit_type& v1, const explicit_type& v2)
    {
        return explicit_type{ v1.value_ >> v2.value_ };
    }
    friend constexpr explicit_type operator&(
        const explicit_type& v1, const value_type& v2)
    {
        return explicit_type{ v1.value_ & v2 };
    }
    friend constexpr explicit_type operator&(
        const value_type& v1, const explicit_type& v2)
    {
        return explicit_type{ v1 & v2.value_ };
    }
    friend constexpr explicit_type operator&(
        const explicit_type& v1, const explicit_type& v2)
    {
        return explicit_type{ v1.value_ & v2.value_ };
    }
    friend constexpr explicit_type operator|(
        const explicit_type& v1, const value_type& v2)
    {
        return explicit_type{ v1.value_ | v2 };
    }
    friend constexpr explicit_type operator|(
        const value_type& v1, const explicit_type& v2)
    {
        return explicit_type{ v1 | v2.value_ };
    }
    friend constexpr explicit_type operator|(
        const explicit_type& v1, const explicit_type& v2)
    {
        return explicit_type{ v1.value_ | v2.value_ };
    }
    friend constexpr explicit_type operator^(
        const explicit_type& v1, const value_type& v2)
    {
        return explicit_type{ v1.value_ ^ v2 };
    }
    friend constexpr explicit_type operator^(
        const value_type& v1, const explicit_type& v2)
    {
        return explicit_type{ v1 ^ v2.value_ };
    }
    friend constexpr explicit_type operator^(
        const explicit_type& v1, const explicit_type& v2)
    {
        return explicit_type{ v1.value_ ^ v2.value_ };
    }

    // one argument operators:
    friend constexpr explicit_type operator~(const explicit_type& v1)
    {
        return explicit_type{ ~v1.value_ };
    }
    friend constexpr explicit_type operator!(const explicit_type& v1)
    {
        return explicit_type{ !v1.value_ };
    }
    friend constexpr explicit_type operator+(const explicit_type& v1)
    {
        return explicit_type{ +v1.value_ };
    }
    friend constexpr explicit_type operator-(const explicit_type& v1)
    {
        return explicit_type{ -v1.value_ };
    }

    // mutating operators:
    friend MJ_CONSTEXPR14 void operator+=(explicit_type& v1, const explicit_type& v2)
    {
        v1.value_ += v2.value_;
    }
    friend MJ_CONSTEXPR14 void operator-=(explicit_type& v1, const explicit_type& v2)
    {
        v1.value_ -= v2.value_;
    }
    friend MJ_CONSTEXPR14 void operator*=(explicit_type& v1, const value_type& v2)
    {
        v1.value_ *= v2;
    }
    friend MJ_CONSTEXPR14 void operator/=(explicit_type& v1, const value_type& v2)
    {
        v1.value_ /= v2;
    }
    friend MJ_CONSTEXPR14 void operator%=(explicit_type& v1, const value_type& v2)
    {
        v1.value_ %= v2;
    }
    friend MJ_CONSTEXPR14 void operator<<=(explicit_type& v1, const value_type& v2)
    {
        v1.value_ <<= v2;
    }
    friend MJ_CONSTEXPR14 void operator>>=(explicit_type& v1, const value_type& v2)
    {
        v1.value_ >>= v2;
    }
    friend MJ_CONSTEXPR14 void operator&=(explicit_type& v1, const value_type& v2)
    {
        v1.value_ &= v2;
    }
    friend MJ_CONSTEXPR14 void operator|=(explicit_type& v1, const value_type& v2)
    {
        v1.value_ |= v2;
    }
    friend MJ_CONSTEXPR14 void operator^=(explicit_type& v1, const value_type& v2)
    {
        v1.value_ ^= v2;
    }

    constexpr explicit operator value_type() const { return value_; }
    constexpr const value_type* operator->() const& { return &value_; }
    value_type* operator->() & { return &value_; }

    constexpr const value_type& operator*() const& { return value_; }
    value_type& operator*() & { return value_; }

private:
    value_type value_;
};
} // namespace mj

#undef MJ_CONSTEXPR14

#endif // jm4r_EXPLICIT_TYPE_H
