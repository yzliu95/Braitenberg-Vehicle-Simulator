/**
 * @file wheel_velocity.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_WHEEL_VELOCITY_H_
#define SRC_WHEEL_VELOCITY_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/common.h"
#include "src/params.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief A simple representation of the position/orientation of an entity
 * within the Arena.
 *
 * NOTE: Origin (0,0) is at the upper left corner of the Arena.
 */
struct WheelVelocity {
 public:
  /**
   * @brief Default constructor. Initialize the pose to (0,0,0)
   */
  WheelVelocity()
    : left(STARTING_VELOCITY), right(STARTING_VELOCITY) {}

  /**
   * @brief Constructor
   *
   * @param in_x The X component of the Pose.
   * @param in_y The Y component of the Pose.
   */
  WheelVelocity(double l, double r) : left(l), right(r) {}


  /**
   * @brief Default assignment operator. Simply copies the (x,y) values of
   * another Pose.
   *
   * @param other The Pose object to copy from.
   *
   * @return The left-hand-side Pose object that is now identical (in value)
   * to `other`.
   */
  WheelVelocity &operator=(const WheelVelocity &other) = default;

  double left;
  double right;
};

NAMESPACE_END(csci3081);

#endif /* SRC_WHEEL_VELOCITY_H_ */
