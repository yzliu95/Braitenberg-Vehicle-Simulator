/**
 * @file light.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/light.h"
#include "src/params.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
Light::Light():
  motion_handler_(this),
  motion_behavior_(this) {
  set_color(LIGHT_COLOR);
  set_pose(LIGHT_POSITION);
  set_radius(LIGHT_RADIUS);
  set_type(kLight);
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void Light::TimestepUpdate(unsigned int dt) {
  reverse_ = motion_handler_.UpdateVelocity(reverse_, this);
  motion_behavior_.UpdatePose(dt, motion_handler_.get_velocity());
} /* TimestepUpdate() */

void Light::HandleCollision(EntityType object_type, ArenaEntity * object) {
  sensor_touch_->HandleCollision(object_type, object);
  if (!reverse_) {
    set_reverse();
  }
}

void Light::Reset() {
  Pose new_pos_ = {static_cast<double>((30 + (random() % 19) * 50)),
        static_cast<double>((30 + (random() % 14) * 50))};
  set_pose(new_pos_);
  set_heading(random_num(0, 360));
  set_radius(random_num(LIGHT_MIN_RADIUS, LIGHT_MAX_RADIUS));
  reverse_ = false;
}

NAMESPACE_END(csci3081);
