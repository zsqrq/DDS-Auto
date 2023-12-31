//
// Created by wz on 23-11-27.
//
#include <utility>
#include <memory>
#include <stdexcept>
#include <string>
#include "boost/test/unit_test.hpp"
#include "boost/fiber/all.hpp"
#include "glog/logging.h"

struct A {
  A() = default;

  A( A const&) = delete;
  A & operator=( A const&) = delete;

  A( A && other) :
      value{ other.value } {
    other.value = 0;
  }

  A & operator=( A && other) {
    if ( this == & other) return * this;
    value = other.value;
    other.value = 0;
    return * this;
  }

  int value{ 0 };
};

struct X {
  int value;

  void foo( int i) {
    value = i;
    LOG(INFO) << "Fiber A::foo() is called";
  }
};

void fn1() {
  LOG(INFO) << "Fiber fn1 is called";
}

int fn2( int i) {
  LOG(INFO) << "Fiber fn2 is called";
  return i;
}

int & fn3( int & i) {
  LOG(INFO) << "Fiber fn3 is called";
  return i;
}

A fn4( A && a) {
  LOG(INFO) << "Fiber fn4 is called";
  return std::forward< A >( a);
}

void test_async_1() {
  boost::fibers::future< void > f1 = boost::fibers::async( boost::fibers::launch::dispatch, fn1);
  BOOST_CHECK( f1.valid() );

  f1.get();
}

void test_async_2() {
  int i = 3;
  boost::fibers::future< int > f1 = boost::fibers::async( boost::fibers::launch::dispatch, fn2, i);
  BOOST_CHECK( f1.valid() );

  BOOST_CHECK( i == f1.get());
}

void test_async_3() {
  int i = 7;
  boost::fibers::future< int& > f1 = boost::fibers::async( boost::fibers::launch::dispatch, fn3, std::ref( i) );
  BOOST_CHECK( f1.valid() );

  BOOST_CHECK( & i == & f1.get());
}

void test_async_4() {
  A a1;
  a1.value = 7;
  boost::fibers::future< A > f1 = boost::fibers::async( boost::fibers::launch::dispatch, fn4, std::move( a1) );
  BOOST_CHECK( f1.valid() );

  A a2 = f1.get();
  BOOST_CHECK( 7 == a2.value);
}

void test_async_5() {
  X x = {0};
  BOOST_CHECK( 0 == x.value);
  boost::fibers::future< void > f1 = boost::fibers::async(
      boost::fibers::launch::dispatch,
      std::bind( & X::foo, std::ref( x), 3) );
  BOOST_CHECK( f1.valid() );

  f1.get();
  BOOST_CHECK( 3 == x.value);
}

void test_async_6() {
  X x = {0};
  BOOST_CHECK( 0 == x.value);
  boost::fibers::future< void > f1 = boost::fibers::async(
      boost::fibers::launch::dispatch,
      std::bind( & X::foo, std::ref( x), std::placeholders::_1), 3);
  BOOST_CHECK( f1.valid() );

  f1.get();
  BOOST_CHECK( 3 == x.value);
}

void test_async_stack_alloc() {
  boost::fibers::future< void > f1 = boost::fibers::async(
      boost::fibers::launch::dispatch,
      std::allocator_arg,
      boost::fibers::fixedsize_stack{},
      fn1);
  BOOST_CHECK( f1.valid() );

  f1.get();
}

void test_async_std_alloc() {
  struct none {};
  boost::fibers::future< void > f1 = boost::fibers::async(
      boost::fibers::launch::dispatch,
      std::allocator_arg,
      boost::fibers::fixedsize_stack{},
      std::allocator< none >{},
      fn1);
  BOOST_CHECK( f1.valid() );

  f1.get();
}


boost::unit_test_framework::test_suite* init_unit_test_suite(int, char*[]) {
  FLAGS_minloglevel = 0;
  FLAGS_alsologtostderr =1;
  google::InitGoogleLogging("Fiber");
  boost::unit_test_framework::test_suite* test =
      BOOST_TEST_SUITE("Boost.Fiber: async test suite");

  test->add(BOOST_TEST_CASE(test_async_1));
  test->add(BOOST_TEST_CASE(test_async_2));
  test->add(BOOST_TEST_CASE(test_async_3));
  test->add(BOOST_TEST_CASE(test_async_4));
  test->add(BOOST_TEST_CASE(test_async_5));
  test->add(BOOST_TEST_CASE(test_async_6));
  test->add(BOOST_TEST_CASE(test_async_stack_alloc));
  test->add(BOOST_TEST_CASE(test_async_std_alloc));
//  test
  return test;
}

