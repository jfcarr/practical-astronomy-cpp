#include "pa_coordinates.h"
#include "pa_macros.h"
#include "pa_types.h"
#include "pa_util.h"
#include <cmath>

using namespace pa_types;
using namespace pa_util;

/**
 * \brief Convert Angle (degrees,minutes,seconds) to Decimal Degrees
 *
 * @param degrees
 * @param minutes
 * @param seconds
 *
 * @return Decimal Degrees
 */
double PACoordinates::angle_to_decimal_degrees(double degrees, double minutes,
                                               double seconds) {
  double a = std::abs(seconds) / 60;
  double b = (std::abs(minutes) + a) / 60;
  double c = std::abs(degrees) + b;
  double d = (degrees < 0 || minutes < 0 || seconds < 0) ? -c : c;

  return d;
}

/**
 * \brief Convert Decimal Degrees to an Angle (degrees, minutes, and seconds)
 *
 * @param decimal_degrees
 *
 * @return tuple <double degrees, double minutes, double seconds>
 */
std::tuple<double, double, double>
PACoordinates::decimal_degrees_to_angle(double decimal_degrees) {
  double unsigned_decimal = std::abs(decimal_degrees);
  double total_seconds = unsigned_decimal * 3600;
  double seconds_2_dp = round(std::fmod(total_seconds, 60), 2);
  double corrected_seconds = (seconds_2_dp == 60) ? 0 : seconds_2_dp;
  double corrected_remainder =
      (seconds_2_dp == 60) ? total_seconds + 60 : total_seconds;
  double minutes = std::fmod(floor(corrected_remainder / 60), 60);
  double unsigned_degrees = floor(corrected_remainder / 3600);
  double signed_degrees =
      (decimal_degrees < 0) ? -1 * unsigned_degrees : unsigned_degrees;

  return std::tuple<double, double, double>{signed_degrees, minutes,
                                            floor(corrected_seconds)};
}