#include "schedule_private.h"

Schedule *schedule_create() {
  Schedule *result = malloc(sizeof(Schedule));
  return result;
}

void schedule_release(Schedule *s) {
    if(s) {
      if(s->destination) free(s->destination);
      if(s->station) free(s->station);
      if(s->status) free(s->status);
      if(s->expected_departure) free(s->expected_departure);
      if(s->last_station) free(s->last_station);
      free(s);
    }
}

void set_str(char **pDest,char *status) {

  // NOTE: se il primo parametro di realloc e'NULL
  // corrisponse ad una malloc
  const size_t len = strlen(status) + 1;
  *pDest = realloc(this->status,len);

  char *dest = *pDest;
  strcpy(dest,status);
  dest[len - 1] = 0x00;
 }

Schedule *schedule_init(Schedule *s,char *station,char *dest,char *exp_dep) {
  memset(s,0,sizeof(Schedule));
  set_str(&s->station,station);
  set_str(&s->destination,dest);
  set_str(&s->expected_departure,exp_dep);
  return s;
}

char *schedule_get_station(Schedule *s) {
  return s->station;
}

char *schedule_get_destination(Schedule *s) {
  return s->destination;
}

char *schedule_get_expected_departure(Schedule *s) {
  return s->expected_departure;
}

char *schedule_get_status(Schedule *s) {
  return s->status;
}

Schedule *schedule_set_status(Schedule *this,char *status) {
  set_str(&this->status,status);
  return this;
 }


char *schedule_get_last_station(Schedule *s) {
  return s->last_station;
}

Schedule *schedule_set_last_station(Schedule *this,char *last_station) {
  set_str(&this->last_station,last_station);
  return this;
}
