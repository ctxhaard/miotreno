#pragma once
#include <pebble.h>

// TODO: should be hidden...
#define KEY_COD_PARTENZA 1
#define KEY_COD_TRENO    2
#define KEY_COD_STAZIONE 3
#define KEY_COD_STATUS   4
#define KEY_COD_LAST_STATION 5
// ...

struct Schedule;
typedef struct Schedule Schedule;

Schedule *schedule_create();

void schedule_release(Schedule *);

Schedule *schedule_init(Schedule *s,char *cod_partenza,char *cod_treno,char *cod_stazione,char *station,char *dest,char *exp_dep);

char *schedule_get_cod_partenza(Schedule *);
char *schedule_get_cod_treno(Schedule *);
char *schedule_get_cod_stazione(Schedule *);

char *schedule_get_station(Schedule *);

char *schedule_get_destination(Schedule *);

char *schedule_get_expected_departure(Schedule *);

char *schedule_get_status(Schedule *);
Schedule *schedule_set_status(Schedule *,char *);

char *schedule_get_last_station(Schedule *);
Schedule *schedule_set_last_station(Schedule *,char *);

void schedule_dump(Schedule *);

void schedule_sync_push(Schedule *,AppSync *);
