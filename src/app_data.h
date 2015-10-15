#pragma once

struct AppData;
typedef struct AppData AppData;

struct Schedule;
typedef struct Schedule Schedule;

AppData *app_get_shared();
void         app_shared_release();
void         app_set_index(AppData *,int index);
Schedule *app_get_current_schedule(AppData *);
