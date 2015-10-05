#pragma once

struct AppData;
typedef struct AppData AppData;

AppData *app_get_shared();

void app_shared_release();

void app_set_index(AppData *,int index);
