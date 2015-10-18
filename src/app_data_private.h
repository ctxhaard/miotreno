#pragma once

#include <pebble.h>
#include "app_data.h"
#include "schedule.h"

#define SCHEDULE_NUM_MAX (10)

struct AppData{
    Schedule *schedules[SCHEDULE_NUM_MAX];
    int schedule_index;
};

AppData *app_data_create();

void app_data_release(AppData *app_data);

struct AppData *app_data_init(struct AppData *);
