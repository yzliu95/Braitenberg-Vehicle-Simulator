/**
 * @file main.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <iostream>
#include "src/arena_params.h"
#include "src/controller.h"
#include "src/graphics_arena_viewer.h"

/*******************************************************************************
 * Non-Member Functions
 ******************************************************************************/
int main(__unused int argc, __unused char **argv) {
  // The controller creates both the arena and viewer
  auto *controller = new csci3081::Controller;

  // The controller will call Run of the viewer
  controller->Run();
  return 0;
}
