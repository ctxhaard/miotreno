#pragma once

#include <pebble.h>
#include "app_data.h"
#include "schedule.h"

struct AppData{
    Schedule *schedules;
    int schedule_index;
};

struct AppData *app_data_init(struct AppData *);
