#pragma once
#include "schedule.h"

struct AppData;
typedef struct AppData AppData;

AppData *app_get_shared();

void app_shared_release();

//void app_set_index(AppData *,int index);

Schedule *app_select_first_schedule(AppData *);
Schedule *app_select_next_schedule(AppData *);
Schedule *app_select_prev_schedule(AppData *);

Schedule *app_get_current_schedule(AppData *);

void app_load_test_schedules(AppData *);
