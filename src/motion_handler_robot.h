/**
 * @file motion_handler_robot.h
 *
 * @copyright 2018 3081 Staff, All rights reserved.
 */

#ifndef SRC_MOTION_HANDLER_ROBOT_H_
#define SRC_MOTION_HANDLER_ROBOT_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <cassert>
#include <iostream>

#include "src/common.h"
#include "src/motion_handler.h"
#include "src/sensor_touch.h"
#include "src/communication.h"
#include "src/robot_type.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Classes
 ******************************************************************************/

/**
 * @brief This is an abstract class. It builds an strategy interface for further
 * development.
 */
class MotionHandlerRobot : public MotionHandler {
 public:
  explicit MotionHandlerRobot(ArenaMobileEntity * ent)
      : MotionHandler(ent) {}

  MotionHandlerRobot(const MotionHandlerRobot& other) = default;
  MotionHandlerRobot& operator=(const MotionHandlerRobot& other) = default;

  /**
  * @brief Update the speed and the pose angle according to the sensor readings.
  * @param[in] light_l, light_r: left and right light sensor readings
  * @param[in] food_l, food_r: left and right food sensor readings
  * @param[in] int: hunger level of robot
  */
  virtual void UpdateVelocity_Robot(__unused double light_l,
    __unused double light_r, __unused double food_l, __unused double food_r,
    __unused int hunger) {}
};

NAMESPACE_END(csci3081);

#endif  // SRC_MOTION_HANDLER_ROBOT_H_
