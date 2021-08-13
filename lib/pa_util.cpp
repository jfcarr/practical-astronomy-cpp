#include "pa_util.h"
#include <cmath>
#include <iostream>

namespace pa_util {
/**
 * Determine if year is a leap year.
 *
 * @return Is a leap year? (true/false)
 */
bool IsLeapYear(int inputYear) {
  double year = (double)inputYear;

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
 * \brief Round a value to a set number of decimal places.
 *
 * WARNING: accurate to about 7 places, then the result of the pow() operation
 * exceeds what a double can handle.
 *
 * @param input Input value to be rounded.
 * @param places Number of decimal places.
 *
 * @return Rounded input value.
 */
double Round(double input, int places) {
  bool isNegative = (input < 0) ? true : false;

  long double multiplier = pow(10, places);

  if (isNegative) {
    input = std::abs(input);
  };

  long double a = input * multiplier;
  a = (a >= 0) ? a + 0.5 : a - 0.5;

  double returnValue =
      floor(a) / multiplier; // floor() gives good results for more places (7+)
                             // than the original (int) cast.

  return (isNegative) ? -(returnValue) : returnValue;
}

/**
 * \brief Convert degrees to radians
 */
double DegreesToRadians(double degrees) { return (degrees * M_PI) / 180; }

/**
 * \brief Convert radians to degrees
 */
double RadiansToDegrees(double radians) { return (radians * 180) / M_PI; }
} // namespace pa_util