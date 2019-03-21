/**
 * @file sensor_light.cc
 *
 * @copyright Yuanzhe Liu, All rights reserved.
 */

 /*******************************************************************************
  * Includes
  ******************************************************************************/
#include <algorithm>
#include <iostream>
#include "src/sensor_light.h"
/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);
/*******************************************************************************
 * Fucntions
 ******************************************************************************/
SensorLight::SensorLight() {
  set_type(kSensorLight);
}

void SensorLight::calculateReading(Pose light_position, double l_radius,
  Pose sensor_position) {
  double x = light_position.x - sensor_position.x;
  double y = light_position.y - sensor_position.y;
  double distance = sqrt(x*x + y*y) - l_radius;
  double result = get_reading() + sensitivity_/(pow(1.08, distance));

  if (result > 1000) {
    set_reading(1000);
  } else {
    set_reading(result);
  }
}

NAMESPACE_END(csci3081);
