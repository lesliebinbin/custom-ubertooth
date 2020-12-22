#include "ubertooth_extension.hpp"
#include <boost/python.hpp>
#include <iostream>
#include <string>

BOOST_PYTHON_MODULE(ubertooth_ext) {
  using namespace boost::python;
  def("start_ubertooth", space::start_ubertooth);
}
