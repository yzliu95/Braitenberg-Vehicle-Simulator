/**
 * @file robot.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_ROBOT_H_
#define SRC_ROBOT_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>

#include "src/arena_mobile_entity.h"
#include "src/common.h"
#include "src/motion_handler_robot_fear.h"
#include "src/motion_handler_robot_explore.h"
#include "src/motion_behavior_differential.h"
#include "src/entity_type.h"
#include "src/robot_type.h"
#include "src/sensor_light.h"
#include "src/sensor_food.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

class MotionBehaviorDifferential;

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief Class representing a robot within the arena.
 *
 * Robots are composed of a motion handler, motion behavior, and touch sensor.
 * These classes interact to maintain the pose (position and heading) of the
 * robot. At each time step, the wheel velocities are used to calculate the
 * next pose of the robot. The handler manages the pose and user requests. The
 * behavior calculates the new pose based on wheel velocities.
 *
 * Robots can be controlled through keypress, which modify wheel velocities.
 *
 * The touch sensor is activated when the robot collides with an object.
 * The heading is modified after a collision to move the robot away from the
 * other object.
 */
class Robot : public ArenaMobileEntity {
 public:
  /**
   * @brief Constructor using initialization values from params.h.
   */

  Robot();
  Robot(const Robot& other) = default;
  Robot& operator = (const Robot& other) = default;
  /**
   * @brief Reset the Robot to a newly constructed state (needed for reset
   * button to work in GUI).
   */
  void Reset() override;

  /**
   * @brief Update the Robot's position and velocity after the specified
   * duration has passed.
   *
   * @param dt The # of timesteps that have elapsed since the last update.
   */
  void TimestepUpdate(unsigned int dt) override;


  /**
   * @brief Handles the collision by setting the sensor to activated.
   */
  void HandleCollision(EntityType object_type, ArenaEntity * object = NULL);

  /**
   * @brief Get the name of the Robot for visualization and for debugging.
   */
  std::string get_name() const override { return "Robot"; }
  std::string get_type_name() const {
    if (type_ == kExplore) {
      return "Explore";
    } else {
      return "Fear";
    }
  }

  /**
  * @brief Completely stop a robot
  */
  void StopRobot();

  // MotionHandlerRobot get_motion_handler() { return motion_handler_; }

  MotionBehaviorDifferential get_motion_behavior() { return motion_behavior_; }

  /**
  * reset all sensor readings
  */
  void resetsensor() {
    sensor_light_left_.Reset();
    sensor_food_left_.Reset();
    sensor_light_right_.Reset();
    sensor_food_right_.Reset();
  }

  /**
  * add the specific light position's reading to the sensor
  */
  void notify_light(Pose position, double radius);
  /**
  * add the specific food position's reading to the sensor
  */
  void notify_food(Pose position, double radius);

  /**
  * Calculate sensor positions
  */
  void set_sensor_position();

  /**
  * get the specific light sensor reading
  */
  double get_reading_light(int i) {
    if (i == LEFT_SENSOR) {
      return sensor_light_left_.get_reading();
    } else {
      return sensor_light_right_.get_reading();
    }
  }

  /**
  * get the specific food sensor reading
  */
  double get_reading_food(int i) {
    if (i == LEFT_SENSOR) {
      return sensor_food_left_.get_reading();
    } else {
      return sensor_food_right_.get_reading();
    }
  }


  void set_robot_type(RobotType t) { type_ = t; }

  RobotType get_robot_type() {return type_;}

  void set_hunger(int h) {hunger_ = h;}

  /** Determine if a robot is starved to death or not */
  bool is_starving() {return (hunger_ == DEATH);}

  /** change a robot's type to fear, strategy pattern */
  void changetofear() {motion_handler_ = new MotionHandlerRobotFear(this);}

  void setFoodSensorSwitch(bool b) { food_sensor_switch_ = b; }

  void setSensitivity(int s) {
    sensor_light_left_.set_sensitivity(s);
    sensor_light_right_.set_sensitivity(s);
    sensor_food_left_.set_sensitivity(s);
    sensor_food_right_.set_sensitivity(s);
  }

 private:
  // Manages pose and wheel velocities that change with time and collisions.
  MotionHandlerRobot* motion_handler_ {nullptr};
  // Calculates changes in pose based on elapsed time and wheel velocities.
  MotionBehaviorDifferential motion_behavior_;
  // sensor-related attributes
  RobotType type_;

  // store left and right sensor positions
  Pose sensor_positions_[2];

  // left and right sensors
  SensorLight sensor_light_left_;
  SensorLight sensor_light_right_;

  SensorFood sensor_food_left_;
  SensorFood sensor_food_right_;

  int hunger_level_;

  // state variable of hunger: NORMAL = 0, HUNGRY = 1; STARVING = 2, DEATH = 3
  int hunger_;

  // determain if the robot should sense food or not
  bool food_sensor_switch_;
};

NAMESPACE_END(csci3081);

#endif  // SRC_ROBOT_H_
