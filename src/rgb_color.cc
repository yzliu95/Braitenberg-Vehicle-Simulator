/**
 * @file rgb_color.cc
 *
 * @copyright 2018 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/rgb_color.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void RgbColor::Set(RgbColorEnum value) {
  switch (value) {
    case kBlack:
      r = 0;
      g = 0;
      b = 0;
      break;
    case kWhite:
      r = 255;
      g = 255;
      b = 255;
      break;
    case kRed:
      r = 255;
      g = 0;
      b = 0;
      break;
    case kGreen:
      r = 0;
      g = 255;
      b = 0;
      break;
    case kBlue:
      r = 0;
      g = 0;
      b = 255;
      break;
    case kYellow:
      r = 255;
      g = 255;
      b = 50;
      break;
    case kOrange:
      r = 255;
      g = 130;
      b = 0;
      break;
    case kPurple:
      r = 75;
      g = 0;
      b = 150;
      break;
    default:
      assert(false);
      break;
  }
}

NAMESPACE_END(csci3081);
