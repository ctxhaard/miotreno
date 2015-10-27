#pragma once
#include "schedule.h"

struct AppData;
typedef struct AppData AppData;

typedef struct {
  /// A Schedule has changed
  void (*schedule_changed)(Schedule *);
  /// Update timer tick
  AppTimerCallback timer_tick;
} AppDataCallbacks;

AppData *app_get_shared();

void app_shared_release();

void app_set_callbacks(AppData *,AppDataCallbacks);

AppDataCallbacks app_get_callbacks(AppData *);

Schedule *app_select_first_schedule(AppData *);
Schedule *app_select_next_schedule(AppData *);
Schedule *app_select_prev_schedule(AppData *);

void app_sync_schedule(AppData *,Schedule *s);

Schedule *app_get_current_schedule(AppData *);

void app_load_test_schedules(AppData *);
