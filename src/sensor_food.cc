/**
 * @file sensor_food.cc
 *
 * @copyright Yuanzhe Liu, All rights reserved.
 */

 /*******************************************************************************
  * Includes
  ******************************************************************************/
#include <algorithm>
#include <iostream>
#include "src/sensor_food.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);
/*******************************************************************************
 * Functions
 ******************************************************************************/
SensorFood::SensorFood() {
  set_type(kSensorFood);
}

void SensorFood::calculateReading(Pose food_position, double l_radius,
  Pose sensor_position) {
  double x = food_position.x - sensor_position.x;
  double y = food_position.y - sensor_position.y;
  double distance = sqrt(x*x + y*y) - l_radius;
  double result = get_reading() + sensitivity_/(pow(1.01, distance));

  if (result > 1000) {
    set_reading(1000);
  } else {
    set_reading(result);
  }
}

NAMESPACE_END(csci3081);
