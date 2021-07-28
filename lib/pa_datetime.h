#ifndef _pa_datetime
#define _pa_datetime

#include "pa_types.h"
#include <tuple>

class PADateTime {
public:
  std::tuple<int, int, int> get_date_of_easter(int input_year);

  int civil_date_to_day_number(int month, int day, int year);

  double civil_time_to_decimal_hours(double hours, double minutes,
                                     double seconds);

  std::tuple<double, double, double>
  decimal_hours_to_civil_time(double decimal_hours);

  std::tuple<int, int, int, int, int, int> local_civil_time_to_universal_time(
      double lct_hours, double lct_minutes, double lct_seconds,
      bool is_daylight_savings, int zone_correction, double local_day,
      int local_month, int local_year);

  std::tuple<int, int, int, int, int, int> universal_time_to_local_civil_time(
      double ut_hours, double ut_minutes, double ut_seconds,
      bool is_daylight_savings, int zone_correction, int gw_day, int gw_month,
      int gw_year);

  std::tuple<int, int, double>
  universal_time_to_greenwich_sidereal_time(double ut_hours, double ut_minutes,
                                            double ut_seconds, double gw_day,
                                            int gw_month, int gw_year);

  std::tuple<int, int, double, pa_types::warning_flags>
  greenwich_sidereal_time_to_universal_time(double gst_hours,
                                            double gst_minutes,
                                            double gst_seconds, double gw_day,
                                            int gw_month, int gw_year);
};
#endif
