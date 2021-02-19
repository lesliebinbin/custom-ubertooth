#pragma once
#include "ubertooth_data_handler.hpp"
#include <map>
#include <string>
#include <tuple>
#include <vector>
extern "C" {
#include <ubertooth/ubertooth.h>
}
namespace space {
std::map<std::string, std::vector<std::string>>
start_ubertooth(int survey_mode, int max_ac_errors, int timeout, uint64_t mac,
                uint64_t pi_id, uint64_t area_id);
} // namespace space

extern "C" namespace space::callback {
  std::tuple<SubmitHandler<space::UbertoothItem>, SubmitHandler<uint32_t>>
  generate_submits_pair(uint64_t mac, uint64_t pi_id, uint64_t area_id);
  // void cb_rx(ubertooth_t * ut, void *args);
};

void my_cb_rx(ubertooth_t *ut, void *args);
