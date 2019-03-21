/**
 * @file arena_mobile_entity.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_ARENA_MOBILE_ENTITY_H_
#define SRC_ARENA_MOBILE_ENTITY_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <algorithm>

#include "src/arena_entity.h"
#include "src/common.h"
#include "src/sensor_touch.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief A mobile entity in the Arena, capable of updating its own position
 * and/or velocity when asked by the simulation.
 *
 * All mobile entities must have a heading angle so that their orientation can
 * be properly drawn by the GraphicsArenaViewer.
 *
 * Since this is also a base class, many of its methods are intuitively
 * `virtual`.
 */
class ArenaMobileEntity : public ArenaEntity {
 public:
  /**
   * @brief ArenaMobileEntity's constructor.
   */

  ArenaMobileEntity()
    : ArenaEntity(),
      speed_(0),
      reverse_(false),
      sensor_touch_(new SensorTouch) {
        set_mobility(true);
  }
  ArenaMobileEntity(const ArenaMobileEntity& other) = delete;
  ArenaMobileEntity& operator=(const ArenaMobileEntity& other) = delete;


  virtual double get_speed() { return speed_; }
  virtual void set_speed(double sp) { speed_ = sp; }

  /**
   * @brief Get a pointer to the ArenaMobileEntity's touch sensor.
  */
  SensorTouch * get_touch_sensor() { return sensor_touch_; }

  /** Getter to get the reverse mode activation status */
  bool get_reverse() {
    return reverse_;
  }

  /** Set the robot to reverse mode */
  void set_reverse() {
    reverse_ = true;
  }

  /** reset for reverse_ */
  void reset_reverse() {
    reverse_ = false;
  }

 private:
  double speed_;

 protected:
  // Using protected allows for direct access to sensor within entity.
  // It was awkward to have get_touch_sensor()->get_output() .
  // state machine to determine whether the obstale is in reverse mode or not
  bool reverse_;

  SensorTouch * sensor_touch_;
};

NAMESPACE_END(csci3081);

#endif  // SRC_ARENA_MOBILE_ENTITY_H_
