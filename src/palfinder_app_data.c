/*
 * Copyright (c) 2015 Pebble Technology
 */

#include <pebble.h>
#include "palfinder_app_data.h"
#include "palfinder_app_resources.h"

void palfinder_app_main_window_view_model_announce_changed(PalfinderAppMainWindowViewModel *model) {
  if (model->announce_changed) {
    model->announce_changed((struct PalfinderAppMainWindowViewModel *)model);
  }
}

void palfinder_app_view_model_set_highlow(PalfinderAppMainWindowViewModel *model, int16_t high, int16_t low) {
  model->highlow.high = high;
  model->highlow.low = low;
  snprintf(model->highlow.text, sizeof(model->highlow.text), "HI %d°, LO %d°", model->highlow.high, model->highlow.low);
}

void palfinder_app_view_model_set_temperature(PalfinderAppMainWindowViewModel *model, int16_t value) {
  model->temperature.value = value;
  snprintf(model->temperature.text, sizeof(model->temperature.text), "%d°", model->temperature.value);
}
https://cloudpebble.net/ide/project/258737#
void palfinder_app_view_model_set_icon(PalfinderAppMainWindowViewModel *model, GDrawCommandImage *image) {
  free(model->icon.draw_command);
  model->icon.draw_command = image;
  palfinder_app_main_window_view_model_announce_changed(model);
}

PalfinderDataViewNumbers palfinder_app_data_point_view_model_numbers(PalfinderAppDataPoint *data_point) {
  return (PalfinderDataViewNumbers){
      .temperature = data_point->current,
      .high = data_point->high,
      .low = data_point->low,
  };
}

int palfinder_app_index_of_data_point(PalfinderAppDataPoint *dp);

void palfinder_app_view_model_fill_strings_and_pagination(PalfinderAppMainWindowViewModel *view_model, PalfinderAppDataPoint *data_point) {
  view_model->city = data_point->city;
  view_model->description = data_point->description;

  view_model->pagination.idx = (int16_t)(1 + palfinder_app_index_of_data_point(data_point));
  view_model->pagination.num = (int16_t)palfinder_app_num_data_points();
  snprintf(view_model->pagination.text, sizeof(view_model->pagination.text), "%d/%d", view_model->pagination.idx, view_model->pagination.num);
  palfinder_app_main_window_view_model_announce_changed(view_model);
}


GDrawCommandImage *palfinder_app_data_point_create_icon(PalfinderAppDataPoint *data_point) {
  return palfinder_app_resources_get_icon(data_point->icon);
}


void palfinder_view_model_fill_numbers(PalfinderAppMainWindowViewModel *model, PalfinderDataViewNumbers numbers) {
  palfinder_app_view_model_set_temperature(model, numbers.temperature);
  palfinder_app_view_model_set_highlow(model, numbers.high, numbers.low);
}

void palfinder_app_view_model_fill_colors(PalfinderAppMainWindowViewModel *model, GColor color) {
  model->bg_color.top = color;
  model->bg_color.bottom = color;
  palfinder_app_main_window_view_model_announce_changed(model);
}

GColor palfinder_app_data_point_color(PalfinderAppDataPoint *data_point) {
  return data_point->current > 90 ? GColorOrange : GColorPictonBlue;
}

void palfinder_app_view_model_fill_all(PalfinderAppMainWindowViewModel *model, PalfinderAppDataPoint *data_point) {
  PalfinderAppMainWindowViewModelFunc annouce_changed = model->announce_changed;
  memset(model, 0, sizeof(*model));
  model->announce_changed = annouce_changed;
  palfinder_app_view_model_fill_strings_and_pagination(model, data_point);
  palfinder_app_view_model_set_icon(model, palfinder_app_data_point_create_icon(data_point));
  palfinder_app_view_model_fill_colors(model, palfinder_app_data_point_color(data_point));
  palfinder_view_model_fill_numbers(model, palfinder_app_data_point_view_model_numbers(data_point));

  palfinder_app_main_window_view_model_announce_changed(model);
}

void palfinder_app_view_model_deinit(PalfinderAppMainWindowViewModel *model) {
  palfinder_app_view_model_set_icon(model, NULL);
}

static PalfinderAppDataPoint s_data_points[] = {
    {
        .city = "PALO ALTO",
        .description = "Light Rain.",
        .icon = PALFINDER_APP_ICON_LIGHT_RAIN,
        .current = 68,
        .high = 70,
        .low = 60,
    },
    {
        .city = "LOS ANGELES",
        .description = "Clear throughout the day.",
        .icon = PALFINDER_APP_ICON_SUNNY_DAY,
        .current = 100,
        .high = 100,
        .low = 80,
    },
    {
        .city = "SAN FRANCISCO",
        .description = "Rain and Fog.",
        .icon = PALFINDER_APP_ICON_HEAVY_SNOW,
        .current = 60,
        .high = 62,
        .low = 56,
    },
    {
        .city = "SAN DIEGO",
        .description = "Surfboard :)",
        .icon = PALFINDER_APP_ICON_GENERIC_PALFINDER,
        .current = 110,
        .high = 120,
        .low = 9,
    },
};

int palfinder_app_num_data_points(void) {
  return ARRAY_LENGTH(s_data_points);
}

PalfinderAppDataPoint *palfinder_app_data_point_at(int idx) {
  if (idx < 0 || idx > palfinder_app_num_data_points() - 1) {
    return NULL;
  }

  return &s_data_points[idx];
}

int palfinder_app_index_of_data_point(PalfinderAppDataPoint *dp) {
  for (int i = 0; i < palfinder_app_num_data_points(); i++) {
    if (dp == palfinder_app_data_point_at(i)) {
      return i;
    }
  }
  return -1;
}

PalfinderAppDataPoint *palfinder_app_data_point_delta(PalfinderAppDataPoint *dp, int delta) {
  int idx = palfinder_app_index_of_data_point(dp);
  if (idx < 0) {
    return NULL;
  }
  return palfinder_app_data_point_at(idx + delta);
}
