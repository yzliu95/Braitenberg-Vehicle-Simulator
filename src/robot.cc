/**
 * @file robot.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/food.h"
#include "src/robot.h"
#include "src/params.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
Robot::Robot() :
    motion_behavior_(this),
    type_(kExplore),
    sensor_light_left_(),
    sensor_light_right_(),
    sensor_food_left_(),
    sensor_food_right_(),
    hunger_level_(0),
    hunger_(NORMAL),
    food_sensor_switch_(true) {
  set_type(kRobot);
  set_color(ROBOT_COLOR);
  set_pose(ROBOT_INIT_POS);
  set_radius(random_num(ROBOT_RADIUS_LOWER, ROBOT_RADIUS_UPPER));
  motion_handler_ = new MotionHandlerRobotExplore (this);
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void Robot::TimestepUpdate(unsigned int dt) {
  hunger_level_++;
  if (reverse_) {
    reverse_ = motion_handler_->UpdateVelocity(reverse_, this);
    motion_behavior_.UpdatePose(dt, motion_handler_->get_velocity());
    return;
  }
  set_sensor_position();

  // Update heading as indicated by touch sensor
  if (food_sensor_switch_) {
    if (hunger_level_ < MINS_TILL_HUNGRY * 60 * 20 * 11 / get_radius()) {
      set_hunger(NORMAL);
    } else if (hunger_level_ <
      MINS_TILL_REALLY_HUNGRY * 60 * 20 * 11 / get_radius()) {
        // Normal hungry
        set_hunger(HUNGRY);
    } else if (hunger_level_ < MINS_TILL_STARVE * 60 * 20 * 11 / get_radius()) {
        // REALLY hungry
        set_hunger(STARVING);
    } else {
        // starved to death
        set_hunger(DEATH);
    }
  }

  motion_handler_->UpdateVelocity_Robot(get_reading_light(LEFT_SENSOR),
  get_reading_light(RIGHT_SENSOR), get_reading_food(LEFT_SENSOR),
  get_reading_food(RIGHT_SENSOR), hunger_);
  // Use velocity and position to update position
  motion_behavior_.UpdatePose(dt, motion_handler_->get_velocity());

  // Reset Sensor for next cycle
  sensor_touch_->Reset();
  resetsensor();
} /* TimestepUpdate() */

void Robot::Reset() {
  set_pose({static_cast<double>((30 + (random() % 19) * 50)),
        static_cast<double>((30 + (random() % 14) * 50))});
  motion_handler_->set_max_speed(ROBOT_MAX_SPEED);
  motion_handler_->set_max_angle(ROBOT_MAX_ANGLE);
  StopRobot();
  sensor_touch_->Reset();
  reset_reverse();
  set_color(ROBOT_COLOR);
  set_heading(random_num(0, 360));
  set_hunger(NORMAL);
  hunger_level_ = 0;
  resetsensor();
} /* Reset() */

void Robot::HandleCollision(EntityType object_type, ArenaEntity * object) {
  sensor_touch_->HandleCollision(object_type, object);
  switch (object_type) {
    case kTopWall:
    case kBottomWall:
    case kLeftWall:
    case kRightWall:
    case kRobot:
    set_reverse();
    break;
    case kFood:
    hunger_level_ = 0;
    break;
    case kLight:
    default: break;
  }
}

void Robot::StopRobot() {
  motion_handler_->set_velocity(0., 0.);
}

void Robot::notify_light(Pose light_position, double radius) {
  sensor_light_left_.calculateReading(light_position, radius,
    sensor_positions_[LEFT_SENSOR]);
  sensor_light_right_.calculateReading(light_position, radius,
    sensor_positions_[RIGHT_SENSOR]);
}

void Robot::notify_food(Pose food_position, double radius) {
  double d_x = food_position.x - get_pose().x;
  double d_y = food_position.y - get_pose().y;
  double distance = sqrt(d_x*d_x + d_y*d_y) - radius - get_radius();
  if ((distance <= 5) && (distance >= 0)) {hunger_level_ = 0;}
  sensor_food_left_.calculateReading(food_position, radius,
    sensor_positions_[LEFT_SENSOR]);
  sensor_food_right_.calculateReading(food_position, radius,
    sensor_positions_[RIGHT_SENSOR]);
}

void Robot::set_sensor_position() {
  double x = get_pose().x;
  double y = get_pose().y;
  double theta1 = get_pose().theta - 40.0;
  theta1 = theta1*M_PI/180;
  double theta2 = get_pose().theta + 40.0;
  theta2 = theta2*M_PI/180;

  sensor_positions_[LEFT_SENSOR].x = get_radius()*cos(theta1) + x;
  sensor_positions_[LEFT_SENSOR].y = get_radius()*sin(theta1) + y;
  sensor_positions_[RIGHT_SENSOR].x = get_radius()*cos(theta2) + x;
  sensor_positions_[RIGHT_SENSOR].y = get_radius()*sin(theta2) + y;
}
NAMESPACE_END(csci3081);
