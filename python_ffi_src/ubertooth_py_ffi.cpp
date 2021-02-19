#include "ubertooth_data_handler.hpp"
#include <iostream>
#include <map>
#include <pybind11/embed.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <string>
#include <vector>
using std::string;
using std::vector;
namespace space {
std::map<std::string, std::vector<string>>
start_ubertooth(int survey_mode, int max_ac_errors, int timeout, uint64_t mac,
                uint64_t pi_id, uint64_t area_id);
};

extern space::SubmitHandler<space::UbertoothItem> *u_handler;

std::map<std::string, std::vector<string>>
start_the_ubertooth(int survey_mode, int max_ac_errors, int timeout,
                    uint64_t mac, uint64_t pi_id, uint64_t area_id) {
  pybind11::gil_scoped_release gil;
  return space::start_ubertooth(survey_mode, max_ac_errors, timeout, mac, pi_id,
                                area_id);
}

vector<string> ubertooth_results() {
  pybind11::gil_scoped_release gil;
  if (u_handler == nullptr)
    return {};
  return u_handler->submit();
}

vector<int> vector_to_py_list() { return vector<int>{1, 2, 3, 4, 5, 6, 7}; }

vector<string> v_str_to_py_l(int num, string element) {
  auto result = vector<string>(num);
  std::fill(result.begin(), result.end(), element);
  return result;
}

int add(int a, int b) { return a + b; }
PYBIND11_MODULE(space_ubertooth, m) {
  m.doc() = "ubertooth binding from c++ to python, fuck it"; // optional module
  m.def("add", add, "A function to start the ubertooth");
  // m.def("start_ubertooth", space::start_ubertooth,
  //       "A function to start the ubertooth");

  m.def("start_ubertooth", start_the_ubertooth,
        "A function to start the ubertooth");
  m.def("ubertooth_results", ubertooth_results,
        "a function to collect ubertooth data");
  m.def("vector_to_py_list", vector_to_py_list,
        "c++ vector convert to py list automatically");
  m.def("v_str_to_py_l", v_str_to_py_l, "c++ vec of string to py list");
}
