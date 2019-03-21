/**
 * @file communication.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_COMMUNICATION_H_
#define SRC_COMMUNICATION_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/common.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

enum Communication {
  // communications from GUI to controller
  kPlay,
  kPause,
  kNewGame,
  kFoodOn,
  kFoodOff,

  // communications from controller to Arena
  kReset,

  // communications from Arena to Controller
  kLost,

  kNone   // in case it is needed
};

NAMESPACE_END(csci3081);

#endif  // SRC_COMMUNICATION_H_
