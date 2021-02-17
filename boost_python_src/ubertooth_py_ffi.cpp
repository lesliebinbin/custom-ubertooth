#include "ubertooth_data_handler.hpp"
#include <iostream>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <string>
#include <vector>
using std::string;
using std::vector;
namespace space {
int start_ubertooth(int survey_mode, int max_ac_errors, int timeout,
                    uint64_t mac, uint64_t pi_id, uint64_t area_id);
};

extern space::SubmitHandler<space::UbertoothItem> *u_handler;
extern space::SubmitHandler<uint32_t> *s_handler;

vector<string> ubertooth_results() { return u_handler->submit(); }

vector<string> survey_results() { return s_handler->submit(); }

int add(int a, int b) { return a + b; }
PYBIND11_MODULE(space_ubertooth, m) {
  m.doc() = "ubertooth binding from c++ to python, fuck it"; // optional module
  m.def("add", add, "A function to start the ubertooth");
  m.def("start_ubertooth", space::start_ubertooth,
        "A function to start the ubertooth");
  m.def("ubertooth_results", ubertooth_results,
        "a function to collect ubertooth data");
  m.def("survey_results", survey_results,
        "a function to collect ubertooth data");
}
