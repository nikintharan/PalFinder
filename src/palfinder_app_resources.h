/*
 * Copyright (c) 2015 Pebble Technology
 */

#pragma once

#include <pebble.h>

typedef enum {
  PALFINDER_APP_ICON_GENERIC_PALFINDER,
  PALFINDER_APP_ICON_HEAVY_RAIN,
  PALFINDER_APP_ICON_LIGHT_RAIN,
  PALFINDER_APP_ICON_HEAVY_SNOW,
  PALFINDER_APP_ICON_LIGHT_SNOW,
  PALFINDER_APP_ICON_PARTLY_CLOUDY,
  PALFINDER_APP_ICON_SUNNY_DAY,
} PalfinderAppIcon;

GDrawCommandImage *palfinder_app_resources_get_icon(PalfinderAppIcon icon);
