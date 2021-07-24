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