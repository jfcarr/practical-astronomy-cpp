#include "pa_datetime.h"
#include "pa_macros.h"
#include "pa_util.h"
#include <cmath>

std::tuple<int, int, int> PADateTime::get_date_of_easter(int input_year) {
  double year = (double)input_year;

  double a = (int)year % 19;
  double b = floor(year / 100.0);
  double c = (int)year % 100;
  double d = floor(b / 4.0);
  double e = (int)b % 4;
  double f = floor((b + 8.0) / 25.0);
  double g = floor((b - f + 1.0) / 3.0);
  double h = (int)((19.0 * a) + b - d - g + 15.0) % 30;
  double i = floor(c / 4.0);
  double k = (int)c % 4;
  double l = (int)(32.0 + 2.0 * (e + i) - h - k) % 7;
  double m = floor((a + (11.0 * h) + (22.0 * l)) / 451.0);
  double n = floor((h + l - (7.0 * m) + 114.0) / 31.0);
  double p = (int)(h + l - (7.0 * m) + 114.0) % 31;

  double day = p + 1.0;
  double month = n;

  return std::tuple<int, int, int>{(int)month, (int)day, (int)year};
}

int PADateTime::civil_date_to_day_number(int month, int day, int year) {
  if (month <= 2) {
    month--;
    month = (is_leap_year(year) == true) ? month * 62 : month * 63;
    month = (int)floor((double)month / 2.0);
  } else {
    month = (int)floor(((double)month + 1.0) * 30.6);
    month = (is_leap_year(year) == true) ? month - 62 : month - 63;
  }

  return month + day;
}

double PADateTime::civil_time_to_decimal_hours(double hours, double minutes,
                                               double seconds) {
  return hms_dh(hours, minutes, seconds);
}

std::tuple<double, double, double>
PADateTime::decimal_hours_to_civil_time(double decimal_hours) {
  int hours = decimal_hours_hour(decimal_hours);
  int minutes = decimal_hours_minute(decimal_hours);
  double seconds = decimal_hours_second(decimal_hours);

  return std::tuple<double, double, double>{hours, minutes, seconds};
}

/**
 * \brief Convert local civil time to universal time
 *
 * @param lct_hours Local civil time, hours part.
 * @param lct_minutes Local civil time, minutes part.
 * @param lct_seconds Local civil time, seconds part.
 * @param is_daylight_savings Currently daylight savings? (true/false)
 * @param zone_correction Time zone correction offset.
 * @param local_day Local date, day part.
 * @param local_month Local date, month part.
 * @param local_year Local date, year part.
 *
 * @return tuple <int utHours, int utMinutes, int utSeconds, int gwDay, int
 * gwMonth, int gwYear>
 */
std::tuple<int, int, int, int, int, int>
PADateTime::local_civil_time_to_universal_time(
    double lct_hours, double lct_minutes, double lct_seconds,
    bool is_daylight_savings, int zone_correction, double local_day,
    int local_month, int local_year) {
  double lct = civil_time_to_decimal_hours(lct_hours, lct_minutes, lct_seconds);

  int daylight_savings_offset = (is_daylight_savings) ? 1 : 0;

  double ut_interim = lct - daylight_savings_offset - zone_correction;
  double g_day_interim = local_day + (ut_interim / 24);

  double jd = civil_date_to_julian_date(g_day_interim, local_month, local_year);

  double g_day = julian_date_day(jd);
  int g_month = julian_date_month(jd);
  int g_year = julian_date_year(jd);

  double ut = 24 * (g_day - floor(g_day));

  return std::tuple<int, int, int, int, int, int>{decimal_hours_hour(ut),
                                                  decimal_hours_minute(ut),
                                                  (int)decimal_hours_second(ut),
                                                  (int)floor(g_day),
                                                  g_month,
                                                  g_year};
}

/**
 * \brief Convert universal time to local civil time
 *
 * @param ut_hours Universal time, hours part.
 * @param ut_minutes Universal time, minutes part.
 * @param ut_seconds Universal time, seconds part.
 * @param is_daylight_savings Currently daylight savings? (true/false)
 * @param zone_correction Time zone correction offset.
 * @param gw_day Greenwich date, day part.
 * @param gw_month Greenwich date, month part.
 * @param gw_year Greenwich date, year part.
 *
 * @return tuple <int lctHours, int lctMinutes, int lctSeconds, int localDay,
 * int localMonth, int localYear>
 */
std::tuple<int, int, int, int, int, int>
PADateTime::universal_time_to_local_civil_time(double ut_hours,
                                               double ut_minutes,
                                               double ut_seconds,
                                               bool is_daylight_savings,
                                               int zone_correction, int gw_day,
                                               int gw_month, int gw_year) {
  int dst_value = (is_daylight_savings) ? 1 : 0;
  double ut = hms_dh(ut_hours, ut_minutes, ut_seconds);
  double zone_time = ut + zone_correction;
  double local_time = zone_time + dst_value;
  double local_jd_plus_local_time =
      civil_date_to_julian_date(gw_day, gw_month, gw_year) + (local_time / 24);
  double local_day = julian_date_day(local_jd_plus_local_time);
  double integer_day = floor(local_day);
  int local_month = julian_date_month(local_jd_plus_local_time);
  int local_year = julian_date_year(local_jd_plus_local_time);

  double lct = 24 * (local_day - integer_day);

  return std::tuple<int, int, int, int, int, int>{
      decimal_hours_hour(lct),
      decimal_hours_minute(lct),
      (int)decimal_hours_second(lct),
      (int)integer_day,
      local_month,
      local_year};
}
