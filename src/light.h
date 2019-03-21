/**
 * @file light.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_LIGHT_H_
#define SRC_LIGHT_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>

#include "src/arena_mobile_entity.h"
#include "src/common.h"
#include "src/entity_type.h"
#include "src/motion_handler_robot.h"
#include "src/motion_behavior_differential.h"
#include "src/pose.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief Class representing an immobile light within the Arena.
 *
 * Since lights are immobile, the Light class is very simple.
 */
class Light : public ArenaMobileEntity {
 public:
  /**
   * @brief Constructor.
   */
  Light();

  /** @brief Reset light instacnce for a new start */
  void Reset() override;

  /** @brief update light's status for every dt*/
  void TimestepUpdate(unsigned int dt) override;

  /**
   * @brief Get the name of the Light for visualization purposes, and to
   * aid in debugging.
   */
  std::string get_name() const override {
    return "Light" + std::to_string(get_id());
  }

  /**
   * @brief Handles the collision by setting the sensor to activated.
   */
  void HandleCollision(EntityType object_type, ArenaEntity * object = NULL);

 private:
  // Manages pose and wheel velocities that change with time and collisions.
  MotionHandlerRobot motion_handler_;
  // Calculates changes in pose foodd on elapsed time and wheel velocities.
  MotionBehaviorDifferential motion_behavior_;
};

NAMESPACE_END(csci3081);

#endif  // SRC_LIGHT_H_
