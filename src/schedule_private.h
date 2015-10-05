#pragma once

#include <pebble.h>
#include "schedule.h"

struct Schedule {
    char *expected_departure;
    char *last_station;
    char *status;
    // TODO: manage icon ICON
    char *destination;
    char *station;
};
