#include "pa_util.h"
#include <cmath>
#include <iostream>

namespace pa_util {
/**
 * Determine if year is a leap year.
 *
 * @return Is a leap year? (true/false)
 */
bool is_leap_year(int input_year) {
  double year = (double)input_year;

  if ((int)year % 4 == 0) {
    if ((int)year % 100 == 0) {
      return ((int)year % 400 == 0) ? true : false;
    } else {
      return true;
    }
  } else {
    return false;
  }
}

/**
 * Round a value to a set number of decimal places.
 *
 * @param input Input value to be rounded.
 * @param places Number of decimal places.
 *
 * @return Rounded input value.
 */
double round(double input, int places) {
  double multiplier = pow(10, places);

  double a = input * multiplier;
  a = (a >= 0) ? a + 0.5 : a - 0.5;

  return (int)a / multiplier;
}

/**
 * \brief Convert degrees to radians
 */
double degrees_to_radians(double degrees) { return (degrees * M_PI) / 180; }

/**
 * \brief Convert radians to degrees
 */
double radians_to_degrees(double radians) { return (radians * 180) / M_PI; }
} // namespace pa_util