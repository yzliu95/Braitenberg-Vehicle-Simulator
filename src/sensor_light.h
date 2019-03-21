/**
 * @file sensor_light.h
 *
 * @copyright Yuanzhe Liu, All rights reserved.
 */
#ifndef SRC_SENSOR_LIGHT_H_
#define SRC_SENSOR_LIGHT_H_
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
  * @brief Class representing a light sensor
  * light sensor will receive necessory position infos and calculate its reading
  */
class SensorLight : public Sensor {
 public:
  SensorLight();
  void calculateReading(Pose light_position, double radius,
    Pose sensor_position);
};
NAMESPACE_END(csci3081);
#endif  // SRC_SENSOR_LIGHT_H_
