#pragma once
extern "C" {
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ubertooth/ubertooth.h>
#include <ubertooth/ubertooth_control.h>
#include <unistd.h>
}

#include "ubertooth_extension.hpp"
void cb_afh_initial(ubertooth_t *ut, void *args);
void cb_afh_monitor(ubertooth_t *ut, void *args);
void cb_afh_r(ubertooth_t *ut, void *args);
void cb_btle(ubertooth_t *ut, void *args);
void cb_ego(ubertooth_t *ut, void *args __attribute__((unused)));
void cb_rx(ubertooth_t *ut, void *args);
void cb_scan(ubertooth_t *ut, void *args);

// uint64_t mac, pi_id, area_id;

extern "C" namespace space::callback{
  void cb_rx(ubertooth_t *ut, void *args);
             void init_callback(uint64_t mac_, uint64_t pi_id_, uint64_t area_id_);
};
