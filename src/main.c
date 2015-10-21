#include <pebble.h>
#include "main_window.h"
#include "app_data.h"


void handle_init(void) {

  AppData *a = app_get_shared();
  app_load_test_schedules(a);
  show_main_window();

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

