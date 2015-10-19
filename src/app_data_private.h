#pragma once

#include <pebble.h>
#include "app_data.h"
#include "schedule.h"

struct AppData{
    Schedule **schedules;
    int schedule_index;
};

AppData *app_data_create();

void app_data_release(AppData *app_data);

struct AppData *app_data_init(struct AppData *);
