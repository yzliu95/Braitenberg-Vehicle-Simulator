/**
 * @file motion_handler_robot_fear.cc
 *
 * @copyright Yuanzhe Liu, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <utility>
#include "src/motion_handler_robot_fear.h"
#include "src/motion_behavior_differential.h"
#include "src/params.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void MotionHandlerRobotFear::UpdateVelocity_Robot(double light_l,
  double light_r, double food_l, double food_r, int hunger) {
    double speed_left = 0;
    double speed_right = 0;
    switch (hunger) {
      case NORMAL:
        speed_left =  ROBOT_OFFSET_SPEED * (light_l / 1000);
        speed_right =  ROBOT_OFFSET_SPEED * (light_r / 1000);
        break;
      case HUNGRY:
        speed_left =  ROBOT_OFFSET_SPEED * (light_l / 1000) * 0.5;
        speed_right =  ROBOT_OFFSET_SPEED * (light_r / 1000) * 0.5;
        speed_left += ROBOT_OFFSET_SPEED * (food_r / 1000) * 0.5;
        speed_right +=  ROBOT_OFFSET_SPEED * (food_l / 1000) * 0.5;
        break;
      case STARVING:
        speed_left =  ROBOT_OFFSET_SPEED * (food_r / 1000);
        speed_right =  ROBOT_OFFSET_SPEED * (food_l / 1000);
        break;
      default: break;
    }
    set_velocity(speed_left, speed_right);
}

NAMESPACE_END(csci3081);
