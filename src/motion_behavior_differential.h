/**
 * @file motion_behavior_differential.h
 *
 * @copyright 2018 3081 Staff, All rights reserved.
 */

#ifndef SRC_MOTION_BEHAVIOR_DIFFERENTIAL_H_
#define SRC_MOTION_BEHAVIOR_DIFFERENTIAL_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/common.h"
#include "src/pose.h"
#include "src/wheel_velocity.h"
#include "src/motion_behavior.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief A simple model of differential drive kinematics based on the notes
 * here:
 * ~https://chess.eecs.berkeley.edu/eecs149/documentation/differentialDrive.pdf~
 */
class MotionBehaviorDifferential : public MotionBehavior {
 public:
  explicit MotionBehaviorDifferential(ArenaMobileEntity * entity)
      : MotionBehavior(entity) , radius_(entity_->get_radius()),
        temp_vel_(0, 0) {
  }

  MotionBehaviorDifferential(const MotionBehaviorDifferential& other) = default;
  MotionBehaviorDifferential&
    operator=(const MotionBehaviorDifferential& other) = default;

  /**
   * @brief Update the pose of an entity based on its current position and how
   * many seconds have elapsed since the last update.
   *
   * @param[in] dt Elapsed time interval.
   * @param[in] vel The WheelVelocity stored within the motion handler.
   *
   * Calculates the new pose (i.e. position and heading) based on a model of
   * differential drive. If both wheels have equivalent velocity, it travels
   * in the direction of its heading. If one wheel is faster than the other,
   * this drives the entity in an arc (e.g. if WheelVelocity.right > .left,
   * then the entity will move in an arc turning to the left relative to its
   * heading.)
   */
  void UpdatePose(double dt, WheelVelocity vel) override;

 private:
  /**
   * @brief Get the radius of the ICC
   */
  double icc_radius() const;

  /**
   * @brief Get the angular velocity, in rad/sec.
   */
  double omega() const;

  /**
   * @brief Get the Instantaneous Center of Curvature (ICC) of the entity.
   *
   * @param pose The entities current pose.
   *
   * @return The center of curvature (theta component of pose unused).
   */
  struct Pose calc_icc(struct Pose pose) const;

  double radius_;

  // Velocity is stored in motion handler. Value is passed in here and used to
  // calculate new pose. Its used in various functions, hence the temp var
  // instead of passing it around from function to function.
  WheelVelocity temp_vel_;
};

NAMESPACE_END(csci3081);

#endif  // SRC_MOTION_BEHAVIOR_DIFFERENTIAL_H_
