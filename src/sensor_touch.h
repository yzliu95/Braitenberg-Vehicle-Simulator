/**
 * @file sensor_touch.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_SENSOR_TOUCH_H_
#define SRC_SENSOR_TOUCH_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <utility>
#include <vector>
#include <iostream>

#include "src/common.h"
#include "src/pose.h"
#include "src/entity_type.h"
#include "src/arena_entity.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Classes
 ******************************************************************************/
/**
 * @brief Class representing a touch sensor.
 *
 * Touch or "bump" sensors are "active" when pressed. For our purposes, imagine
 * a series of bump sensors around the perimeter of an entity. A collision will
 * activate the sensor at a particular point of contact, which translates to an
 * angle of contact.
 *
 * SensorTouch can be observed for collision events.
 */
class SensorTouch {
 public:
  /**
   * @brief Constructor.
   */
  SensorTouch() : point_of_contact_(0, 0) {}

  /**
   * @brief Getter method for the point of contact.
   *
   * Should only be called when the sensor is activated.
   *
   * @return The latest point of contact.
   */
  const Pose &get_point_of_contact() { return point_of_contact_; }

  /**
   * @brief Setter method for the point of contact.
   *
   * @param p The new point of contact.
   */
  void set_point_of_contact(const Pose &p) { point_of_contact_ = p; }

  /**
   * @brief Getter for output, which is true when collision occurs.
   */
  bool get_output() const { return output_; }

  /**
   * @brief Modify heading to presumably move away from collision.
   *
   * Currently, no information is used to determine point of contact. The
   * heading should really only change when it collides with something in
   * front of it (as opposed to something running into the entity from behind.)
   * The ArenaEntity can be used to determine the point of contact.
   */
  void HandleCollision(
    __unused EntityType object_type, __unused ArenaEntity * object);

  /**
   * @brief Reset the sensor.
   */
  void Reset() {
    output_ = false;
  }

 private:
  Pose point_of_contact_;  // currently unused
  bool output_{false};
};

NAMESPACE_END(csci3081);

#endif  // SRC_SENSOR_TOUCH_H_
