// #include "ubertooth_extension.hpp"
#include <boost/python.hpp>
#include <iostream>
#include <string>
namespace space{
int start_ubertooth(int survey_mode, int max_ac_errors, int timeout,
                    uint64_t mac, uint64_t pi_id, uint64_t area_id);
};


BOOST_PYTHON_MODULE(ubertooth_ext) {
  using namespace boost::python;
  def("start_ubertooth", space::start_ubertooth);
}
