/**
 * @file arena.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <algorithm>
#include <iostream>

#include "src/arena.h"
#include "src/arena_params.h"
#include "src/robot_type.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
Arena::Arena(const struct arena_params *const params)
    : x_dim_(params->x_dim),
      y_dim_(params->y_dim),
      factory_(new EntityFactory),
      robot_(),
      entities_(),
      mobile_entities_(),
      game_status_(PLAYING),
      pause_status_(true) {
  AddRobot(params->n_robots, params->food_exist, params->sensitivity);
  int r = static_cast<int>(params->r_fear * params->n_robots / 100);
  for (auto rob : robot_) {
    if ((rob->get_id() - 1) < r) {
    rob->set_robot_type(kFear);
    rob->changetofear();
  }
  }
  AddEntity(kLight, params->n_lights);
  if (params->food_exist) {
    AddEntity(kFood, params->n_foods);
  }
}

Arena::~Arena() {
  for (auto ent : entities_) {
    delete ent;
  } /* for(ent..) */
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void Arena::AddRobot(int quantity, bool b, int sensitivity) {
  for (int i = 0; i < quantity; i++) {
    Robot *robot = dynamic_cast<Robot *>(factory_->CreateEntity(kRobot));
    robot->setFoodSensorSwitch(b);
    robot->setSensitivity(sensitivity);
    robot_.push_back(robot);
    entities_.push_back(robot);
    mobile_entities_.push_back(robot);
  }
}

void Arena::AddEntity(EntityType type, int quantity) {
  if (type == kFood) {
    for (int i = 0; i < quantity; i++) {
      entities_.push_back(factory_->CreateEntity(kFood));
    }
  } else {
    for (int i = 0; i < quantity; i++) {
      Light* light =
        dynamic_cast<Light *>(factory_->CreateEntity(kLight));
      entities_.push_back(light);
      mobile_entities_.push_back(light);}
    }
}
/**
 * Resets the arena. Call reset for every entity it has.
 */
void Arena::Reset() {
  set_game_status(PLAYING);
  pause_status_ = true;
  for (auto ent : entities_) {
    ent->Reset();
  } /* for(ent..) */
} /* reset() */

// The primary driver of simulation movement. Called from the Controller
// but originated from the graphics viewer.
void Arena::AdvanceTime(double dt) {
  if (!(dt > 0)) {
    return;
  }
  if (pause_status_) { return; }
  if (get_game_status() == LOST) {return;}
  for (size_t i = 0; i < 1; ++i) {  // this loop can adjust the simulation speed
    UpdateEntitiesTimestep();
  } /* for(i..) */
} /* AdvanceTime() */

/**
 *  This is called by controller. It will call every entity it has and perform
 * update on every one of them. It also handles collision either by calling
 * resposition function.
 */
void Arena::UpdateEntitiesTimestep() {
  // In the beginning of every timestep, reset all sensors
  for (auto rob : robot_) {
    rob->resetsensor();
  }
  // First, update the position of all entities, according to their current
  // velocities. Also when an entity is updated, it should notify robot
  // (observer pattern)
  for (auto ent : entities_) {
    if (ent->get_type() != kRobot) {
     ent->TimestepUpdate(1);
      if (kLight == ent->get_type()) {
        for (auto rob : robot_) {
          rob->notify_light(ent->get_pose(), ent->get_radius());
        }
      } else {
        for (auto rob : robot_) {
          rob->notify_food(ent->get_pose(), ent->get_radius());
        }
      }
    }
  }
  // Then update all robots, if a robot is too starved, then simulation ends
  for (auto ent : entities_) {
    if (ent->get_type() == kRobot) {
      if ((dynamic_cast<Robot*>(ent))->is_starving()) { set_game_status(LOST); }
      ent->TimestepUpdate(1);
    }
  }
  // Finally, call RepositionEntities() function to adjust any overlap existing
  RepositionEntities();
}

