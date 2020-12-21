#pragma once
#include <nlohmann/json.hpp>
#include <vector>
#include <string>
#include <chrono>
namespace space {
int start_ubertooth(int survey_mode, int max_ac_errors, int timeout, uint64_t mac, uint64_t pi_id, uint64_t area_id);
// auto generate_submits_pair();

template<typename Item>
struct SubmitResult{
  std::vector<Item> items;
  std::string type;
  int64_t submit_time;
  uint64_t mac;
  uint64_t pi_id;
  uint64_t area_id;
  NLOHMANN_DEFINE_TYPE_INTRUSIVE(SubmitResult, items, type, mac, pi_id, area_id);
  std::string submit(){
    using std::chrono::duration_cast;
    using std::chrono::milliseconds;
    using std::chrono::system_clock;
    this->submit_time = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    nlohmann::json j;
    nlohmann::to_json(j, *this);
    auto result = j.dump();
    this->items.clear();
    return result;
  }
};


struct UbertoothItem {
  uint32_t systime;
  uint8_t channel;
  uint32_t lap;
  uint32_t err;
  uint32_t clkn;
  uint32_t clk_offset;
  int32_t s;
  int32_t n;
  int32_t snr;

  NLOHMANN_DEFINE_TYPE_INTRUSIVE(UbertoothItem, systime, channel, lap, err,
                                 clkn, clk_offset, s, n, snr);
};



} // namespace space