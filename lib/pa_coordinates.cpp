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
 * @return tuple <double right_ascension_hours, double right_ascension_minutes,
 * double right_ascension_seconds>
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

/**
 * \brief Convert Equatorial Coordinates to Horizon Coordinates
 *
 * @return tuple <double azimuthDegrees, double azimuthMinutes, double
 * azimuthSeconds, double altitudeDegrees, double altitudeMinutes, double
 * altitudeSeconds>
 */
std::tuple<double, double, double, double, double, double>
PACoordinates::equatorial_coordinates_to_horizon_coordinates(
    double hour_angle_hours, double hour_angle_minutes,
    double hour_angle_seconds, double declination_degrees,
    double declination_minutes, double declination_seconds,
    double geographical_latitude) {
  double azimuth_in_decimal_degrees = equatorial_coordinates_to_azimuth(
      hour_angle_hours, hour_angle_minutes, hour_angle_seconds,
      declination_degrees, declination_minutes, declination_seconds,
      geographical_latitude);

  double altitude_in_decimal_degrees = equatorial_coordinates_to_altitude(
      hour_angle_hours, hour_angle_minutes, hour_angle_seconds,
      declination_degrees, declination_minutes, declination_seconds,
      geographical_latitude);

  double azimuth_degrees = decimal_degrees_degrees(azimuth_in_decimal_degrees);
  double azimuth_minutes = decimal_degrees_minutes(azimuth_in_decimal_degrees);
  double azimuth_seconds = decimal_degrees_seconds(azimuth_in_decimal_degrees);

  double altitude_degrees =
      decimal_degrees_degrees(altitude_in_decimal_degrees);
  double altitude_minutes =
      decimal_degrees_minutes(altitude_in_decimal_degrees);
  double altitude_seconds =
      decimal_degrees_seconds(altitude_in_decimal_degrees);

  return std::tuple<double, double, double, double, double, double>{
      azimuth_degrees,  azimuth_minutes,  azimuth_seconds,
      altitude_degrees, altitude_minutes, altitude_seconds};
}

/**
 * \brief Convert Horizon Coordinates to Equatorial Coordinates
 *
 * @return tuple <double hour_angle_hours, double hour_angle_minutes, double
 * hour_angle-seconds, double declination_degrees, double declination_minutes,
 * double declination_seconds>
 */
std::tuple<double, double, double, double, double, double>
PACoordinates::horizon_coordinates_to_equatorial_coordinates(
    double azimuth_degrees, double azimuth_minutes, double azimuth_seconds,
    double altitude_degrees, double altitude_minutes, double altitude_seconds,
    double geographical_latitude) {
  double hour_angle_in_decimal_degrees = horizon_coordinates_to_hour_angle(
      azimuth_degrees, azimuth_minutes, azimuth_seconds, altitude_degrees,
      altitude_minutes, altitude_seconds, geographical_latitude);

  double declination_in_decimal_degrees = horizon_coordinates_to_declination(
      azimuth_degrees, azimuth_minutes, azimuth_seconds, altitude_degrees,
      altitude_minutes, altitude_seconds, geographical_latitude);

  int hour_angle_hours = decimal_hours_hour(hour_angle_in_decimal_degrees);
  int hour_angle_minutes = decimal_hours_minute(hour_angle_in_decimal_degrees);
  double hour_angle_seconds =
      decimal_hours_second(hour_angle_in_decimal_degrees);

  double declination_degrees =
      decimal_degrees_degrees(declination_in_decimal_degrees);
  double declination_minutes =
      decimal_degrees_minutes(declination_in_decimal_degrees);
  double declination_seconds =
      decimal_degrees_seconds(declination_in_decimal_degrees);

  return std::tuple<double, double, double, double, double, double>{
      hour_angle_hours,    hour_angle_minutes,  hour_angle_seconds,
      declination_degrees, declination_minutes, declination_seconds};
}

/**
 * \brief Calculate Mean Obliquity of the Ecliptic for a Greenwich Date
 */
double PACoordinates::mean_obliquity_of_the_ecliptic(double greenwich_day,
                                                     int greenwich_month,
                                                     int greenwich_year) {
  double jd =
      civil_date_to_julian_date(greenwich_day, greenwich_month, greenwich_year);
  double mjd = jd - 2451545;
  double t = mjd / 36525;
  double de1 = t * (46.815 + t * (0.0006 - (t * 0.00181)));
  double de2 = de1 / 3600;

  return 23.439292 - de2;
}
