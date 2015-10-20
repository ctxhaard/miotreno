#pragma once

#include <pebble.h>
#include "app_data.h"
#include "schedule.h"

#define SCHEDULE_NUM_MAX (10)

struct AppData{
  int schedule_index;
  Schedule *schedules[SCHEDULE_NUM_MAX];
};

AppData *app_data_create();

void app_data_release(AppData *app_data);

struct AppData *app_data_init(struct AppData *);
