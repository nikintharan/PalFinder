/*
 * Copyright (c) 2015 Pebble Technology
 */

#pragma once

#include <pebble.h>

struct PalfinderAppMainWindowViewModel;

typedef void (*PalfinderAppMainWindowViewModelFunc)(struct PalfinderAppMainWindowViewModel* model);

typedef struct {
  PalfinderAppMainWindowViewModelFunc announce_changed;
  struct {
    GColor top;
    GColor bottom;
    int32_t to_bottom_normalized;
  } bg_color;
  char *mood;
  struct {
    int16_t value;
    char text[8];
  } temperature;
  struct {
    GDrawCommandImage *draw_command;
    int32_t to_square_normalized;
  } icon;
  struct {
    int16_t idx;
    int16_t num;
    char text[8];
  } pagination;
  struct {
    int16_t high;
    int16_t low;
    char text[20];
  } highlow;
  char *description;
} PalfinderAppMainWindowViewModel;

//! calls model's .announce_changed or does nothing if NULL
void palfinder_app_main_window_view_model_announce_changed(PalfinderAppMainWindowViewModel *model);

typedef struct {
  char *mood;
  char *description;
  int icon;
  int16_t current;
  int16_t high;
  int16_t low;
} PalfinderAppDataPoint;

typedef struct {
  int16_t temperature;
  int16_t low;
  int16_t high;
} PalfinderDataViewNumbers;


void palfinder_app_view_model_set_highlow(PalfinderAppMainWindowViewModel *model, int16_t high, int16_t low);

void palfinder_app_view_model_set_temperature(PalfinderAppMainWindowViewModel *model, int16_t value);
void palfinder_app_view_model_set_icon(PalfinderAppMainWindowViewModel *model, GDrawCommandImage *image);

PalfinderDataViewNumbers palfinder_app_data_point_view_model_numbers(PalfinderAppDataPoint *data_point);

GDrawCommandImage *palfinder_app_data_point_create_icon(PalfinderAppDataPoint *data_point);

void palfinder_app_view_model_fill_strings_and_pagination(PalfinderAppMainWindowViewModel *view_model, PalfinderAppDataPoint *data_point);

void palfinder_view_model_fill_numbers(PalfinderAppMainWindowViewModel *model, PalfinderDataViewNumbers numbers);

void palfinder_app_view_model_fill_all(PalfinderAppMainWindowViewModel *model, PalfinderAppDataPoint *data_point);

void palfinder_app_view_model_fill_colors(PalfinderAppMainWindowViewModel *model, GColor color);

void palfinder_app_view_model_deinit(PalfinderAppMainWindowViewModel *model);

GColor palfinder_app_data_point_color(PalfinderAppDataPoint *data_point);

int palfinder_app_num_data_points(void);

PalfinderAppDataPoint *palfinder_app_data_point_at(int idx);
PalfinderAppDataPoint *palfinder_app_data_point_delta(PalfinderAppDataPoint *dp, int delta);
