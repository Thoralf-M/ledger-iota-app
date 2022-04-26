/*
 * flow.h
 *
 *  Created on: 21.10.2020
 *      Author: thomas
 */
#pragma once

#include <stdint.h>

#include "ux.h"

#include "api.h"

#define UNKNOWN 0
#define NEW_ADDRESS 1
#define REMAINDER 2
#define OUTPUT 3

#define LINE_WIDTH 16

#define FLOW_USER_CONFIRM 0
#define FLOW_NEW_ADDRESS 1

typedef enum { FLOW_ACCEPT_REJECT, FLOW_OK } FLOW_TYPES;

typedef unsigned int (*ux_callback_cb_t)(const bagl_element_t *e);
typedef void (*ux_fetch_data)();

typedef void (*accept_cb_t)();
typedef void (*reject_cb_t)();
typedef void (*timeout_cb_t)();

typedef void (*populate_cb_t)();


// struct that contains the data to be displayed on the screen
// during confirming the outputs
typedef struct {
    const API_CTX *api;

    // current index of output displayed
    short flow_outputs_index_current;

    // callbacks
    accept_cb_t accept_cb;
    reject_cb_t reject_cb;
    timeout_cb_t timeout_cb;

    populate_cb_t populate_cb;

    // buffer for nnbnn layout
    char flow_lines[5][LINE_WIDTH + 1];
    int flow_scroll_ypos;

    // buffer for bech32 strings
    char flow_bech32[ADDRESS_SIZE_BECH32 + 1]; // +1 zero terminator

    // total number of lines
    uint8_t number_of_lines;

    // toggles between short and full format of amount
    uint8_t amount_toggle;

    // for UI-100s-timeout
    uint32_t flow_timer_start;

    // flag that indicates the flow is active
    uint8_t flow_active;

    FLOW_TYPES flow_type;
    uint16_t flow_dataset_count;

    uint32_t flow_bip32[BIP32_PATH_LEN];
} flowdata_t;

void flow_main_menu(void);

void flow_init(void);

void flow_confirm_datasets(const API_CTX *api, accept_cb_t accept_cb,
                           reject_cb_t reject_cb, timeout_cb_t timeout_cb,
                           populate_cb_t populate_cb,
                           const uint32_t bip32[BIP32_PATH_LEN],
                           FLOW_TYPES flow_type, uint16_t dataset_count);

void flow_stop(void);

void flow_timer_event(void);

