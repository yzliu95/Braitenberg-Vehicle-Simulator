/**
 * @file rgb_color.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_RGB_COLOR_H_
#define SRC_RGB_COLOR_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <assert.h>

#include "src/common.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

enum RgbColorEnum {
  kRed,
  kGreen,
  kBlue,
  kYellow,
  kOrange,
  kPurple,
  kWhite,
  kBlack
};

/*******************************************************************************
 * Struct Definitions
 ******************************************************************************/
/**
 * @brief Struct representing a rgb_color.
 *
 * Internally uses RGBA values to represent the rgb_color.
 */
struct RgbColor {
 public:
  int r{0};
  int g{0};
  int b{0};

  /**
   * @brief Default constructor.
   *
   * Initialize RGB all to 0 (kWhite).
   */
  RgbColor() {}

  /**
   * @brief Constructor for Rgb_Color.
   *
   * @param r_in The R component of the rgb_color.
   * @param g_in The G component of the rgb_color.
   * @param b_in The B component of the rgb_color.
   */
  RgbColor(int r_in, int g_in, int b_in) : r(r_in), g(g_in), b(b_in) {}

  void Set(RgbColorEnum value);
};

NAMESPACE_END(csci3081);

#endif  // SRC_RGB_COLOR_H_
