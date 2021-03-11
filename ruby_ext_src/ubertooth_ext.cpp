#include "ubertooth_extension.hpp"
#include <functional>
#include <iostream>
#include <map>
#include <ruby.h>
#include <ruby/thread.h>
#include <string>
#include <tuple>
#include <vector>

#include "rice/Array.hpp"
#include "rice/Class.hpp"
#include "rice/Hash.hpp"
#include "rice/String.hpp"

using namespace Rice;

void *start_my_ubertooth(void *args) {
  auto actual_args = reinterpret_cast<
      std::tuple<int, int, int, uint64_t, uint64_t, uint64_t, Hash *> *>(args);
  auto [survey_mode, max_ac_errors, timeout, mac, pi_id, area_id, hptr] =
      *actual_args;
  std::map<std::string, std::vector<string>> result = space::start_ubertooth(
      survey_mode, max_ac_errors, timeout, mac, pi_id, area_id);
  for (const auto &[key, value] : result) {
    Array a;
    for (auto aIt : value) {
      a.push(aIt);
    }
    hptr->operator[](key) = a;
  }
  return nullptr;
}

Hash start_my_ubertooth_without_gvl(Object self, int survey_mode,
                                    int max_ac_errors, int timeout,
                                    uint64_t mac, uint64_t pi_id,
                                    uint64_t area_id) {
  Hash h;
  auto args = std::make_tuple(survey_mode, max_ac_errors, timeout, mac, pi_id,
                              area_id, &h);
  void *argv = reinterpret_cast<void *>(&args);
  rb_thread_call_without_gvl(start_my_ubertooth, argv, nullptr, nullptr);
  return h;
}

void *get_ubertooth_items(void *array) {
  Array* a = reinterpret_cast<Array *>(array);
  for (auto it : submit_my_ubertooth_items())
    a->push(it);
  return nullptr;
}

// The function implementing the Ruby method
Array get_ubertooth_items_no_gvl(Object self) {
  // First wrap up the input as a pointer.
  // You'll probably want to do some checking on the type of the
  // argument here too.

  // Now call the function without the GVL.
  // It might be worth looking into providing
  // an ubf function here too.
  Array a;
  rb_thread_call_without_gvl(get_ubertooth_items, &a, nullptr, nullptr);
  return a;
}
extern "C" void Init_ubertooth_ext() {
  Class rb_cTest =
      define_class("UbertoothExt")
          .define_method("start_my_ubertooth", start_my_ubertooth_without_gvl)
          .define_method("get_ubertooth_items", get_ubertooth_items_no_gvl);
}
