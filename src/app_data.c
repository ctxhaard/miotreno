#include <pebble.h>
#include "app_data_private.h"

static AppData *g_app_data = NULL;

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
  return this;
}

static void sync_changed_handler(const uint32_t key, const Tuple *new_tuple, const Tuple *old_tuple, void *context) {

  APP_LOG(APP_LOG_LEVEL_DEBUG,"%s",__PRETTY_FUNCTION__);
  // TODO: aggiungere alla Schule corrente l'informazione
  // e notificare la GUI che il dato e' cambiato
  if(KEY_COD_STATUS == key) {
    APP_LOG(APP_LOG_LEVEL_DEBUG,"KEY_COD_STATUS changed: %s",new_tuple->value->cstring);
    AppData *app_data = context;
    Schedule *s = app_get_current_schedule(app_data);
    schedule_set_status(s,new_tuple->value->cstring);
    if(app_data->callbacks.schedule_changed) {
      app_data->callbacks.schedule_changed(s);    
    }
  }
}

static void sync_error_handler(DictionaryResult dict_error, AppMessageResult app_message_error, void *context) {

  APP_LOG(APP_LOG_LEVEL_DEBUG,"%s",__PRETTY_FUNCTION__);
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

void app_set_callbacks(AppData *this,AppDataCallbacks callbacks) {
  this->callbacks = callbacks;
}

Schedule *app_select_first_schedule(AppData *this) {

  int new_index = 0;
  if(new_index >= SCHEDULE_NUM_MAX) {
    return NULL;
  }
  Schedule *result = this->schedules[new_index];
  if(result) {
    this->schedule_index = new_index;
    schedule_sync_push(result,&(this->sync.sync));
  }
  return result;
}

Schedule *app_select_next_schedule(AppData *this){

  int new_index = this->schedule_index + 1;
  if(new_index >= SCHEDULE_NUM_MAX) {
    return NULL;
  }
  Schedule *result = this->schedules[new_index];
  if(result) {
    this->schedule_index = new_index;
    schedule_sync_push(result,&(this->sync.sync));
  }
  return result;
}

Schedule *app_select_prev_schedule(AppData *this){

  int new_index = this->schedule_index - 1;
  if(new_index < 0) {
    return NULL;
  }
  this->schedule_index = new_index;
  Schedule *result = this->schedules[new_index];
  if(result) {
    schedule_sync_push(result,&(this->sync.sync));
  }
  return result;
}

Schedule *app_get_current_schedule(AppData *this) {

    Schedule *result = NULL;
    if(this->schedule_index != SCHEDULE_INDEX_UNDEF) {
      result = this->schedules[this->schedule_index];
    }
    return result;
}

void app_load_test_schedules(AppData *this) {

  this->schedules[0] = schedule_init(schedule_create(),"fake","fake","fake",
  "Meolo","Venezia S.L.","17:39");
  schedule_set_status(this->schedules[0],"status: undefined");

  this->schedules[1] = schedule_init(schedule_create(),
  "S03317", // trieste
  "2216", // 17:55
  "S02670", // quarto d'altino
  "Quarto D'Altino","Venezia S.L.","17:55");
  schedule_set_status(this->schedules[1],"status: undefined");

  this->schedules[2] = schedule_init(schedule_create(),
  "S03200", // portogrouaro
  "10046", // 18:17
  "S02670", // Quarto d'altino
  "Quarto D'Altino","Venezia S.L.","18:17");
  schedule_set_status(this->schedules[2],"status: undefined");
}
