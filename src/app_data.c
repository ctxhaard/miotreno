#include <pebble.h>
#include "app_data_private.h"

#define SCHEDULE_INDEX_UNDEF (-1)

static AppData *g_app_data = NULL;

AppData *app_data_create() {

    AppData *result = malloc(sizeof(AppData));
    return result;
}

void app_data_release(AppData *app_data) {

    for(int i = 0 ; i < SCHEDULE_NUM_MAX; ++i) {
        schedule_release(app_data->schedules[i]);
    }
    free(app_data);
}

AppData *app_data_init(AppData *app_data) {

    app_data->schedule_index = SCHEDULE_INDEX_UNDEF;
    for(int i = 0 ; i < SCHEDULE_NUM_MAX; ++i) {
      Schedule *s = schedule_create();
      schedule_init(s);
      app_data->schedules[i] = s;
    }
    return app_data;
}

AppData *app_get_shared() {

    AppData *result = g_app_data;
    if(NULL == result)
    {
        result = app_data_create();
        app_data_init(result);
        g_app_data = result;
    }
    return result;
}

void app_shared_release() {

    app_data_release(g_app_data);
    g_app_data = NULL;
}

void app_set_index(AppData *app_data, int index) {
    if(index < SCHEDULE_NUM_MAX) {
        app_data->schedule_index = index;
    }
}

Schedule *app_get_current_schedule(AppData *app_data) {
    Schedule *result = NULL;
    if(app_data->schedule_index != SCHEDULE_INDEX_UNDEF)
        result = app_data->schedules[app_data->schedule_index];

    return result;
}

void app_load_test_schedules(AppData *this) {
  
  this->schedules[0] = schedule_init(schedule_create(),"Meolo","Venezia S.L.","17:39");
  this->schedules[0] = schedule_init(schedule_create(),"Quarto D'Altino","Venezia S.L.","17:55");
  this->schedules[0] = schedule_init(schedule_create(),"Quarto D'Altino","Venezia S.L.","18:17");
}
