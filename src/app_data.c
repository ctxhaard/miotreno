#include <pebble.h>
//#include "app_data.h"
#include "app_data_private.h"
//#include <stddef.h> // NULL
//#include <stdlib.h> // malloc

#define SCHEDULE_NUM_MAX (10)
#define SCHEDULE_INDEX_UNDEF (-1)

static AppData *g_app_data = NULL;

AppData *app_data_create() {

    AppData *result = malloc(sizeof(AppData));
    result->schedules = calloc(SCHEDULE_NUM_MAX,sizeof(Schedule *));
    return result;
}

void app_data_release(AppData *app_data) {

    for(int i = 0 ; i < SCHEDULE_NUM_MAX; ++i) {
        schedule_release(app_data->schedules + i);
    }
    free(app_data->schedules);
    free(app_data);
}

AppData *app_data_init(AppData *app_data) {

    app_data->schedule_index = SCHEDULE_INDEX_UNDEF;
    for(int i = 0 ; i < SCHEDULE_NUM_MAX; ++i) {
        Schedule *s = app_data->schedules + i;
        s = schedule_create();
        schedule_init(s);
    }
//    app_data->schedules = calloc(SCHEDULE_NUM_MAX,sizeof(Schedule));
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
