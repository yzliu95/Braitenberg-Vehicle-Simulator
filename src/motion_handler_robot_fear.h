/**
 * @file motion_handler_robot_fear.h
 *
 * @copyright 2018 3081 Staff, All rights reserved.
 */

#ifndef SRC_MOTION_HANDLER_ROBOT_FEAR_H_
#define SRC_MOTION_HANDLER_ROBOT_FEAR_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <cassert>
#include <iostream>

#include "src/common.h"
#include "src/motion_handler_robot.h"
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
 * @brief This class handles collision for fear robots
 */
class MotionHandlerRobotFear : public MotionHandlerRobot {
 public:
  explicit MotionHandlerRobotFear(ArenaMobileEntity * ent)
      : MotionHandlerRobot(ent) {}

  MotionHandlerRobotFear(const MotionHandlerRobotFear& other) = default;
  MotionHandlerRobotFear& operator=(const MotionHandlerRobotFear& other)
    = default;

  /**
  * @brief Update the speed and the pose angle according to the sensor readings.
  * @param[in] light_l, light_r: left and right light sensor readings
  * @param[in] food_l, food_r: left and right food sensor readings
  * @param[in] int: hunger level of robot
  */
  void UpdateVelocity_Robot(double light_l, double light_r,
    double food_l, double food_r, int hunger) override;
};

NAMESPACE_END(csci3081);

#endif  // SRC_MOTION_HANDLER_ROBOT_FEAR_H_
