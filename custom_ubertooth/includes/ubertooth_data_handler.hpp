#pragma once
#include <algorithm>
#include <chrono>
#include <iterator>
#include <nlohmann/json.hpp>
#include <string>
#include <utility>
#include <vector>
using std::string;
using std::vector;
namespace space {

template <typename Item, int CHUNK_SIZE = 200> struct SubmitHandler {
  std::vector<Item> items;
  std::string type;
  uint64_t mac;
  uint64_t pi_id;
  uint64_t area_id;
  int64_t current_length;
  NLOHMANN_DEFINE_TYPE_INTRUSIVE(SubmitHandler, type, mac, pi_id, area_id);
  // std::string submit() {
  //   using std::chrono::duration_cast;
  //   using std::chrono::milliseconds;
  //   using std::chrono::system_clock;
  //   this->submit_time =
  //       duration_cast<milliseconds>(system_clock::now().time_since_epoch())
  //           .count();
  //   nlohmann::json j;
  //   nlohmann::to_json(j, *this);
  //   current_length = items.size();
  //   auto result = j.dump();
  //   this->items.clear();
  //   return result;
  // }

  auto submit() {
    std::vector<Item> temp;
    temp.reserve(CHUNK_SIZE);
    std::copy(items.cbegin(), items.cend(), temp.begin());
    auto result = split_items(temp);
    current_length = result.size();
    return result;
  }
  vector<string> split_items(const vector<Item> &items) {
    using std::chrono::duration_cast;
    using std::chrono::milliseconds;
    using std::chrono::system_clock;
    vector<string> result;
    auto iter = items.begin();
    while (true) {
      nlohmann::json j;
      nlohmann::to_json(j, *this);
      auto submit_time =
          duration_cast<milliseconds>(system_clock::now().time_since_epoch())
              .count();
      j["submit_time"] = submit_time;
      if (std::distance(iter, items.end()) > CHUNK_SIZE) {
        auto current_iter = iter;
        std::advance(iter, CHUNK_SIZE);
        j["items"] = std::vector<Item>(current_iter, iter);
        result.emplace_back(j.dump());
      } else {
        j["items"] = std::vector<Item>(iter, items.end());
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

  NLOHMANN_DEFINE_TYPE_INTRUSIVE(UbertoothItem, systime, channel, lap, err,
                                 clkn, clk_offset, s, n, snr);
};

}; // namespace space
