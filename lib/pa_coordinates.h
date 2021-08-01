#ifndef _pa_coordinates
#define _pa_coordinates

#include "pa_types.h"
#include <tuple>

class PACoordinates {
public:
  double angle_to_decimal_degrees(double degrees, double minutes,
                                  double seconds);

  std::tuple<double, double, double>
  decimal_degrees_to_angle(double decimal_degrees);

  std::tuple<double, double, double> right_ascension_to_hour_angle(
      double ra_hours, double ra_minutes, double ra_seconds, double lct_hours,
      double lct_minutes, double lct_seconds, bool is_daylight_savings,
      int zone_correction, double local_day, int local_month, int local_year,
      double geographical_longitude);

  std::tuple<double, double, double> hour_angle_to_right_ascension(
      double hour_angle_hours, double hour_angle_minutes,
      double hour_angle_seconds, double lct_hours, double lct_minutes,
      double lct_seconds, bool is_daylight_savings, int zone_correction,
      double local_day, int local_month, int local_year,
      double geographical_longitude);

  std::tuple<double, double, double, double, double, double>
  equatorial_coordinates_to_horizon_coordinates(double hour_angle_hours,
                                                double hour_angle_minutes,
                                                double hour_angle_seconds,
                                                double declination_degrees,
                                                double declination_minutes,
                                                double declination_seconds,
                                                double geographical_latitude);

  std::tuple<double, double, double, double, double, double>
  horizon_coordinates_to_equatorial_coordinates(
      double azimuth_degrees, double azimuth_minutes, double azimuth_seconds,
      double altitude_degrees, double altitude_minutes, double altitude_seconds,
      double geographical_latitude);

  double mean_obliquity_of_the_ecliptic(double greenwich_day,
                                        int greenwich_month,
                                        int greenwich_year);

  std::tuple<double, double, double, double, double, double>
  ecliptic_coordinate_to_equatorial_coordinate(
      double ecliptic_longitude_degrees, double ecliptic_longitude_minutes,
      double ecliptic_longitude_seconds, double ecliptic_latitude_degrees,
      double ecliptic_latitude_minutes, double ecliptic_latitude_seconds,
      double greenwich_day, int greenwich_month, int greenwich_year);

  std::tuple<double, double, double, double, double, double>
  equatorial_coordinate_to_ecliptic_coordinate(
      double ra_hours, double ra_minutes, double ra_seconds, double dec_degrees,
      double dec_minutes, double dec_seconds, double gw_day, int gw_month,
      int gw_year);
};
#endif