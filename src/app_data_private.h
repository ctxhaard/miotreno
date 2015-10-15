#include <pebble.h>
#include "app_data.h"

struct Schedule {
    char *expected_departure;
    char *last_station;
    char *status;
    // TODO: manage icon ICON
    char *destination;
    char *station;
};

struct AppData{
    Schedule *schedules;
    int schedule_index;
};

struct AppData *app_data_init(struct AppData *);
