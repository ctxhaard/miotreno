#pragma once

#include <pebble.h>
#include "app_data.h"
#include "schedule.h"

#define SCHEDULE_NUM_MAX (10)
#define SCHEDULE_INDEX_UNDEF (-1)
#define APP_SYNC_BUFFER_SIZE (2048)

struct AppData{
  struct {
    AppSync sync;
    uint8_t buffer[APP_SYNC_BUFFER_SIZE];
  } sync;
  AppDataCallbacks callbacks;
  int schedule_index;
  Schedule *schedules[SCHEDULE_NUM_MAX];
};

AppData *app_data_create();

void app_data_release(AppData *app_data);

struct AppData *app_data_init(struct AppData *);
