/**
 * @file params.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_PARAMS_H_
#define SRC_PARAMS_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/common.h"

/*******************************************************************************
 * Macros
 ******************************************************************************/
/*
 * @file. Constructors for classes should use reasonable default values as
 * defined here. An exception might be if the value is 0.
 */

// graphics
#define X_DIM 1024
#define Y_DIM 768
#define TEXT_BOX_WIDTH 50
#define GUI_MENU_WIDTH 180
#define GUI_MENU_GAP 10

//
#define MINS_TILL_HUNGRY 0.5
#define MINS_TILL_REALLY_HUNGRY 2
#define MINS_TILL_STARVE 2.5

// arena
#define N_LIGHTS 4
#define N_ROBOTS_EXPLORE 5
#define N_ROBOTS_FEAR 5
#define N_ROBOTS 10
#define RATIO_FEAR 50
#define ARENA_X_DIM X_DIM
#define ARENA_Y_DIM Y_DIM

// game status
#define WON 0
#define LOST 1
#define PLAYING 2

// entity
#define DEFAULT_POSE \
  { 200, 200, 0}
#define DEFAULT_COLOR \
  { 255, 255, 255 }
#define DEFAULT_RADIUS 20

// mobile entity
#define DEFAULT_VELOCITY 4.0
#define STARTING_VELOCITY 0.0

// robot
#define ROBOT_ANGLE_DELTA 1
#define ROBOT_SPEED_DELTA 1
#define ROBOT_COLLISION_DELTA 1
#define ROBOT_RADIUS_LOWER 8
#define ROBOT_RADIUS_UPPER 14
#define ROBOT_INIT_POS \
  { 500, 500 , 0}
#define ROBOT_COLOR \
  { 0, 0, 255 }
#define ROBOT_COLOR_GODMODE \
    { 0, 0, 255 }
#define NORMAL 0
#define HUNGRY 1
#define STARVING 2
#define DEATH 3

#define ROBOT_HEADING 270
#define ROBOT_INIT_SPEED 0
#define ROBOT_OFFSET_SPEED 10
#define ROBOT_MAX_SPEED 10
#define ROBOT_MAX_ANGLE 360

// food
#define N_FOODS 4
#define FOOD_RADIUS 20
#define FOOD_COLLISION_DELTA 1
#define FOOD_INIT_POS \
  { 400, 400 }
#define FOOD_COLOR \
  { 255, 0, 0 }
#define FOOD_COLOR2 \
  { 255, 155, 0 }

// light
#define LIGHT_POSITION \
  { 200, 200 }
#define LIGHT_RADIUS 30
#define LIGHT_MIN_RADIUS 10
#define LIGHT_MAX_RADIUS 50
#define LIGHT_COLOR \
  { 255, 255, 255 }
#define ALL_LIGHT

// sensor
#define LEFT_SENSOR 0
#define RIGHT_SENSOR 1

#endif  // SRC_PARAMS_H_
