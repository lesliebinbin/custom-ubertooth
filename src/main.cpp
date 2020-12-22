#include "ubertooth_extension.hpp"
#include <iostream>
int main(int argc, char *argv[]) {

  int survey_mode = 1;
  int max_ac_errors = 0;
  int timeout = 1800;
  // space::start_ubertooth(survey_mode, max_ac_errors, timeout, 7,8,9);

  auto& [ubertooth1, survey1] = space::callback::generate_submits_pair();
  auto& [ubertooth2, survey2] = space::callback::generate_submits_pair();
  std::cout<<&ubertooth1<<std::endl;
  std::cout<<&ubertooth2<<std::endl;
  return 0;
}
