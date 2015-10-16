#pragma once

struct Schedule;
typedef struct Schedule Schedule;

Schedule *schedule_create();

void schedule_release(Schedule *);

Schedule *schedule_init(Schedule *);

char *schedule_get_station(Schedule *);

char *schedule_get_destination(Schedule *);

char *schedule_get_status(Schedule *);

char *schedule_get_expected_departure(Schedule *);

char *schedule_get_last_station(Schedule *);
