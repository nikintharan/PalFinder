/*
 * Copyright (c) 2015 Pebble Technology
 */

#pragma once

#include <pebble.h>
#include "palfinder_app_data.h"

typedef struct {
  PalfinderAppDataPoint *data_point;
  PalfinderAppMainWindowViewModel view_model;
  Animation *previous_animation;
  TextLayer *fake_statusbar;
  TextLayer *pagination_layer;
  TextLayer *mood_layer;
  Layer *horizontal_ruler_layer;
  TextLayer *temperature_layer;
  TextLayer *highlow_layer;
  TextLayer *description_layer;
  Layer *icon_layer;
} PalfinderAppData;
