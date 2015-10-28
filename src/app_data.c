#include <pebble.h>
#include "app_data_private.h"

static AppData *g_app_data = NULL;

#define STORAGE_KEY_CURRENT_SCHEDULE_INDEX 1
#define UPDATE_TIMER_MS (5 * 60 * 1000)

AppData *app_data_create() {

    AppData *result = malloc(sizeof(AppData));
    return result;
}

void app_data_release(AppData *app_data) {

    for(int i = 0 ; i < SCHEDULE_NUM_MAX; ++i) {
        schedule_release(app_data->schedules[i]);
    }
    if(g_app_data == app_data) {
      app_sync_deinit(&app_data->sync.sync);
    }
    free(app_data);
}

AppData *app_data_init(AppData *this) {

  memset(this,0,sizeof(AppData));
  this->schedule_index = SCHEDULE_INDEX_UNDEF;
  this->callbacks.timer_tick = update_timer_tick;
  return this;
}

AppData *app_get_shared() {

    AppData *result = g_app_data;
    if(NULL == result)
    {
        result = app_data_create();
        app_data_init(result);
        g_app_data = result;

        // AppSync init
        Tuplet initial_values[] = {
          TupletCString(KEY_COD_PARTENZA, ""),
          TupletCString(KEY_COD_TRENO, ""),
          TupletCString(KEY_COD_STAZIONE, ""),
          TupletCString(KEY_COD_STATUS, ""),
          TupletCString(KEY_COD_LAST_STATION, ""),
          TupletInteger(KEY_JS_READY,0),
        };

        app_sync_init(&result->sync.sync,
                      result->sync.buffer,
                      sizeof(result->sync.buffer),
                      initial_values,
                      ARRAY_LENGTH(initial_values),
                      sync_changed_handler,
                      sync_error_handler,
                      result); // NOTE: AppData is passed as context

    }
    return result;
}

void app_shared_release() {

    app_data_release(g_app_data);
    g_app_data = NULL;
}

// void app_set_index(AppData *app_data, int index) {
//     if(index < SCHEDULE_NUM_MAX) {
//       app_data->schedule_index = index;
//     }
//     else {
//       APP_LOG(APP_LOG_LEVEL_ERROR,"AppData: setting invalid schedule index");
//     }
// }

AppDataCallbacks app_get_callbacks(AppData *this) {
  return this->callbacks;
}

void app_set_callbacks(AppData *this,AppDataCallbacks callbacks) {
  this->callbacks = callbacks;
}

Schedule *app_select_first_schedule(AppData *this) {

  int new_index = persist_read_int(STORAGE_KEY_CURRENT_SCHEDULE_INDEX);
  if(new_index >= SCHEDULE_NUM_MAX) {
    return NULL;
  }
  Schedule *result = this->schedules[new_index];
  if(result) {
    this->schedule_index = new_index;
    
    schedule_set_status(result,"loading...");
    schedule_set_last_station(result,"loading...");     

    schedule_sync_push(result,&(this->sync.sync));
  }
  return result;
}

Schedule *app_select_next_schedule(AppData *this){

  int new_index = this->schedule_index;
  Schedule *result = NULL;
  do {
    new_index = (new_index + 1) % SCHEDULE_NUM_MAX;
    result = this->schedules[new_index];
  } while(!result && new_index != 0);
  if(result) {
    this->schedule_index = new_index;
    persist_write_int(STORAGE_KEY_CURRENT_SCHEDULE_INDEX,new_index);
    
    schedule_set_status(result,"loading...");
    schedule_set_last_station(result,"loading...");     

    schedule_sync_push(result,&(this->sync.sync));
  }
  return result;
}

Schedule *app_select_prev_schedule(AppData *this){

  int new_index = this->schedule_index;
  Schedule *result = NULL;
  do {
    new_index = (new_index - 1);
    if(new_index < 0) new_index = (SCHEDULE_NUM_MAX - 1);
    
    result = this->schedules[new_index];
  } while(!result && new_index != 0);
  if(result) {
    this->schedule_index = new_index;
    persist_write_int(STORAGE_KEY_CURRENT_SCHEDULE_INDEX,new_index);
    
    schedule_set_status(result,"loading...");
    schedule_set_last_station(result,"loading...");     

    schedule_sync_push(result,&(this->sync.sync));
  }
  return result;
}

