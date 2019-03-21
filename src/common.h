/**
 * @file common.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_COMMON_H_
#define SRC_COMMON_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <random>

/*******************************************************************************
 * Macros
 ******************************************************************************/
#define NAMESPACE_BEGIN(name) namespace name {
#define NAMESPACE_END(name) }

/**
 * This should be placed in front of any variable defined but not used to
 * satisfy the compiler - otherwise a warning is given.
 */
#define __unused __attribute__((unused))

/*******************************************************************************
 * Common Template Functions
 ******************************************************************************/
/**
 * @brief A template method for random number generation.
 *
 * @tparam T The type of the input/return values. Can be any primitive numeric
 * type (e.g. `int`).
 * @param min The (inclusive) minimum of the generated value.
 * @param max The (exclusive) maximum of the generated value.
 *
 * @return A pseudo-randomly generated number in the range of [min, max).
 *
 * Reference: https://stackoverflow.com/a/19728404
 */
template <typename T>
T random_num(T min, T max) {
  static std::random_device rd;
  static std::mt19937 rng(rd());

  std::uniform_real_distribution<> dis(min, max);
  return static_cast<T>(dis(rng));
}

#endif  // SRC_COMMON_H_
