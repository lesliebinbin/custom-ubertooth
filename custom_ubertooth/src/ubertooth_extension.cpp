#include "ubertooth_extension.hpp"
#include "ubertooth_custom_callback.hpp"
#include <iostream>
#include <list>
#include <map>
#include <set>
#include <stdexcept>
#include <string>
#include <vector>
using std::map;
using std::string;
using std::vector;
space::SubmitHandler<space::UbertoothItem> *u_handler;
extern std::set<void *> gc;
map<string, vector<string>>
space::start_ubertooth(int survey_mode, int max_ac_errors, int timeout,
                       uint64_t mac, uint64_t pi_id, uint64_t area_id) {
  SubmitHandler<UbertoothItem> ubertooth_submit_handler =
      space::SubmitHandler<space::UbertoothItem>{"ubertooth", mac, pi_id,
                                                 area_id};
  SubmitHandler<unsigned int> survey_submit_handler =
      space::SubmitHandler<uint32_t>{"survey", mac, pi_id, area_id};
  u_handler = &ubertooth_submit_handler;
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
    // return 1;
    return {};

  r = btbb_init(max_ac_errors);
  if (r < 0)
    // return r;
    return {};

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
    // return r;
    return {};

  // gc.insert(ut->rx_xfer);

  r = ubertooth_bulk_thread_start();
  if (r < 0)
    // return r;
    return {};

  // tell ubertooth to send packets
  r = cmd_rx_syms(ut->devh);
  if (r < 0)
    // return r;
    return {};

  // receive and process each packet
  while (!ut->stop_ubertooth) {
    std::tuple<space::SubmitHandler<space::UbertoothItem> *, btbb_piconet *>
        item = std::make_tuple(&ubertooth_submit_handler, pn);
    ubertooth_bulk_receive(ut, my_cb_rx, reinterpret_cast<void *>(&item));
  }

  ubertooth_bulk_thread_stop();

  ubertooth_stop(ut);

  u_handler = nullptr;

  printf("Survey Results\n");
  // while ((pn = btbb_next_survey_result()) != NULL) {
  while ((pn = my_btbb_next_survey_result()) != NULL) {
    lap = btbb_piconet_get_lap(pn);
    uint32_t result = 0;
    if (btbb_piconet_get_flag(pn, BTBB_UAP_VALID)) {
      uap = btbb_piconet_get_uap(pn);
      /* Printable version showing that the NAP is unknown */
      printf("??:??:%02X:%02X:%02X:%02X\n", uap, (lap >> 16) & 0xFF,
             (lap >> 8) & 0xFF, lap & 0xFF);
      result |= lap;
      result |= (uap << 16);

    } else {
      printf("??:??:??:%02X:%02X:%02X\n", (lap >> 16) & 0xFF, (lap >> 8) & 0xFF,
             lap & 0xFF);
      // btbb_print_afh_map(pn);
      result |= lap;
    }
    survey_submit_handler.items.push_back(result);
  }

  delete_all();
  auto final_survey_result = survey_submit_handler.submit();
  auto final_ubertooth_result = ubertooth_submit_handler.submit();
  gc.insert(ut);
  gc.insert(ut->fifo);
  // gc.insert(ut->devh);
  // gc.insert(ut->h_pcap_bredr);
  // gc.insert(ut->h_pcap_le);
  // gc.insert(ut->h_pcapng_bredr);
  // gc.insert(ut->h_pcapng_le);
  for (auto s : gc) {
    cout << "the address of s is " << s << endl;
    if (s != nullptr)
      free(s);
  }
  gc.clear();
  // libusb_free_transfer(ut->rx_xfer);
  return {{"survey_result", final_survey_result},
          {"ubertooth_result", final_ubertooth_result}};
}
