#include <pebble.h>
#include "main_window.h"
#include "app_data.h"

// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *s_window;
static GFont s_res_24;
static GFont s_res_24_bold;
static TextLayer *s_expected_departure;
static TextLayer *s_last_station;
static TextLayer *s_last_station_label;
static TextLayer *s_status;
static Layer *s_icon_layer;
static Layer *s_ruler;
static TextLayer *s_destination;
static TextLayer *s_destination_label;
static TextLayer *s_station;

static void ruler_update_proc(Layer *this,GContext *ctx) {
  
  graphics_context_set_stroke_color(ctx,GColorBlack);
  graphics_context_set_stroke_width(ctx,2);
  graphics_draw_line(ctx,GPoint(0,5),GPoint(100,5));
}

static void initialise_ui(void) {
  s_window = window_create();
  window_set_background_color(s_window, GColorWhite);
  #ifndef PBL_SDK_3
  window_set_fullscreen(s_window, true);
  #endif
  // static GFont s_custom_font_28;  
  s_res_24 = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_KEY_DS_DIGITAL_24));
  s_res_24_bold = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_KEY_DS_DIGITAL_BOLD_24));
  // s_station
  s_station = text_layer_create(GRect(8, 4, 138, 25));
  text_layer_set_background_color(s_station, GColorClear);
  text_layer_set_text_color(s_station, GColorBlack);
  text_layer_set_font(s_station, s_res_24);
  text_layer_set_overflow_mode(s_station,GTextOverflowModeWordWrap);
  text_layer_set_text(s_station,"--");
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_station);
  // s_destination_label
  s_destination_label = text_layer_create(GRect(8, 29, 20, 25));
  text_layer_set_background_color(s_destination_label, GColorClear);
  text_layer_set_text_color(s_destination_label, GColorBlack);
  text_layer_set_font(s_destination_label, s_res_24);
  text_layer_set_text(s_destination_label,"a:");
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_destination_label);
  // s_destination
  s_destination = text_layer_create(GRect(30, 29, 98, 25));
  text_layer_set_background_color(s_destination, GColorClear);
  text_layer_set_text_color(s_destination, GColorBlack);
  text_layer_set_font(s_destination, s_res_24);
  text_layer_set_overflow_mode(s_destination,GTextOverflowModeWordWrap);
  text_layer_set_text(s_destination,"--");
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_destination);
  // s_expected_departure
  s_expected_departure = text_layer_create(GRect(8, 54, 138, 25));
  text_layer_set_background_color(s_expected_departure, GColorClear);
  text_layer_set_text_color(s_expected_departure, GColorBlack);
  text_layer_set_font(s_expected_departure, s_res_24);
  text_layer_set_text(s_expected_departure,"--:--");
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_expected_departure);
  // s_ruler
  s_ruler = layer_create(GRect(8, 79, 130, 10));
  layer_set_update_proc(s_ruler,ruler_update_proc);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_ruler);
  // s_status
  s_status = text_layer_create(GRect(8, 89, 138, 25));
  text_layer_set_background_color(s_status, GColorClear);
  text_layer_set_text_color(s_status, GColorBlack);
  text_layer_set_font(s_status, s_res_24_bold);
  text_layer_set_overflow_mode(s_status,GTextOverflowModeWordWrap);
  text_layer_set_text(s_status,"loading...");
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_status);
  // s_last_station_label
  s_last_station_label = text_layer_create(GRect(8, 114, 20, 25));
  text_layer_set_background_color(s_last_station_label, GColorClear);
  text_layer_set_text_color(s_last_station_label, GColorBlack);
  text_layer_set_font(s_last_station_label, s_res_24);
  text_layer_set_text(s_last_station_label,">>");
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_last_station_label);
  // s_last_station
  s_last_station = text_layer_create(GRect(28, 114, 108, 50));
  text_layer_set_background_color(s_last_station, GColorClear);
  text_layer_set_text_color(s_last_station, GColorBlack);
  text_layer_set_overflow_mode(s_last_station,GTextOverflowModeWordWrap);
  text_layer_set_font(s_last_station, s_res_24);
  text_layer_set_text(s_last_station,"loading...");
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_last_station);
  // s_icon_layer
  s_icon_layer = layer_create(GRect(86, 86, 40, 40));
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_icon_layer);
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
  fonts_unload_custom_font(s_res_24);
  fonts_unload_custom_font(s_res_24_bold);
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

static void up_handler(ClickRecognizerRef clickRecognizer,void *context) {
 
  Window *w = context;
  AppData *app_data = window_get_user_data(w);
  app_select_prev_schedule(app_data);
  main_window_load_schedule(w, app_get_current_schedule(app_data));
  // TODO: inviare comando di aggiornamento dei dati
}

static void down_handler(ClickRecognizerRef clickRecognizer,void *context) {
  
  Window *w = context;
  AppData *app_data = window_get_user_data(w);
  app_select_next_schedule(app_data);
  main_window_load_schedule(w, app_get_current_schedule(app_data));
  // TODO: inviare comando di aggiornamento dei dati
}

static void select_handler(ClickRecognizerRef clickRecognizer,void *context) {
  
  Window *w = context;
  AppData *app_data = window_get_user_data(w);
  Schedule *s = app_get_current_schedule(app_data);
  if(s) {
    app_sync_schedule(app_data,s);    
  }
}

static void click_config_provider(void *context) {

  window_single_click_subscribe(BUTTON_ID_UP, up_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN,down_handler);
  window_single_click_subscribe(BUTTON_ID_SELECT, select_handler);
}

static void schedule_changed(Schedule *s) {
  schedule_dump(s);
  APP_LOG(APP_LOG_LEVEL_DEBUG,"%s",__PRETTY_FUNCTION__);
  main_window_load_schedule(s_window,s);
  layer_mark_dirty(window_get_root_layer(s_window));
}

static void handle_window_load(Window *window) {

  window_set_click_config_provider(window,click_config_provider);
  AppData *app_data = window_get_user_data(window);
  
  AppDataCallbacks cb = app_get_callbacks(app_data);
  cb.schedule_changed = schedule_changed;
  app_set_callbacks(app_data,cb);

  app_select_first_schedule(app_data);
}

static void handle_window_unload(Window* window) {
  destroy_ui();
}

void show_main_window(void) {
  initialise_ui();
  
  AppData *app_data = app_get_shared();
  if(!app_data) APP_LOG(APP_LOG_LEVEL_ERROR,"NULL app data");

  app_select_first_schedule(app_data);
  
  window_set_user_data(s_window, app_data);

  window_set_window_handlers(s_window, (WindowHandlers) {
    .load = handle_window_load,
    .unload = handle_window_unload,
  });
  window_stack_push(s_window, true);
}

void hide_main_window(void) {
  window_stack_remove(s_window, true);
}
