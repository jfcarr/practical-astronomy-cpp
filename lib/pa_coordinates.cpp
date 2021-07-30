#include "pa_coordinates.h"
#include "pa_macros.h"
#include "pa_types.h"
#include "pa_util.h"
#include <cmath>

using namespace pa_types;
using namespace pa_util;
using namespace pa_macros;

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

/**
 * \brief Convert Right Ascension to Hour Angle
 *
 * @return tuple <double hour_angle_hours, double hour_angle_minutes, double
 * hour_angle_seconds>
 */
std::tuple<double, double, double> PACoordinates::right_ascension_to_hour_angle(
    double ra_hours, double ra_minutes, double ra_seconds, double lct_hours,
    double lct_minutes, double lct_seconds, bool is_daylight_savings,
    int zone_correction, double local_day, int local_month, int local_year,
    double geographical_longitude) {
  int daylight_saving = (is_daylight_savings) ? 1 : 0;

  double hour_angle = pa_macros::right_ascension_to_hour_angle(
      ra_hours, ra_minutes, ra_seconds, lct_hours, lct_minutes, lct_seconds,
      daylight_saving, zone_correction, local_day, local_month, local_year,
      geographical_longitude);

  int hour_angle_hours = decimal_hours_hour(hour_angle);
  int hour_angle_minutes = decimal_hours_minute(hour_angle);
  double hour_angle_seconds = decimal_hours_second(hour_angle);

  return std::tuple<double, double, double>{
      hour_angle_hours, hour_angle_minutes, hour_angle_seconds};
}

/**
 * \brief Convert Hour Angle to Right Ascension
 *
 * tuple <double right_ascension_hours, double right_ascension_minutes, double
 * right_ascension_seconds>
 */
std::tuple<double, double, double> PACoordinates::hour_angle_to_right_ascension(
    double hour_angle_hours, double hour_angle_minutes,
    double hour_angle_seconds, double lct_hours, double lct_minutes,
    double lct_seconds, bool is_daylight_savings, int zone_correction,
    double local_day, int local_month, int local_year,
    double geographical_longitude) {
  int daylight_saving = (is_daylight_savings) ? 1 : 0;

  double right_ascension = pa_macros::hour_angle_to_right_ascension(
      hour_angle_hours, hour_angle_minutes, hour_angle_seconds, lct_hours,
      lct_minutes, lct_seconds, daylight_saving, zone_correction, local_day,
      local_month, local_year, geographical_longitude);

  int right_ascension_hours = decimal_hours_hour(right_ascension);
  int right_ascension_minutes = decimal_hours_minute(right_ascension);
  int right_ascension_seconds = decimal_hours_second(right_ascension);

  return std::tuple<double, double, double>{
      right_ascension_hours, right_ascension_minutes, right_ascension_seconds};
}