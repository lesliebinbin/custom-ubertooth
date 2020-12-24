#pragma once
extern "C" {
#include <ubertooth/ubertooth.h>
}

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

// #include "ubertooth_extension.hpp"
#include "ubertooth_data_handler.hpp"
void cb_afh_initial(ubertooth_t *ut, void *args);
void cb_afh_monitor(ubertooth_t *ut, void *args);
void cb_afh_r(ubertooth_t *ut, void *args);
void cb_btle(ubertooth_t *ut, void *args);
void cb_ego(ubertooth_t *ut, void *args __attribute__((unused)));
void cb_rx(ubertooth_t *ut, void *args);
void cb_scan(ubertooth_t *ut, void *args);
