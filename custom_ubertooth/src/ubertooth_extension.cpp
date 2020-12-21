#include "ubertooth_extension.hpp"
#include "ubertooth_custom_callback.hpp"
#include <iostream>
#include <ranges>
#include <stdexcept>
#include <vector>
#include <functional>
#include <tuple>
int space_mac;
int space_pi_id;
int space_area_id;

void space::callback::init_callback(uint64_t mac_, uint64_t pi_id_, uint64_t area_id_){
  space_mac = mac_;
  space_pi_id = pi_id_;
  space_area_id = area_id_;
}

int space::start_ubertooth(int survey_mode, int max_ac_errors, int timeout, uint64_t mac, uint64_t pi_id, uint64_t area_id) {
  callback::init_callback(mac, pi_id, area_id);
  // int survey_mode = 0;
  // auto [ubertooth, survey] = generate_submits_pair();
  int r;
  // int timeout = 0;
  char *end;
  int ubertooth_device = -1;
  btbb_piconet *pn = NULL;
  uint32_t lap = 0;
  uint8_t uap = 0;
  uint16_t channel = 9999;
  ubertooth_t *ut = ubertooth_init();

  // ++survey_mode;
  // max_ac_errors = 0;
  // timeout = 1800;

  r = ubertooth_connect(ut, ubertooth_device);
  if (r < 0) {
    if (ut->devh) {
      throw std::runtime_error("usb_claim_interface error");
    } else
      throw std::runtime_error("could not open Ubertooth device\n");
  }

  r = ubertooth_check_api(ut);
  if (r < 0)
    return 1;

  r = btbb_init(max_ac_errors);
  if (r < 0)
    return r;

  // auto-flush stdout so that wrapper scripts work
  setvbuf(stdout, NULL, _IONBF, 0);
  btbb_init_survey();

  cmd_set_channel(ut->devh, channel);

  /* Clean up on exit. */
  register_cleanup_handler(ut, 0);

  if (timeout)
    ubertooth_set_timeout(ut, timeout);

  // init USB transfer
  r = ubertooth_bulk_init(ut);
  if (r < 0)
    return r;

  r = ubertooth_bulk_thread_start();
  if (r < 0)
    return r;

  // tell ubertooth to send packets
  r = cmd_rx_syms(ut->devh);
  if (r < 0)
    return r;

  // receive and process each packet
  while (!ut->stop_ubertooth) {
    ubertooth_bulk_receive(ut, space::callback::cb_rx, pn);
  }

  ubertooth_bulk_thread_stop();

  ubertooth_stop(ut);

  printf("Survey Results\n");
  while ((pn = btbb_next_survey_result()) != NULL) {
    lap = btbb_piconet_get_lap(pn);
    if (btbb_piconet_get_flag(pn, BTBB_UAP_VALID)) {
      uap = btbb_piconet_get_uap(pn);
      /* Printable version showing that the NAP is unknown */
      printf("??:??:%02X:%02X:%02X:%02X\n", uap, (lap >> 16) & 0xFF,
             (lap >> 8) & 0xFF, lap & 0xFF);
    } else
      printf("??:??:??:%02X:%02X:%02X\n", (lap >> 16) & 0xFF, (lap >> 8) & 0xFF,
             lap & 0xFF);
    // btbb_print_afh_map(pn);
  }
  return 0;
}