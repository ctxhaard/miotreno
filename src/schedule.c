#include "schedule_private.h"
#include <pebble.h>

Schedule *schedule_create() {
  Schedule *result = malloc(sizeof(Schedule));
  return result;
}

void schedule_release(Schedule *s) {
    if(s) {
      free(s->id.cod_partenza);
      free(s->id.cod_treno);
      free(s->id.cod_stazione);
      free(s->destination);
      free(s->station);
      free(s->status);
      free(s->expected_departure);
      free(s->last_station);
      free(s);
    }
}

void set_str(char **ppDest,const char *src) {

  // NOTE: se il primo parametro di realloc e'NULL
  // corrisponse ad una malloc
  const size_t len = strlen(src) + 1;
  char *pDest = *ppDest;
  pDest = realloc(pDest,len);
  strcpy(pDest,src);
  pDest[len - 1] = '\0';
  *ppDest = pDest;
 }

Schedule *schedule_init(Schedule *s,char *cod_partenza,char *cod_treno,char *cod_stazione,
    char *station,char *dest,char *exp_dep) {
  if(cod_partenza && cod_treno && cod_stazione && station && dest && exp_dep) {
    memset(s,0,sizeof(Schedule));
    set_str(&s->id.cod_partenza,cod_partenza);
    set_str(&s->id.cod_treno,cod_treno);
    set_str(&s->id.cod_stazione,cod_stazione);

    set_str(&s->station,station);
    set_str(&s->destination,dest);
    set_str(&s->expected_departure,exp_dep);
  }
  return s;
}

char *schedule_get_cod_partenza(Schedule *this){
  return this->id.cod_partenza;
}

char *schedule_get_cod_treno(Schedule *this){
  return this->id.cod_treno;
}

char *schedule_get_cod_stazione(Schedule *this) {
  return this->id.cod_stazione;
}

char *schedule_get_station(Schedule *s) {
  char *result = s->station;
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

Schedule *schedule_set_status(Schedule *this,const char *status) {
//  APP_LOG(APP_LOG_LEVEL_DEBUG,"setting schedule status: %s",status);
  set_str(&this->status,status);
  return this;
 }

char *schedule_get_last_station(Schedule *s) {
  return s->last_station;
}

Schedule *schedule_set_last_station(Schedule *this,const char *last_station) {
  set_str(&this->last_station,last_station);
  return this;
}

void schedule_sync_push(Schedule *this,AppSync *app_sync) {

  Tuplet tuples[] = {
    TupletCString(KEY_COD_TRENO,this->id.cod_treno),
    TupletCString(KEY_COD_PARTENZA,this->id.cod_partenza),
    TupletCString(KEY_COD_STAZIONE,this->id.cod_stazione),
  };
  app_sync_set(app_sync,tuples,sizeof(tuples)/sizeof(Tuplet));
}

void schedule_dump(Schedule *s) {
  APP_LOG(APP_LOG_LEVEL_DEBUG,"Schedule (0x%0x):\n"
          "\ttrain id: %s\n"
          "\tstation: %s\n"
          "\tdestination: %s\n",
          (int)s,
          s->id.cod_treno,
          s->station,
          s->destination);
    APP_LOG(APP_LOG_LEVEL_DEBUG,
          "\texp dep:%s\n"
          "\tstatus:%s",
          s->expected_departure,
          s->status);

}
