#include <pebble.h>
//#include "app_data.h"
#include "app_data_private.h"
//#include <stddef.h> // NULL
//#include <stdlib.h> // malloc

#define SCHEDULE_NUM_MAX (10)
#define SCHEDULE_INDEX_UNDEF (-1)

static AppData *g_app_data = NULL;

AppData *app_get_shared() {

    AppData *result = g_app_data;
    if(NULL == result)
    {
        result = malloc(sizeof(AppData));
        app_data_init(result);
        g_app_data = result;
    }
    return result;
}

void app_shared_release() {

    free(g_app_data);
    g_app_data = NULL;
}

void app_set_index(AppData *app_data, int index) {

    app_data->schedule_index = index;
}

Schedule *app_get_current_schedule(AppData *app_data) {
    Schedule *result = NULL;
     // TODO: continuare qui
    
    return result;
}


AppData *app_data_init(AppData *app_data) {
    
    app_data->schedule_index = SCHEDULE_INDEX_UNDEF;
//    app_data->schedules = calloc(SCHEDULE_NUM_MAX,sizeof(Schedule));
    return app_data;
}
