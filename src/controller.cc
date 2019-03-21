/**
 * @file controller.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <nanogui/nanogui.h>
#include <string>

#include "src/arena_params.h"
#include "src/common.h"
#include "src/controller.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Constructor
 ******************************************************************************/
Controller::Controller() : last_dt(0), aparams_() {
  // Initialize default properties for various arena entities
  aparams_.n_lights = N_LIGHTS;
  aparams_.n_robots = N_ROBOTS;
  aparams_.n_foods = N_FOODS;
  aparams_.x_dim = ARENA_X_DIM;
  aparams_.y_dim = ARENA_Y_DIM;

  // use the default params to construct an arena
  arena_ = new Arena(&aparams_);

  // Start up the graphics (which creates the arena).
  // Run() will enter the nanogui::mainloop().
  viewer_ = new GraphicsArenaViewer(&aparams_, arena_, this);
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void Controller::Run() { viewer_->Run(); }

void Controller::AdvanceTime(double dt) {
  if ((last_dt + dt) <= .05) {
    last_dt += dt;
    return;
  }
  last_dt = 0;
  arena_->AdvanceTime(dt);
}

/* forward com to arena */
void Controller::AcceptCommunication(Communication com) {
  arena_->AcceptCommand(ConvertComm(com));
}

/** Converts communication from one source to appropriate communication to
 * the other source. Or call the reset function to reset the simulation
 */
Communication Controller::ConvertComm(Communication com) {
  switch (com) {
    case (kPlay) : return kPlay;
    case (kPause) : return kPause;
    case (kFoodOn) :
      aparams_.food_exist = true;
      break;
    case (kFoodOff) :
      aparams_.food_exist = false;
      break;
    case (kNewGame) : reset();
      break;
    default: return kNone;
  }
  return kNone;
}

/* delete arena and create a new one according to new params */
void Controller::reset() {
  delete arena_;
  arena_ = new Arena(&aparams_);
}

/* update entitiy count in params */
void Controller::updateEntityCount(EntityType t, int n) {
  switch (t) {
    case (kRobot) :
      aparams_.n_robots = n;
      break;
    case (kLight) :
      aparams_.n_lights = n;
      break;
    case (kFood) :
      aparams_.n_foods = n;
      break;
    default: break;
  }
}

/* update fear robot ratio in params */
void Controller::updateRobotRatio(int r) {
  aparams_.r_fear = r;
}

/* update sensor calculation constant in params */
void Controller::updateSensitivity(int s) {
  aparams_.sensitivity = s;
}

NAMESPACE_END(csci3081);
