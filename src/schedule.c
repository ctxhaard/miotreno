#include "schedule_private.h"

char *schedule_get_station(Schedule *s) {
    return s->station;
}

char *schedule_get_destination(Schedule *s) {
    return s->destination;
}

char *schedule_get_status(Schedule *s) {
    return s->status;
}

char *schedule_get_expected_departure(Schedule *s) {
    return s->expected_departure;
}

char *schedule_get_last_station(Schedule *s) {
    return s->last_station;
}
