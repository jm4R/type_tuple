# type_tuple

This library contains:

* opaque typedef's – `explicit_type`;
* tuple indexed by type, instead of standard numeric-index based – `type_tuple`.

## Problem introduction

Standard, index-based tuples requires us to remember or constantly checking out what specific index stands for. Let's see an example:

```c++
using db_options = std::tuple<bool /*auto_commit*/, bool /*use_cache*/, int /*cache_size*/>;

//usage:
db_options options{false, true, 500};
auto db = open_db(options);
```

This example is pretty ugly as passing list of raw values to function causes poorly readable code.
Of course in this particular example we would rather develop a structure containing database options.
Possibly the best option would be to use [named parameters](https://en.wikipedia.org/wiki/Named_parameter). Unfortunately C++ itself does not handle that feature.
Please note that very similar (but not the same) feature comes with C++20's [designated initializers](http://en.cppreference.com/w/cpp/language/aggregate_initialization).

## The proposed solution

Let's see the example with database, rewritten using `type_tuple` library:

```c++
using use_cache = mj::explicit_type<bool, class use_cache_tag>;
using cache_size = mj::explicit_type<int, class cache_size_tag>;
using auto_commit = mj::explicit_type<bool, class auto_commit_tag>;

using db_options = mj::type_tuple<use_cache, cache_size, auto_commit>;


//usage:
db_options options{auto_commit{false}, cache_size{500}, use_cache{true}};
auto db = open_db(options);
```

Let's see what happens here.
At first, we declare each option type.
All of those has unique tag at template parameter list, just to make each of them having unique types.
Then we declare the tuple itself. The `type_tuple` is a variadic template, but – unlike `std::tuple` all types have to be unique.
What for? We can see the answer when we see the tuple usage. The constructor arguments are binded by a type, not by an order.

This means that all of following statements are the same:

```c++
db_options options{auto_commit{false}, cache_size{500}, use_cache{true}};
db_options options{auto_commit{false}, use_cache{true}, cache_size{500}};
db_options options{cache_size{500}, auto_commit{false}, use_cache{true}};
db_options options{cache_size{500}, use_cache{true}, auto_commit{false}};
db_options options{use_cache{true}, cache_size{500}, auto_commit{false}};
db_options options{use_cache{true}, auto_commit{false}, cache_size{500}};
```

What is more, we don't have to set every value, but just leave it default-constructed:

```c++
db_options options{auto_commit{true}};
assert(0 == options.get<cache_size>());
assert(false == options.get<use_cache>());
```

this example also shows the getter usage.

## What this library is, and what is not
This library is not a *"better tuple"* and never will be.
The definition of such tuple is more complicated, and are considered to be used in very different contexts.
The first idea of name of this library was `properties`,
as it was needed for setting properties for initialization of some other libraries in more expressive way.
So this is rather a hacky workaround for lack of named parameters feature in C++ language.

The `explicit_type` purpose is very similar to [BOOST_STRONG_TYPEDEF](https://www.boost.org/doc/libs/1_67_0/libs/serialization/doc/strong_typedef.html).
Is it that bad? Boost libraries widely uses macros so I will not give you an answer, just refer to [Bjarne Stroustrup thoughts about using macros](http://www.stroustrup.com/bs_faq2.html#macro).

Please note that also [designated initializers](http://en.cppreference.com/w/cpp/language/aggregate_initialization)
from C++20 functionality differs from this libraries purposes – it doesn't support mixed order of parameters,
it's also limited to an object constructors so no appliable to a ordinary functions/member functions whereas this library could be applied to variadic templated functions.

## Known limitations
1. `explicit_type` doesn't support arrays (and probably never will, use `std::array` instead)
2. `explicit_type` doesn't support references (**TO ANALYSE**)
3. default values for parameter is always default-constructed (**TODO**)
4. it is not constrexpr, but possibly could be (**TODO**)
5. it is early version of it, so a bug can happen (please inform me)

## Installation
It is a C++11 header-only library. Requires C++11 support

## License
Distributed under the [Boost Software License, Version 1.0](http://www.boost.org/LICENSE_1_0.txt).

## Acknowledgements
This library was inspired by Andrzej Krzemiński's [`explicit`](https://github.com/akrzemi1/explicit) library, especially [`tagged_bool`](https://github.com/akrzemi1/explicit#tool-tagged_bool) part of it and is extension of the idea.