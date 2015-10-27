#pragma once

#include <pebble.h>
#include "app_data.h"
#include "schedule.h"

#define SCHEDULE_NUM_MAX (10)
#define SCHEDULE_INDEX_UNDEF (-1)
#define APP_SYNC_BUFFER_SIZE (2048)

struct AppData{
  struct {
    /// Sync with Pebble Mobile app
    AppSync sync;
    /// Load timer
    AppTimer *ldtmr;
    /// Communication buffer
    uint8_t buffer[APP_SYNC_BUFFER_SIZE];
  } sync;
  /// Callbacks
  AppDataCallbacks callbacks;
  int schedule_index;
  Schedule *schedules[SCHEDULE_NUM_MAX];
};

AppData *app_data_create();

void app_data_release(AppData *app_data);

struct AppData *app_data_init(struct AppData *);

void sync_changed_handler(const uint32_t key, const Tuple *new_tuple, const Tuple *old_tuple, void *context);

void sync_error_handler(DictionaryResult dict_error, AppMessageResult app_message_error, void *context);

void update_timer_tick(void *context);

