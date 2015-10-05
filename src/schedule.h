#pragma once

struct Schedule;
typedef struct Schedule Schedule;

AppData *app_get_shared();

void     app_shared_release();

void     app_set_index(AppData *,int index);

Schedule *app_get_current_schedule(AppData *);


char *schedule_get_station(Schedule *);

char *schedule_get_destination(Schedule *);

char *schedule_get_status(Schedule *);

char *schedule_get_expected_departure(Schedule *);

char *schedule_get_last_station(Schedule *);

