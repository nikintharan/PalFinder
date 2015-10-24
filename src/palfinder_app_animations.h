/*
 * Copyright (c) 2015 Pebble Technology
 */

#pragma once

#include <pebble.h>
#include "palfinder_app_data.h"

Animation *palfinder_app_create_view_model_animation_numbers(PalfinderAppMainWindowViewModel *view_model, PalfinderAppDataPoint *next_data_point);

Animation *palfinder_app_create_view_model_animation_bgcolor(PalfinderAppMainWindowViewModel *view_model, PalfinderAppDataPoint *next_data_point);

Animation *palfinder_app_create_view_model_animation_icon(PalfinderAppMainWindowViewModel *view_model, PalfinderAppDataPoint *next_data_point, uint32_t duration);
