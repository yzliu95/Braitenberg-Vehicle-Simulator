/**
 * @file sensor_food.h
 *
 * @copyright Yuanzhe Liu, All rights reserved.
 */

#ifndef SRC_SENSOR_FOOD_H_
#define SRC_SENSOR_FOOD_H_
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/common.h"
#include "src/sensor.h"
#include "src/params.h"
#include "src/pose.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
 /**
 * @brief Class representing a food sensor
 * food sensor will receive necessory position infos and calculate its reading
 */
class SensorFood : public Sensor {
 public:
  SensorFood();
  void calculateReading(Pose food_position, double radius,
    Pose sensor_position);
};

NAMESPACE_END(csci3081);
#endif  // SRC_SENSOR_FOOD_H_