void app_sync_schedule(AppData *this,Schedule *s) {
    schedule_sync_push(s,&(this->sync.sync));  
}

Schedule *app_get_current_schedule(AppData *this) {

  Schedule *result = NULL;
  if(this->schedule_index != SCHEDULE_INDEX_UNDEF) {
    result = this->schedules[this->schedule_index];
  }
  return result;
}

void app_load_test_schedules(AppData *this) {

  this->schedules[0] = schedule_init(schedule_create(),
                                     "S03200",
                                     "10046",
                                     "S02668",
                                     "Meolo","Venezia S.L.","17:39");

  this->schedules[1] = schedule_init(schedule_create(),
                                     "S03317", // trieste
                                     "2216", // 17:55
                                     "S02670", // quarto d'altino
                                     "Quarto D'Altino","Venezia S.L.","17:55");

  this->schedules[2] = schedule_init(schedule_create(),
                                     "S03200", // portogrouaro
                                     "10046", // 18:17
                                     "S02670", // Quarto d'altino
                                     "Quarto D'Altino","Venezia S.L.","18:17");

  this->schedules[3] = schedule_init(schedule_create(),
                                     "S03200", // portogrouaro
                                     "10046", // 18:11
                                     "S02668", // Meolo
                                     "Meolo","Venezia S.L.","18:11");

  this->schedules[4] = schedule_init(schedule_create(),
                                     "S02593", // Venezia
                                     "10011", // 07:11
                                     "S03200", // Venezia
                                     "Venezia S.L.","Portogruaro","07:11");

}

void sync_changed_handler(const uint32_t key, const Tuple *new_tuple, const Tuple *old_tuple, void *context) {
  
  AppData *app_data = context;
  Schedule *s = app_get_current_schedule(app_data);
  bool changed = false;

  // NOTE: changed handler is called in case of Tuplet reorganization; check actual values
  // changing is needed
  // status could be the same for different trains: skip value comparison
  if(KEY_COD_STATUS == key /*&& old_tuple && 0 != strcmp(new_tuple->value->cstring,old_tuple->value->cstring)*/) {
    APP_LOG(APP_LOG_LEVEL_DEBUG,"KEY_COD_STATUS changed: %s",new_tuple->value->cstring);
    schedule_set_status(s,new_tuple->value->cstring);
    changed = true;
  }
  // last station could be the same for different trains: skip value comparison
  else if(KEY_COD_LAST_STATION == key /*&& old_tuple && 0 != strcmp(new_tuple->value->cstring,old_tuple->value->cstring)*/) {
    APP_LOG(APP_LOG_LEVEL_DEBUG,"KEY_COD_LAST_STATION changed: %s",new_tuple->value->cstring);
    schedule_set_last_station(s,new_tuple->value->cstring); 
    changed = true;
  }
  else if(KEY_JS_READY == key && new_tuple->value->int32 && old_tuple && new_tuple->value->int32 != old_tuple->value->int32) {
    // javascript is ready to run
    app_select_first_schedule(app_data);
  }
  if(changed && app_data->callbacks.schedule_changed) {
    app_data->callbacks.schedule_changed(s);    
  }
  if(app_data->callbacks.timer_tick) {
    if(app_data->sync.ldtmr) {
      app_timer_reschedule(app_data->sync.ldtmr,UPDATE_TIMER_MS);
    }
    else {
      app_timer_register(UPDATE_TIMER_MS,app_data->callbacks.timer_tick,app_data);
    }
  }
}

void sync_error_handler(DictionaryResult dict_error, AppMessageResult app_message_error, void *context) {

  APP_LOG(APP_LOG_LEVEL_DEBUG,"%s",__PRETTY_FUNCTION__);
}

void update_timer_tick(void *context) {
  AppData *this = context;

  app_timer_reschedule(this->sync.ldtmr,UPDATE_TIMER_MS);
  
  Schedule *s = app_get_current_schedule(this);
  if(s) {
    schedule_sync_push(s,&(this->sync.sync));
  }
}

