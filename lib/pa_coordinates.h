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
};
#endif