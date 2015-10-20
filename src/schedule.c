#include "schedule_private.h"

Schedule *schedule_create() {
  Schedule *result = malloc(sizeof(Schedule));
  result->id = 0xCACA;
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

void set_str(char **ppDest,char *src) {

  // NOTE: se il primo parametro di realloc e'NULL
  // corrisponse ad una malloc
  const size_t len = strlen(src) + 1;
  char *pDest = *ppDest;
  pDest = realloc(pDest,len);
  strcpy(pDest,src);
  pDest[len - 1] = '\0';
  *ppDest = pDest;
 }

Schedule *schedule_init(Schedule *s,char *train_id,char *station,char *dest,char *exp_dep) {
  APP_LOG(APP_LOG_LEVEL_DEBUG,"%s",__PRETTY_FUNCTION__);
  if(train_id && station && dest && exp_dep) {
    memset(s,0,sizeof(Schedule));
    s->id = 0xCACA;
    set_str(&s->train_id,train_id);
    set_str(&s->station,station);
    set_str(&s->destination,dest);
    set_str(&s->expected_departure,exp_dep);
  }
  return s;
}

char *schedule_get_station(Schedule *s) {
  char *result = s->station;
  APP_LOG(APP_LOG_LEVEL_DEBUG,"get_station: %s",result);
  return result;
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

void schedule_dump(Schedule *s) {
  APP_LOG(APP_LOG_LEVEL_DEBUG,"Schedule (0x%0x):\n"
          "\tid:0x%X\n"
          "\ttrain id: %s\n"
          "\tstation: %s\n"
          "\tdestination: %s\n"
          "\texp dep:%s",
    (int)s,
    (uint)s->id,
    s->train_id,
    s->station,
    s->destination,
    s->expected_departure);
}


