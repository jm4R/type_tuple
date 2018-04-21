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

  void test_size() {
    enum some_enum { v1, v2 };
    enum class some_enum_class { v1, v2 };

    using t01 = mj::explicit_type<char, class some_tag>;
    static_assert(sizeof(char) == sizeof(t01),
                  "size of underlying type should equal");
    using t02 = mj::explicit_type<int, class some_tag>;
    static_assert(sizeof(int) == sizeof(t02),
                  "size of underlying type should equal");
    using t03 = mj::explicit_type<long, class some_tag>;
    static_assert(sizeof(long) == sizeof(t03),
                  "size of underlying type should equal");
    using t04 = mj::explicit_type<unsigned, class some_tag>;
    static_assert(sizeof(unsigned) == sizeof(t04),
                  "size of underlying type should equal");
    using t05 = mj::explicit_type<float, class some_tag>;
    static_assert(sizeof(float) == sizeof(t05),
                  "size of underlying type should equal");
    using t06 = mj::explicit_type<double, class some_tag>;
    static_assert(sizeof(double) == sizeof(t06),
                  "size of underlying type should equal");
    using t07 = mj::explicit_type<bool, class some_tag>;
    static_assert(sizeof(bool) == sizeof(t07),
                  "size of underlying type should equal");
    using t08 = mj::explicit_type<int *, class some_tag>;
    static_assert(sizeof(int *) == sizeof(t08),
                  "size of underlying type should equal");
    using t09 = mj::explicit_type<std::string, class some_tag>;
    static_assert(sizeof(std::string) == sizeof(t09),
                  "size of underlying type should equal");
    using t10 = mj::explicit_type<std::shared_ptr<int>, class some_tag>;
    static_assert(sizeof(std::shared_ptr<int>) == sizeof(t10),
                  "size of underlying type should equal");
    using t11 = mj::explicit_type<some_enum, class some_tag>;
    static_assert(sizeof(some_enum) == sizeof(t11),
                  "size of underlying type should equal");
    using t12 = mj::explicit_type<some_enum_class, class some_tag>;
    static_assert(sizeof(some_enum_class) == sizeof(t12),
                  "size of underlying type should equal");

    struct plain_data {
      char v01;
      int v02;
      long v03;
      unsigned v04;
      float v05;
      double v06;
      bool v07;
      int *v08;
      std::string v09;
      std::shared_ptr<int> v10;
      some_enum v11;
      some_enum_class v12;
    };

    using tuple_data = mj::explicit_tuple<t01, t02, t03, t04, t05, t06, t07,
                                          t08, t09, t10, t11, t12>;

    static_assert(
        sizeof(plain_data) == sizeof(tuple_data),
        "size of tuple should be the same as size of plain data struct");
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
  test.test_explicit_type<bool>(false);
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
  test.test_size();

  std::cout << "All tests passed" << std::endl;
}
