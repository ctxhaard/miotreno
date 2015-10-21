#include <pebble.h>
#include "main_window.h"
#include "app_data.h"

#define APP_SYNC_BUFFER_SIZE (1024)

struct {
  AppSync sync;
  uint8_t buffer[APP_SYNC_BUFFER_SIZE];
} s_sync;

#define KEY_COD_PARTENZA 1
#define KEY_COD_TRENO    2
#define KEY_COD_STAZIONE 3
#define KEY_COD_STATUS   4
#define KEY_COD_LAST_STATION 5

static void sync_changed_handler(const uint32_t key, const Tuple *new_tuple, const Tuple *old_tuple, void *context) {

  APP_LOG(APP_LOG_LEVEL_DEBUG,"%s",__PRETTY_FUNCTION__);
}

static void sync_error_handler(DictionaryResult dict_error, AppMessageResult app_message_error, void *context) {

  APP_LOG(APP_LOG_LEVEL_DEBUG,"%s",__PRETTY_FUNCTION__);
}

void handle_init(void) {

  AppData *a = app_get_shared();
  app_load_test_schedules(a);
  show_main_window();
  // AppSync init
  Tuplet initial_values[] = {
    TupletCString(KEY_COD_PARTENZA, ""),
    TupletCString(KEY_COD_TRENO, ""),
    TupletCString(KEY_COD_STAZIONE, ""),
    TupletCString(KEY_COD_STATUS, ""),
    TupletCString(KEY_COD_LAST_STATION, ""),
  };
  
  app_message_open(app_message_inbox_size_maximum(),app_message_outbox_size_maximum());
  app_sync_init(&s_sync.sync,
                s_sync.buffer,
                sizeof(s_sync.buffer),
                initial_values,
                ARRAY_LENGTH(initial_values),
                sync_changed_handler,
                sync_error_handler,
                a); // NOTE: AppData is passed as context

}

void handle_deinit(void) {
  hide_main_window();
  
  app_sync_deinit(&s_sync.sync);
}

int main(void) {
  handle_init();
  app_event_loop();
  handle_deinit();
}

