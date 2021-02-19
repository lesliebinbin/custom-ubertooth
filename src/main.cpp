#include "ubertooth_data_handler.hpp"
#include <chrono>
#include <iostream>
#include <map>
#include <string>
#include <thread>
using std::string;
using std::vector;
namespace space {

std::map<std::string, std::vector<string>>
start_ubertooth(int survey_mode, int max_ac_errors, int timeout, uint64_t mac,
                uint64_t pi_id, uint64_t area_id);
};

extern space::SubmitHandler<space::UbertoothItem> *u_handler;
void func1() {
    int survey_mode = 1;
    int max_ac_errors = 0;
    int timeout = 15;
    auto result =
        space::start_ubertooth(survey_mode, max_ac_errors, timeout, 7, 8, 9);
    for (auto &kv : result) {
      std::cout << kv.first << std::endl;
      for (auto &r : kv.second) {
        std::cout << r << std::endl;
      }
    }
}
void func2() {
  while (true) {
    std::this_thread::sleep_for(std::chrono::seconds(5));
    if (u_handler == nullptr)
      continue;
    auto result = u_handler->submit();
    for (auto &r : result) {
      std::cout << r << std::endl;
    }
  }
}
int main(int argc, char *argv[]) {
  func1();
  return 0;
}
