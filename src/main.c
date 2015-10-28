#include <pebble.h>
#include "main_window.h"
#include "app_data.h"


//void inbox_received_callback(DictionaryIterator *iterator, void *context);
//void inbox_dropped_callback(AppMessageResult reason, void *context);

void handle_init(void) {

  AppData *a = app_get_shared();
  app_load_test_schedules(a);
  show_main_window();

//  app_message_register_inbox_received(inbox_received_callback);
//  app_message_register_inbox_dropped(inbox_dropped_callback);
  
  app_message_open(app_message_inbox_size_maximum(),app_message_outbox_size_maximum());
}

void handle_deinit(void) {
  hide_main_window();
}

int main(void) {
  handle_init();
  app_event_loop();
  handle_deinit();
}

void inbox_received_callback(DictionaryIterator *iterator, void *context) {
  
  Tuple *data =  dict_find(iterator,KEY_JS_READY);
  if(data) {
    
    bool active = data->value->int32;
    if(active) {
      AppData *app_data = app_get_shared();
      app_select_first_schedule(app_data);
    }
  }
}

void inbox_dropped_callback(AppMessageResult reason, void *context) {
    
  APP_LOG(APP_LOG_LEVEL_DEBUG,"message dropped");
}