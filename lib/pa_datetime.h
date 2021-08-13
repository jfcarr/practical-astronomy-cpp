#ifndef _pa_datetime
#define _pa_datetime

#include "pa_types.h"
#include <tuple>

class PADateTime {
public:
  std::tuple<int, int, int> GetDateOfEaster(int input_year);

  int CivilDateToDayNumber(int month, int day, int year);

  double CivilTimeToDecimalHours(double hours, double minutes, double seconds);

  std::tuple<double, double, double>
  DecimalHoursToCivilTime(double decimal_hours);

  std::tuple<int, int, int, int, int, int>
  LocalCivilTimeToUniversalTime(double lct_hours, double lct_minutes,
                                double lct_seconds, bool is_daylight_savings,
                                int zone_correction, double local_day,
                                int local_month, int local_year);

  std::tuple<int, int, int, int, int, int>
  UniversalTimeToLocalCivilTime(double ut_hours, double ut_minutes,
                                double ut_seconds, bool is_daylight_savings,
                                int zone_correction, int gw_day, int gw_month,
                                int gw_year);

  std::tuple<int, int, double>
  UniversalTimeToGreenwichSiderealTime(double ut_hours, double ut_minutes,
                                       double ut_seconds, double gw_day,
                                       int gw_month, int gw_year);

  std::tuple<int, int, double, pa_types::WarningFlags>
  GreenwichSiderealTimeToUniversalTime(double gst_hours, double gst_minutes,
                                       double gst_seconds, double gw_day,
                                       int gw_month, int gw_year);

  std::tuple<int, int, double>
  GreenwichSiderealTimeToLocalSiderealTime(double gst_hours, double gst_minutes,
                                           double gst_seconds,
                                           double geographical_longitude);

  std::tuple<int, int, double>
  LocalSiderealTimeToGreenwichSiderealTime(double lst_hours, double lst_minutes,
                                           double lst_seconds,
                                           double geographical_longitude);
};
#endif
