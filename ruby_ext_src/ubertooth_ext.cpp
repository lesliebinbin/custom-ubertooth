#include "ubertooth_extension.hpp"
#include <iostream>

#include "rice/Class.hpp"
#include "rice/String.hpp"

using namespace Rice;

Object test_hello(Object /* self */) {
  auto &[ubertooth1, survey1] = space::callback::generate_submits_pair();
  auto &[ubertooth2, survey2] = space::callback::generate_submits_pair();
  std::cout << &ubertooth1 << std::endl;
  std::cout << &ubertooth2 << std::endl;
  String str("hello, world");
  return str;
}

extern "C" void Init_ubertooth_ext() {
  Class rb_cTest =
      define_class("UbertoothExt")
          .define_method("hello", &test_hello)
          .define_method("start_ubertooth", &space::start_ubertooth);
}
