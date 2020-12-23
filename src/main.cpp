#include <iostream>

namespace space {
int start_ubertooth(int survey_mode, int max_ac_errors, int timeout,
                    uint64_t mac, uint64_t pi_id, uint64_t area_id);
};
int main(int argc, char *argv[]) {

  int survey_mode = 1;
  int max_ac_errors = 0;
  int timeout = 1800;
  // space::start_ubertooth(survey_mode, max_ac_errors, timeout, 7,8,9);

  return 0;
}
