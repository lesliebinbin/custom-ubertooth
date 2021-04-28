#pragma once
#include <algorithm>
#include <chrono>
#include <iostream>
#include <iterator>
#include <list>
#include <mutex>
#include <nlohmann/json.hpp>
#include <numeric>
#include <string>
#include <utility>
#include <vector>
using std::cout;
using std::endl;
using std::string;
using std::vector;
namespace space {
template <typename Item, int CHUNK_SIZE = 512> struct SubmitHandler {
  std::string type;
  uint64_t mac;
  uint64_t pi_id;
  uint64_t area_id;
  std::list<Item> items;
  std::unique_ptr<std::mutex> mylock = std::make_unique<std::mutex>();

  NLOHMANN_DEFINE_TYPE_INTRUSIVE(SubmitHandler, type, mac, pi_id, area_id);

  // It needs a lock here in order to resolve submitting result conflict
  auto submit() {
    std::lock_guard<std::mutex> guard(*mylock);
    std::vector<Item> temp(items.cbegin(), items.cend());
    auto i_begin = items.begin();
    auto i_end = items.begin();
    std::advance(i_end, temp.size());
    auto result = split_items(temp);
    items.erase(i_begin, i_end);
    return result;
  }

  vector<string> split_items(const vector<Item> &items) {
    using std::chrono::duration_cast;
    using std::chrono::milliseconds;
    using std::chrono::system_clock;
    vector<string> result;
    auto iter = items.begin();
    auto iter_end = items.end();
    while (true) {
      nlohmann::json j;
      nlohmann::to_json(j, *this);
      auto submit_time =
          duration_cast<milliseconds>(system_clock::now().time_since_epoch())
              .count();
      j["submit_time"] = submit_time;
      if (std::distance(iter, iter_end) > CHUNK_SIZE) {
        auto current_iter = iter;
        std::advance(iter, CHUNK_SIZE);
        j["items"] = std::vector<Item>(current_iter, iter);
        result.emplace_back(j.dump());
      } else {
        // j["items"] = items;
        j["items"] = std::vector<Item>(iter, iter_end);
        result.emplace_back(j.dump());
        break;
      }
    }
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

  UbertoothItem(uint32_t systime, uint8_t channel, uint32_t lap, uint32_t err,
                uint32_t clkn, uint32_t clk_offset, int32_t s, int32_t n,
                int32_t snr)
      : systime{systime}, channel{channel}, lap{lap}, err{err}, clkn{clkn},
        clk_offset{clk_offset}, s{s}, n{n}, snr{snr} {}

  NLOHMANN_DEFINE_TYPE_INTRUSIVE(UbertoothItem, systime, channel, lap, err,
                                 clkn, clk_offset, s, n, snr);
};

}; // namespace space
