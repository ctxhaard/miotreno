#pragma once

struct Schedule;
typedef struct Schedule Schedule;

Schedule *schedule_create();

void schedule_release(Schedule *);

Schedule *schedule_init(Schedule *s,char *train_id,char *station,char *dest,char *exp_dep);

char *schedule_get_station(Schedule *);

char *schedule_get_destination(Schedule *);

char *schedule_get_expected_departure(Schedule *);

char *schedule_get_status(Schedule *);
Schedule *schedule_set_status(Schedule *,char *);

char *schedule_get_last_station(Schedule *);
Schedule *schedule_set_last_station(Schedule *,char *);

void schedule_dump(Schedule *);
