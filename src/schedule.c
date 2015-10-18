#include "schedule_private.h"

Schedule *schedule_create() {
  Schedule *result = malloc(sizeof(Schedule));
  return result;
}

void schedule_release(Schedule *s) {
    if(s) {
      free(s);
    }
}

Schedule *schedule_init(Schedule *s,char *station,char *dest,char *exp_dep) {
  memset(s,0,sizeof(Schedule));
  s->station = station;
  s->destination = dest;
  s->expected_departure = exp_dep;
  return s;
}

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

Schedule *schedule_set_fake(Schedule *s) {
  
  // TODO: implementare
}


