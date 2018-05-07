# explicit_type

## Declare own instantiation and object

One can easy declare a variable of some `explicit_type`:

```c++
mj::explicit_type<int, class cache_size_tag> db_cache_size{500};
```

but such usage is not use is not convenient. Better (and suggested) way is to always declare instantiation

```c++
using use_cache = mj::explicit_type<int, class cache_size_tag>;
use_cache db_cache_size{500};
```

## Setting and getting raw value

```c++
using use_cache = mj::explicit_type<int, class cache_size_tag>;
use_cache db_cache_size;
db_cache_size = use_cache{500}; //set
int copy1 = static_cast<int>(db_cache_size); //get
int copy2 = *db_cache_size; //get
int& ref = *db_cache_size; //get
```

## Underlying objects members

By `operator ->`

```c++
using use_cache = mj::explicit_type<std::string, class cache_size_tag>;
use_cache db_cache_size;
db_cache_size = use_cache{"500kB"};
std::cout << "Cache size is configured to: " << db_cache_size->c_str() << std::endl;
```

# explicit_tuple – simple usage

## Declare own instantiation and object

```c++
using use_cache = mj::explicit_type<bool, class use_cache_tag>;
using cache_size = mj::explicit_type<int, class cache_size_tag>;
using auto_commit = mj::explicit_type<bool, class auto_commit_tag>;

using db_options = mj::explicit_tuple<use_cache, cache_size, auto_commit>;
```

## Setting values

```c++
//in constructor – order-agnostic
db_options options{ auto_commit{true}, use_cache{false} };

//by multi-setter – also order-agnostic
options.set( use_cache{true}, cache_size{500} );

//by reference-getter
auto_commit ac{false};
options.get<auto_commit>() = ac;
```

## Getting values

```c++
//by simple getter
auto_commit ac = options.get<auto_commit>();

//also as a reference
auto& uc = options.get<use_cache>();

//get raw value
bool ac_r = *options.get<auto_commit>();

//conversions (explicit) are avaliable
if (options.get<use_cache>())
    std::cout << "using cache..." << std::endl;
```

# explicit_tuple – good practice

It is always good to hide implementation from the target user
of our class and show him what is important only.
Let's see simple example how one may prepare class with `explicit_tuple` as options:

```c++
class database {
public:
  struct options { //(1)
    using use_cache = mj::explicit_type<bool, class use_cache_tag>;
    using cache_size = mj::explicit_type<int, class cache_size_tag>;
    using auto_commit = mj::explicit_type<bool, class auto_commit_tag>;
  };

  // constructor with options:
  template <typename... Opts> //(2)
  explicit database(std::string url, Opts... opts)
      : options_(std::forward<Opts>(opts)...) {
    // somehow use url (it also could be a part of options)
  }

  //...
  // some other constructors and database stuff here
  //...
private:
  using db_options = mj::explicit_tuple<options::use_cache, options::cache_size,
                                        options::auto_commit>;
  db_options options_;
};
```
And usage:

```c++
database db{ //(3)
             "172.0.0.1:4321",
             database::options::auto_commit{true},
             database::options::cache_size{500},
             database::options::use_cache{true}
           };
```

1. I colected all possible options in one struct – it is not necessary but
it was my whim as when a class user write `database::options::`,
a good IDE will list him all avaliable options that this class support?
Isn't it wonderful? I know, some people would argue...

2. I wrote variadic–templated constructor to make user comfortable not
forcing him to instantiate `database::db_options` object himself. 

3. And finally the usage – (yes, I know I will repeat myself) user can choose an option
he likes and in order that he likes. And let the rest be default–constructed.
**One note here:** The types without default constructor has to be set here to avoid compilers errors.















