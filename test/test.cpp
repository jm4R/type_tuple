#include "../include/explicit_tuple.h"
#include "../include/explicit_type.h"

#include <cassert>
#include <iostream>
#include <memory>
#include <string>
#include <type_traits>

struct test_fixture {

  template <typename T> void test_explicit_type(T testValue) {
    using acceleration = mj::explicit_type<T, class acceleration_tag>;
    using velocity = mj::explicit_type<T, class velocity_tag>;

    acceleration a1{testValue}, a2;
    velocity v;

    static_assert(std::is_convertible<acceleration, acceleration>::value,
                  "same types should be convertible");
    static_assert(!std::is_convertible<acceleration, velocity>::value,
                  "different types shouldn't be explicitly convertible");
    static_assert(!std::is_convertible<T, velocity>::value,
                  "explicit_type shouldn't be explicitly convertible from "
                  "underlying type");
    static_assert(
        std::is_convertible<velocity, T>::value,
        "explicit_type should be explicitly convertible to underlying type");

    assert(testValue == a1);
    assert(T{} == a2);

    a2 = a1;

    assert(testValue == a2);

    v = velocity{testValue};

    assert(testValue == a2);
  }

  void test_explicit_tuple() {
    using use_cache = mj::explicit_type<bool, class use_cache_tag>;
    using cache_size = mj::explicit_type<int, class cache_size_tag>;
    using auto_commit = mj::explicit_type<bool, class auto_commit_tag>;

    using db_options = mj::explicit_tuple<use_cache, cache_size, auto_commit>;

    {
      db_options db{};
      assert(false == db.get<use_cache>());
      assert(false == db.get<auto_commit>());
      assert(0 == db.get<cache_size>());
    }

    {
      db_options db{auto_commit{true}};
      assert(false == db.get<use_cache>());
      assert(true == db.get<auto_commit>());
      assert(0 == db.get<cache_size>());
    }

    {
      db_options db{cache_size{500}, use_cache{true}};
      assert(true == db.get<use_cache>());
      assert(false == db.get<auto_commit>());
      assert(500 == db.get<cache_size>());
    }

    {
      db_options db{cache_size{500}, use_cache{true}, auto_commit{true}};
      assert(true == db.get<use_cache>());
      assert(true == db.get<auto_commit>());
      assert(500 == db.get<cache_size>());
    }

    {
      db_options db{auto_commit{true}, use_cache{true}, cache_size{500}};
      assert(true == db.get<use_cache>());
      assert(true == db.get<auto_commit>());
      assert(500 == db.get<cache_size>());
    }
  }
};

int main() {
  test_fixture test;
  //---
  test.test_explicit_type<char>(5);
  test.test_explicit_type<int>(5);
  test.test_explicit_type<long>(5);
  test.test_explicit_type<unsigned>(5);
  test.test_explicit_type<float>(5.5);
  test.test_explicit_type<double>(5);
  test.test_explicit_type<bool>(true);
  test.test_explicit_type<bool>(true);
  int a;
  test.test_explicit_type<int *>(&a);
  test.test_explicit_type<std::string>("test");
  test.test_explicit_type<std::shared_ptr<int>>(std::make_shared<int>(5));
  enum some_enum { v1, v2 };
  test.test_explicit_type<some_enum>(v2);

  enum class some_enum_class { v1, v2 };
  test.test_explicit_type<some_enum_class>(some_enum_class::v2);
  //---
  test.test_explicit_tuple();

  std::cout << "All tests passed" << std::endl;
}
