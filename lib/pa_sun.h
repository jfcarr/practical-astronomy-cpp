#ifndef _pa_sun
#define _pa_sun

#include "pa_types.h"
#include <tuple>

class PASun {
public:
  std::tuple<double, double, double, double, double, double>
  approximate_position_of_sun(double lct_hours, double lct_minutes,
                              double lct_seconds, double local_day,
                              int local_month, int local_year,
                              bool is_daylight_saving, int zone_correction);

  std::tuple<double, double, double, double, double, double>
  precise_position_of_sun(double lct_hours, double lct_minutes,
                          double lct_seconds, double local_day, int local_month,
                          int local_year, bool is_daylight_saving,
                          int zone_correction);

  std::tuple<double, double, double, double>
  sun_distance_and_angular_size(double lct_hours, double lct_minutes,
                                double lct_seconds, double local_day,
                                int local_month, int local_year,
                                bool is_daylight_saving, int zone_correction);
};
#endif