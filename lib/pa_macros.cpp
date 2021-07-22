#include "pa_macros.h"
#include "pa_util.h"
#include <cmath>

double hms_dh(double hours, double minutes, double seconds) {
  double f_hours = hours;
  double f_minutes = minutes;
  double f_seconds = seconds;

  double a = abs((int)f_seconds) / 60.0;
  double b = (abs((int)f_minutes) + a) / 60.0;
  double c = abs((int)f_hours) + b;

  return (f_hours < 0 || f_minutes < 0 || f_seconds < 0) ? -c : c;
}

int decimal_hours_hour(double decimal_hours) {
  double a = std::abs(decimal_hours);
  double b = a * 3600;
  double c = round_d(b - 60 * floor(b / 60), 2);
  double e = (c == 60) ? b + 60 : b;

  return (decimal_hours < 0) ? (int)-(floor(e / 3600)) : (int)floor(e / 3600);
}

int decimal_hours_minute(double decimal_hours) {
  double a = std::abs(decimal_hours);
  double b = a * 3600;
  double c = round_d(b - 60 * floor(b / 60), 2);
  double e = (c == 60) ? b + 60 : b;

  return (int)floor(e / 60) % 60;
}

double decimal_hours_second(double decimal_hours) {
  double a = std::abs(decimal_hours);
  double b = a * 3600;
  double c = round_d(b - 60 * floor(b / 60), 2);
  double d = (c == 60) ? 0 : c;

  return d;
}