/* Goes thru every entities and adjust overlap when needed */
void Arena::RepositionEntities() {
  /* Determine if any mobile entity is colliding with wall.
  * Adjust the position accordingly so it doesn't overlap.
  */
  for (auto &ent1 : mobile_entities_) {
     EntityType wall = GetCollisionWall(ent1);
     if (kUndefined != wall) {  // if colliding with wall
       AdjustWallOverlap(ent1, wall);
       if (ent1->get_type() == kRobot) {  // if the robot hits something
         (dynamic_cast<Robot*>(ent1)) -> HandleCollision(wall);
       } else {  // if an light hits something
         (dynamic_cast<Light*>(ent1))-> HandleCollision(wall);
       }
     }
   /* Determine if that mobile entity is colliding with any other entity.
    * Adjust the position accordingly so they don't overlap.
    */
     for (auto &ent2 : entities_) {
       if (ent2 == ent1) { continue; }
       if (IsColliding(ent1, ent2)) {
         if (ent2 -> get_type() != kFood) {
           AdjustEntityOverlap(ent1, ent2);
         }
         if (ent1->get_type() == kRobot) {
          (dynamic_cast<Robot*>(ent1))->HandleCollision(ent2->get_type(), ent2);
         } else {
           (dynamic_cast<Light*>(ent1))->HandleCollision(wall);
         }
       }
     }
  }
}

/* Determine if the entity is colliding with a wall.
* Always returns an entity type. If not collision, returns kUndefined.
*/
EntityType Arena::GetCollisionWall(ArenaMobileEntity *const ent) {
  if (ent->get_pose().x + ent->get_radius() >= x_dim_) {
    return kRightWall;  // at x = x_dim_
  } else if (ent->get_pose().x - ent->get_radius() <= 0) {
    return kLeftWall;  // at x = 0
  } else if (ent->get_pose().y + ent->get_radius() >= y_dim_) {
    return kBottomWall;  // at y = y_dim
  } else if (ent->get_pose().y - ent->get_radius() <= 0) {
    return kTopWall;  // at y = 0
  } else {
    return kUndefined;
  }
}

/* The entity type indicates which wall the entity is colliding with.
* This determines which way to move the entity to set it slightly off the wall.
*/
void Arena::AdjustWallOverlap(ArenaMobileEntity *const ent, EntityType object) {
  Pose entity_pos = ent->get_pose();
  switch (object) {
    case (kRightWall):  // at x = x_dim_
    ent->set_position(x_dim_-(ent->get_radius()+5), entity_pos.y);
    break;
    case (kLeftWall):  // at x = 0
    ent->set_position(ent->get_radius()+5, entity_pos.y);
    break;
    case (kTopWall):  // at y = 0
    ent->set_position(entity_pos.x, ent->get_radius()+5);
    break;
    case (kBottomWall):  // at y = y_dim_
    ent->set_position(entity_pos.x, y_dim_-(ent->get_radius()+5));
    break;
    default: break;
  }
}

/* Calculates the distance between the center points to determine overlap */
bool Arena::IsColliding(
  ArenaMobileEntity * const mobile_e,
  ArenaEntity * const other_e) {
    if (((mobile_e->get_type() == kLight) && (other_e->get_type() == kLight))
      ||((mobile_e->get_type()== kRobot) && (other_e->get_type() == kRobot))
      ||((mobile_e->get_type() == kRobot) && (other_e->get_type() == kFood))) {
        // if light-light or robot-robot
      double delta_x = other_e->get_pose().x - mobile_e->get_pose().x;
      double delta_y = other_e->get_pose().y - mobile_e->get_pose().y;
      double distance_between = sqrt(delta_x*delta_x + delta_y*delta_y);
      return
      (distance_between <= (mobile_e->get_radius() + other_e->get_radius()));
    }
  return false;
}

/** This is called when it is known that the two entities overlap.
* We determine by how much they overlap then move the mobile entity to
* the edge of the other
*
* Determine the distance distance_between two instances
*(e.g. overload operator -)
*/
void Arena::AdjustEntityOverlap(ArenaMobileEntity * const mobile_e,
  ArenaEntity *const other_e) {
    double delta_x = mobile_e->get_pose().x - other_e->get_pose().x;
    double delta_y = mobile_e->get_pose().y - other_e->get_pose().y;
    double distance_between = sqrt(delta_x*delta_x + delta_y*delta_y);
    double distance_to_move =
      mobile_e->get_radius() + other_e->get_radius() - distance_between + 5;
    double angle = atan2(delta_y, delta_x);
    mobile_e->set_position(
       mobile_e->get_pose().x+cos(angle)*distance_to_move,
       mobile_e->get_pose().y+sin(angle)*distance_to_move);
}

// Accept communication from the controller. Dispatching as appropriate.
/** Call the appropriate Robot functions to implement user input
  * for controlling the robot.
  */
void Arena::AcceptCommand(Communication com) {
  switch (com) {
    case(kPlay):
    pause_status_ = false;
    break;
    case(kPause):
    pause_status_ = true;
    break;
    case(kReset):
    Reset();
    break;
    case(kNone):
    default: break;
  }
} /* AcceptCommand */

NAMESPACE_END(csci3081);
