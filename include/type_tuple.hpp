// Copyright (C) 2017 - 2019 Mariusz Jaskółka.
//
// Use, modification, and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef jm4r_type_tuple_H
#define jm4r_type_tuple_H

#include <utility>

#if __cplusplus >= 201400L
#define MJ_CONSTEXPR14 constexpr
#else
#define MJ_CONSTEXPR14
#endif

namespace mj
{

namespace detail
{
    template < typename T > class property_holder
    {
        using value_type = T;
        value_type val_;

    protected:
        constexpr property_holder() = default;
        constexpr explicit property_holder(const value_type& val) : val_{ val }
        {
        }
        constexpr explicit property_holder(value_type&& val) noexcept(
            std::is_nothrow_move_constructible< T >::value)
        : val_{ std::move(val) }
        {
        }
        constexpr value_type get() const { return val_; }
        MJ_CONSTEXPR14 value_type& get() { return val_; }
    };

    template < typename T, typename... Args > struct first_type
    {
        using type = T;
    };

    template < typename T, typename... Args >
    using prefer_std_constructors = std::enable_if< sizeof...(Args) != 1
        || !std::is_same< T,
               typename std::decay<
                   typename first_type< Args... >::type >::type >::value >;
}

template < typename... Params >
class type_tuple : public detail::property_holder< Params >...
{
public:
    constexpr explicit type_tuple() = default;

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wreorder"
#elif defined(_MSC_VER)
#endif
    template < typename... Args,
        typename detail::prefer_std_constructors< type_tuple,
            Args... >::type* = nullptr >
    constexpr explicit type_tuple(Args&&... args)
    : detail::property_holder< Args >(std::forward< Args >(args))...
    {
    }
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic pop
#elif defined(_MSC_VER)
#endif

    constexpr type_tuple(const type_tuple&) = default;
    constexpr type_tuple(type_tuple&&) noexcept = default;
    MJ_CONSTEXPR14 type_tuple& operator=(const type_tuple&) = default;

    template < typename T > constexpr T get() const
    {
        return detail::property_holder< T >::get();
    }
    template < typename T > MJ_CONSTEXPR14 T& get()
    {
        return detail::property_holder< T >::get();
    }

    template < typename T > MJ_CONSTEXPR14 type_tuple& set(T&& val)
    {
        get< T >() = std::forward< T >(val);
        return *this;
    }

    template < typename... Args > MJ_CONSTEXPR14 void set(Args&&... args)
    {
        using expand = int[];
        (void)expand{ 0, set_helper(std::forward< Args >(args))... };
    }

private:
    template < typename T > MJ_CONSTEXPR14 int set_helper(T&& val)
    {
        get< T >() = std::forward< T >(val);
        return 0;
    }
};

} // namespace mj

#undef MJ_CONSTEXPR14

#endif // jm4r_type_tuple_H
