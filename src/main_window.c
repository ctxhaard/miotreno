#include <pebble.h>
#include "main_window.h"
#include "app_data.h"

// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *s_window;
static GFont s_res_gothic_18_bold;
static TextLayer *s_expected_departure;
static TextLayer *s_last_station;
static TextLayer *s_last_station_label;
static TextLayer *s_status;
static Layer *s_icon_layer;
static Layer *s_ruler;
static TextLayer *s_destination;
static TextLayer *s_destination_label;
static TextLayer *s_station;
static ActionBarLayer *s_actionbarlayer;

static void initialise_ui(void) {
  s_window = window_create();
  window_set_background_color(s_window, GColorBlack);
  #ifndef PBL_SDK_3
    window_set_fullscreen(s_window, true);
  #endif

  s_res_gothic_18_bold = fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD);
  // s_expected_departure
  s_expected_departure = text_layer_create(GRect(8, 56, 118, 20));
  text_layer_set_background_color(s_expected_departure, GColorClear);
  text_layer_set_text_color(s_expected_departure, GColorWhite);
  text_layer_set_text(s_expected_departure, "17:39");
  text_layer_set_font(s_expected_departure, s_res_gothic_18_bold);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_expected_departure);

  // s_last_station
  s_last_station = text_layer_create(GRect(8, 126, 108, 40));
  text_layer_set_background_color(s_last_station, GColorClear);
  text_layer_set_text_color(s_last_station, GColorWhite);
  text_layer_set_text(s_last_station, "PORTOGRUARO / CAORLE");
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_last_station);

  // s_last_station_label
  s_last_station_label = text_layer_create(GRect(8, 106, 78, 20));
  text_layer_set_background_color(s_last_station_label, GColorClear);
  text_layer_set_text_color(s_last_station_label, GColorWhite);
  text_layer_set_text(s_last_station_label, "last seen at:");
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_last_station_label);

  // s_status
  s_status = text_layer_create(GRect(8, 86, 78, 20));
  text_layer_set_background_color(s_status, GColorClear);
  text_layer_set_text_color(s_status, GColorWhite);
  text_layer_set_text(s_status, "IN ORARIO");
  text_layer_set_font(s_status, s_res_gothic_18_bold);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_status);

  // s_icon_layer
  s_icon_layer = layer_create(GRect(86, 86, 40, 40));
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_icon_layer);

  // s_ruler
  s_ruler = layer_create(GRect(8, 76, 130, 10));
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_ruler);

  // s_destination
  s_destination = text_layer_create(GRect(30, 36, 98, 20));
  text_layer_set_background_color(s_destination, GColorClear);
  text_layer_set_text_color(s_destination, GColorWhite);
  text_layer_set_text(s_destination, "VENEZIA S.L.");
  text_layer_set_font(s_destination, s_res_gothic_18_bold);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_destination);

  // s_destination_label
  s_destination_label = text_layer_create(GRect(8, 36, 20, 20));
  text_layer_set_background_color(s_destination_label, GColorClear);
  text_layer_set_text_color(s_destination_label, GColorWhite);
  text_layer_set_text(s_destination_label, "to:");
  text_layer_set_font(s_destination_label, s_res_gothic_18_bold);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_destination_label);

  // s_station
  s_station = text_layer_create(GRect(8, 16, 118, 20));
  text_layer_set_background_color(s_station, GColorClear);
  text_layer_set_text_color(s_station, GColorWhite);
  text_layer_set_text(s_station, "MEOLO");
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_station);

  // s_actionbarlayer
  s_actionbarlayer = action_bar_layer_create();
  action_bar_layer_add_to_window(s_actionbarlayer, s_window);
  action_bar_layer_set_background_color(s_actionbarlayer, GColorBlack);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_actionbarlayer);
}

static void destroy_ui(void) {
  window_destroy(s_window);
  text_layer_destroy(s_expected_departure);
  text_layer_destroy(s_last_station);
  text_layer_destroy(s_last_station_label);
  text_layer_destroy(s_status);
  layer_destroy(s_icon_layer);
  layer_destroy(s_ruler);
  text_layer_destroy(s_destination);
  text_layer_destroy(s_destination_label);
  text_layer_destroy(s_station);
  action_bar_layer_destroy(s_actionbarlayer);
}
// END AUTO-GENERATED UI CODE

static void main_window_load_schedule(Window *window,Schedule *schedule) {
  if(schedule) {

    text_layer_set_text(s_station,schedule_get_station(schedule));
    text_layer_set_text(s_destination,schedule_get_destination(schedule));
    text_layer_set_text(s_status,schedule_get_status(schedule));
    text_layer_set_text(s_expected_departure,schedule_get_expected_departure(schedule));
    text_layer_set_text(s_last_station,schedule_get_last_station(schedule));
  }
  else {

    text_layer_set_text(s_station,"station");
    text_layer_set_text(s_destination,"destination");
    text_layer_set_text(s_status,"status");
    text_layer_set_text(s_expected_departure,"--:--");
    text_layer_set_text(s_last_station,"last seen at");
  }
}

static void handle_window_load(Window *window) {
  AppData *app_data = app_get_shared();
  app_set_index(app_data,0);
  Schedule *schedule = app_get_current_schedule(app_data);
  main_window_load_schedule(s_window,schedule);
}

static void handle_window_unload(Window* window) {
  destroy_ui();
}

void show_main_window(void) {
  initialise_ui();
  window_set_window_handlers(s_window, (WindowHandlers) {
    .load = handle_window_load,
    .unload = handle_window_unload,
  });
  window_stack_push(s_window, true);
}

void hide_main_window(void) {
  window_stack_remove(s_window, true);
}
