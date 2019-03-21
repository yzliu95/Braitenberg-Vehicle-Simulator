/**
 * @file entity_type.h
 *
 * @copyright Yuanzhe Liu, All rights reserved.
 */

#ifndef SRC_ROBOT_TYPE_H_
#define SRC_ROBOT_TYPE_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/common.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

enum RobotType {
  kFear, kExplore, kAggressive, kLove
};

NAMESPACE_END(csci3081);

#endif  // SRC_ROBOT_TYPE_H_
