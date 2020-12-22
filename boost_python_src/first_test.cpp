#include "ubertooth_extension.hpp"
#include <boost/python.hpp>
#include <iostream>
#include <string>
std::string greet() {
  auto &[ubertooth1, survey1] = space::callback::generate_submits_pair();
  auto &[ubertooth2, survey2] = space::callback::generate_submits_pair();
  std::cout << "Hello It is the fucking c++" << std::endl;
  std::cout << &ubertooth1 << std::endl;
  std::cout << &ubertooth2 << std::endl;
  survey1.items.push_back(1);
  survey1.items.push_back(2);
  survey1.items.push_back(3);
  return survey1.submit();
}

BOOST_PYTHON_MODULE(ubertooth_ext) {
  using namespace boost::python;
  def("greet", greet);
  def("start_ubertooth", space::start_ubertooth);
}
