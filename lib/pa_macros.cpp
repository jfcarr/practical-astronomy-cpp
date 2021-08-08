#include "pa_macros.h"
#include "pa_types.h"
#include "pa_util.h"
#include <cmath>
#include <tuple>

using namespace pa_util;

namespace pa_macros {
/**
 * \brief Convert a Civil Time (hours,minutes,seconds) to Decimal Hours
 *
 * Original macro name: HMSDH
 *
 * @param hours Hours part of time.
 * @param minutes Minutes part of time.
 * @param seconds Seconds part of time.
 *
 * @return Time as a decimal value.
 */
double hms_dh(double hours, double minutes, double seconds) {
  double f_hours = hours;
  double f_minutes = minutes;
  double f_seconds = seconds;

  double a = std::abs(f_seconds) / 60;
  double b = (std::abs(f_minutes) + a) / 60;
  double c = std::abs(f_hours) + b;

  return (f_hours < 0 || f_minutes < 0 || f_seconds < 0) ? -c : c;
}

/**
 * \brief Return the hour part of a Decimal Hours
 *
 * Original macro name: DHHour
 *
 * @param decimal_hours Time as a decimal value.
 *
 * @return Hour part of time.
 */
int decimal_hours_hour(double decimal_hours) {
  double a = std::abs(decimal_hours);
  double b = a * 3600;
  double c = round(b - 60 * floor(b / 60), 2);
  double e = (c == 60) ? b + 60 : b;

  return (decimal_hours < 0) ? (int)-(floor(e / 3600)) : (int)floor(e / 3600);
}

/**
 * \brief Return the minutes part of a Decimal Hours
 *
 * Original macro name: DHMin
 *
 * @param decimal_hours Time as a decimal value.
 *
 * @return Minutes part of time.
 */
int decimal_hours_minute(double decimal_hours) {
  double a = std::abs(decimal_hours);
  double b = a * 3600;
  double c = round(b - 60 * floor(b / 60), 2);
  double e = (c == 60) ? b + 60 : b;

  return (int)floor(e / 60) % 60;
}

/**
 * \brief Return the seconds part of a Decimal Hours
 *
 * Original macro name: DHSec
 *
 * @param decimal_hours Time as a decimal value.
 *
 * @return Seconds part of time.
 */
double decimal_hours_second(double decimal_hours) {
  double a = std::abs(decimal_hours);
  double b = a * 3600;
  double c = round(b - 60 * floor(b / 60), 2);
  double d = (c == 60) ? 0 : c;

  return d;
}

/**
 * \brief Convert a Greenwich Date/Civil Date (day,month,year) to Julian Date
 *
 * Original macro name: CDJD
 *
 * @param day Day part of civil date.
 * @param month Month part of civil date.
 * @param year Year part of civil date.
 *
 * @return Julian date
 */
double civil_date_to_julian_date(double day, double month, double year) {
  double f_day = (double)day;
  double f_month = (double)month;
  double f_year = (double)year;

  double y = (f_month < 3) ? f_year - 1 : f_year;
  double m = (f_month < 3) ? f_month + 12 : f_month;

  double b;

  if (f_year > 1582) {
    double a = floor(y / 100);
    b = 2 - a + floor(a / 4);
  } else {
    if (f_year == 1582 && f_month > 10) {
      double a = floor(y / 100);
      b = 2 - a + floor(a / 4);
    } else {
      if (f_year == 1582 && f_month == 10 && f_day >= 15) {
        double a = floor(y / 100);
        b = 2 - a + floor(a / 4);
      } else
        b = 0;
    }
  }

  double c = (y < 0) ? floor(((365.25 * y) - 0.75)) : floor(365.25 * y);
  double d = floor(30.6001 * (m + 1.0));

  return b + c + d + f_day + 1720994.5;
}

/**
 * \brief Returns the day part of a Julian Date
 *
 * Original macro name: JDCDay
 */
double julian_date_day(double julian_date) {
  double i = floor(julian_date + 0.5);
  double f = julian_date + 0.5 - i;
  double a = floor((i - 1867216.25) / 36524.25);
  double b = (i > 2299160) ? i + 1 + a - floor(a / 4) : i;
  double c = b + 1524;
  double d = floor((c - 122.1) / 365.25);
  double e = floor(365.25 * d);
  double g = floor((c - e) / 30.6001);

  return c - e + f - floor(30.6001 * g);
}

/**
 * \brief Returns the month part of a Julian Date
 *
 * Original macro name: JDCMonth
 */
int julian_date_month(double julian_date) {
  double i = floor(julian_date + 0.5);
  double a = floor((i - 1867216.25) / 36524.25);
  double b = (i > 2299160) ? i + 1 + a - floor(a / 4) : i;
  double c = b + 1524;
  double d = floor((c - 122.1) / 365.25);
  double e = floor(365.25 * d);
  double g = floor((c - e) / 30.6001);

  double returnValue = (g < 13.5) ? g - 1 : g - 13;

  return (int)returnValue;
}

/**
 * \brief Returns the year part of a Julian Date
 *
 * Original macro name: JDCYear
 */
int julian_date_year(double julian_date) {
  double i = floor(julian_date + 0.5);
  double a = floor((i - 1867216.25) / 36524.25);
  double b = (i > 2299160) ? i + 1.0 + a - floor(a / 4.0) : i;
  double c = b + 1524;
  double d = floor((c - 122.1) / 365.25);
  double e = floor(365.25 * d);
  double g = floor((c - e) / 30.6001);
  double h = (g < 13.5) ? g - 1 : g - 13;

  double returnValue = (h > 2.5) ? d - 4716 : d - 4715;

  return (int)returnValue;
}

/**
 * \brief Convert Right Ascension to Hour Angle
 *
 * Original macro name: RAHA
 */
double right_ascension_to_hour_angle(double ra_hours, double ra_minutes,
                                     double ra_seconds, double lct_hours,
                                     double lct_minutes, double lct_seconds,
                                     int daylight_saving, int zone_correction,
                                     double local_day, int local_month,
                                     int local_year,
                                     double geographical_longitude) {
  double a = local_civil_time_to_universal_time(
      lct_hours, lct_minutes, lct_seconds, daylight_saving, zone_correction,
      local_day, local_month, local_year);
  double b = local_civil_time_greenwich_day(lct_hours, lct_minutes, lct_seconds,
                                            daylight_saving, zone_correction,
                                            local_day, local_month, local_year);
  int c = local_civil_time_greenwich_month(lct_hours, lct_minutes, lct_seconds,
                                           daylight_saving, zone_correction,
                                           local_day, local_month, local_year);
  int d = local_civil_time_greenwich_year(lct_hours, lct_minutes, lct_seconds,
                                          daylight_saving, zone_correction,
                                          local_day, local_month, local_year);
  double e = universal_time_to_greenwich_sidereal_time(a, 0, 0, b, c, d);
  double f = greenwich_sidereal_time_to_local_sidereal_time(
      e, 0, 0, geographical_longitude);
  double g = hms_dh(ra_hours, ra_minutes, ra_seconds);
  double h = f - g;

  return (h < 0) ? 24 + h : h;
}

/**
 * \brief Convert Hour Angle to Right Ascension
 *
 * Original macro name: HARA
 */
double hour_angle_to_right_ascension(double hour_angle_hours,
                                     double hour_angle_minutes,
                                     double hour_angle_seconds,
                                     double lct_hours, double lct_minutes,
                                     double lct_seconds, int daylight_saving,
                                     int zone_correction, double local_day,
                                     int local_month, int local_year,
                                     double geographical_longitude) {
  double a = local_civil_time_to_universal_time(
      lct_hours, lct_minutes, lct_seconds, daylight_saving, zone_correction,
      local_day, local_month, local_year);
  double b = local_civil_time_greenwich_day(lct_hours, lct_minutes, lct_seconds,
                                            daylight_saving, zone_correction,
                                            local_day, local_month, local_year);
  int c = local_civil_time_greenwich_month(lct_hours, lct_minutes, lct_seconds,
                                           daylight_saving, zone_correction,
                                           local_day, local_month, local_year);
  int d = local_civil_time_greenwich_year(lct_hours, lct_minutes, lct_seconds,
                                          daylight_saving, zone_correction,
                                          local_day, local_month, local_year);
  double e = universal_time_to_greenwich_sidereal_time(a, 0, 0, b, c, d);
  double f = greenwich_sidereal_time_to_local_sidereal_time(
      e, 0, 00, geographical_longitude);
  double g = hms_dh(hour_angle_hours, hour_angle_minutes, hour_angle_seconds);
  double h = f - g;

  return (h < 0) ? 24 + h : h;
}

/**
 * \brief Convert Local Civil Time to Universal Time
 *
 * Original macro name: LctUT
 */
double local_civil_time_to_universal_time(double lct_hours, double lct_minutes,
                                          double lct_seconds,
                                          int daylight_saving,
                                          int zone_correction, double local_day,
                                          int local_month, int local_year) {
  double a = hms_dh(lct_hours, lct_minutes, lct_seconds);
  double b = a - daylight_saving - zone_correction;
  double c = local_day + (b / 24);
  double d = civil_date_to_julian_date(c, local_month, local_year);
  double e = julian_date_day(d);
  double e1 = floor(e);

  return 24 * (e - e1);
}

/**
 * \brief Determine Greenwich Day for Local Time
 *
 * Original macro name: LctGDay
 */
double local_civil_time_greenwich_day(double lct_hours, double lct_minutes,
                                      double lct_seconds, int daylight_saving,
                                      int zone_correction, double local_day,
                                      int local_month, int local_year) {
  double a = hms_dh(lct_hours, lct_minutes, lct_seconds);
  double b = a - daylight_saving - zone_correction;
  double c = local_day + (b / 24);
  double d = civil_date_to_julian_date(c, local_month, local_year);
  double e = julian_date_day(d);

  return floor(e);
}

/**
 * \brief Determine Greenwich Month for Local Time
 *
 * Original macro name: LctGMonth
 */
double local_civil_time_greenwich_month(double lct_hours, double lct_minutes,
                                        double lct_seconds, int daylight_saving,
                                        int zone_correction, double local_day,
                                        int local_month, int local_year) {
  double a = hms_dh(lct_hours, lct_minutes, lct_seconds);
  double b = a - daylight_saving - zone_correction;
  double c = local_day + (b / 24);
  double d = civil_date_to_julian_date(c, local_month, local_year);

  return julian_date_month(d);
}

/**
 * \brief Determine Greenwich Year for Local Time
 *
 * Original macro name: LctGYear
 */
double local_civil_time_greenwich_year(double lct_hours, double lct_minutes,
                                       double lct_seconds, int daylight_saving,
                                       int zone_correction, double local_day,
                                       int local_month, int local_year) {
  double a = hms_dh(lct_hours, lct_minutes, lct_seconds);
  double b = a - daylight_saving - zone_correction;
  double c = local_day + (b / 24);
  double d = civil_date_to_julian_date(c, local_month, local_year);

  return julian_date_year(d);
}

/**
 * \brief Convert Universal Time to Greenwich Sidereal Time
 *
 * Original macro name: UTGST
 */
double universal_time_to_greenwich_sidereal_time(
    double u_hours, double u_minutes, double u_seconds, double greenwich_day,
    int greenwich_month, int greenwich_year) {
  double a =
      civil_date_to_julian_date(greenwich_day, greenwich_month, greenwich_year);
  double b = a - 2451545;
  double c = b / 36525;
  double d = 6.697374558 + (2400.051336 * c) + (0.000025862 * c * c);
  double e = d - (24 * floor(d / 24));
  double f = hms_dh(u_hours, u_minutes, u_seconds);
  double g = f * 1.002737909;
  double h = e + g;

  return h - (24 * floor(h / 24));
}

/**
 * \brief Convert Greenwich Sidereal Time to Local Sidereal Time
 *
 * Original macro name: GSTLST
 */
double greenwich_sidereal_time_to_local_sidereal_time(
    double greenwich_hours, double greenwich_minutes, double greenwich_seconds,
    double geographical_longitude) {
  double a = hms_dh(greenwich_hours, greenwich_minutes, greenwich_seconds);
  double b = geographical_longitude / 15;
  double c = a + b;

  return c - (24 * floor(c / 24));
}

/**
 * \brief Convert Equatorial Coordinates to Azimuth (in decimal degrees)
 *
 * Original macro name: EQAz
 */
double equatorial_coordinates_to_azimuth(double hour_angle_hours,
                                         double hour_angle_minutes,
                                         double hour_angle_seconds,
                                         double declination_degrees,
                                         double declination_minutes,
                                         double declination_seconds,
                                         double geographical_latitude) {
  double a = hms_dh(hour_angle_hours, hour_angle_minutes, hour_angle_seconds);
  double b = a * 15;
  double c = degrees_to_radians(b);
  double d = degrees_minutes_seconds_to_decimal_degrees(
      declination_degrees, declination_minutes, declination_seconds);
  double e = degrees_to_radians(d);
  double f = degrees_to_radians(geographical_latitude);
  double g = sin(e) * sin(f) + cos(e) * cos(f) * cos(c);
  double h = -cos(e) * cos(f) * sin(c);
  double i = sin(e) - (sin(f) * g);
  double j = w_to_degrees(atan2(h, i));

  return j - 360.0 * floor(j / 360);
}

/**
 * \brief Convert Equatorial Coordinates to Altitude (in decimal degrees)
 *
 * Original macro name: EQAlt
 */
double equatorial_coordinates_to_altitude(double hour_angle_hours,
                                          double hour_angle_minutes,
                                          double hour_angle_seconds,
                                          double declination_degrees,
                                          double declination_minutes,
                                          double declination_seconds,
                                          double geographical_latitude) {
  double a = hms_dh(hour_angle_hours, hour_angle_minutes, hour_angle_seconds);
  double b = a * 15;
  double c = degrees_to_radians(b);
  double d = degrees_minutes_seconds_to_decimal_degrees(
      declination_degrees, declination_minutes, declination_seconds);
  double e = degrees_to_radians(d);
  double f = degrees_to_radians(geographical_latitude);
  double g = sin(e) * sin(f) + cos(e) * cos(f) * cos(c);

  return w_to_degrees(asin(g));
}

/**
 * \brief Convert Degrees Minutes Seconds to Decimal Degrees
 *
 * Original macro name: DMSDD
 */
double degrees_minutes_seconds_to_decimal_degrees(double degrees,
                                                  double minutes,
                                                  double seconds) {
  double a = std::abs(seconds) / 60;
  double b = (std::abs(minutes) + a) / 60;
  double c = std::abs(degrees) + b;

  return (degrees < 0 || minutes < 0 || seconds < 0) ? -c : c;
}

/**
 * \brief Convert W to Degrees
 *
 * Original macro name: Degrees
 */
double w_to_degrees(double w) { return w * 57.29577951; }

/**
 * \brief Return Degrees part of Decimal Degrees
 *
 * Original macro name: DDDeg
 */
double decimal_degrees_degrees(double decimal_degrees) {
  double a = std::abs(decimal_degrees);
  double b = a * 3600;
  double c = round(b - 60 * floor(b / 60), 2);
  double e = (c == 60) ? 60 : b;

  return (decimal_degrees < 0) ? -(floor(e / 3600)) : floor(e / 3600);
}

/**
 * \brief Return Minutes part of Decimal Degrees
 *
 * Original macro name: DDMin
 */
double decimal_degrees_minutes(double decimal_degrees) {
  double a = std::abs(decimal_degrees);
  double b = a * 3600;
  double c = round(b - 60 * floor(b / 60), 2);
  double e = (c == 60) ? b + 60 : b;

  return (int)floor(e / 60) % 60;
}

/**
 * \brief Return Seconds part of Decimal Degrees
 *
 * Original macro name: DDSec
 */
double decimal_degrees_seconds(double decimal_degrees) {
  double a = std::abs(decimal_degrees);
  double b = a * 3600;
  double c = round(b - 60 * floor(b / 60), 2);
  double d = (c == 60) ? 0 : c;

  return d;
}

/**
 * \brief Convert Decimal Degrees to Degree-Hours
 *
 * Original macro name: DDDH
 */
double decimal_degrees_to_degree_hours(double decimal_degrees) {
  return decimal_degrees / 15;
}

/**
 * \brief Convert Degree-Hours to Decimal Degrees
 *
 * Original macro name: DHDD
 */
double degree_hours_to_decimal_degrees(double degree_hours) {
  return degree_hours * 15;
}

/**
 * \brief Convert Horizon Coordinates to Declination (in decimal degrees)
 *
 * Original macro name: HORDec
 */
double horizon_coordinates_to_declination(
    double azimuth_degrees, double azimuth_minutes, double azimuth_seconds,
    double altitude_degrees, double altitude_minutes, double altitude_seconds,
    double geographical_latitude) {
  double a = degrees_minutes_seconds_to_decimal_degrees(
      azimuth_degrees, azimuth_minutes, azimuth_seconds);
  double b = degrees_minutes_seconds_to_decimal_degrees(
      altitude_degrees, altitude_minutes, altitude_seconds);
  double c = degrees_to_radians(a);
  double d = degrees_to_radians(b);
  double e = degrees_to_radians(geographical_latitude);
  double f = sin(d) * sin(e) + cos(d) * cos(e) * cos(c);

  return w_to_degrees(asin(f));
}

/**
 * \brief Convert Horizon Coordinates to Hour Angle (in decimal degrees)
 *
 * Original macro name: HORHa
 */
double horizon_coordinates_to_hour_angle(
    double azimuth_degrees, double azimuth_minutes, double azimuth_seconds,
    double altitude_degrees, double altitude_minutes, double altitude_seconds,
    double geographical_latitude) {
  double a = degrees_minutes_seconds_to_decimal_degrees(
      azimuth_degrees, azimuth_minutes, azimuth_seconds);
  double b = degrees_minutes_seconds_to_decimal_degrees(
      altitude_degrees, altitude_minutes, altitude_seconds);
  double c = degrees_to_radians(a);
  double d = degrees_to_radians(b);
  double e = degrees_to_radians(geographical_latitude);
  double f = sin(d) * sin(e) + cos(d) * cos(e) * cos(c);
  double g = -cos(d) * cos(e) * sin(c);
  double h = sin(d) - sin(e) * f;
  double i = decimal_degrees_to_degree_hours(w_to_degrees(atan2(g, h)));

  return i - 24 * floor(i / 24);
}

/**
 * \brief Obliquity of the Ecliptic for a Greenwich Date
 *
 * Original macro name: Obliq
 */
double obliq(double greenwich_day, int greenwich_month, int greenwich_year) {
  double a =
      civil_date_to_julian_date(greenwich_day, greenwich_month, greenwich_year);
  double b = a - 2415020;
  double c = (b / 36525) - 1;
  double d = c * (46.815 + c * (0.0006 - (c * 0.00181)));
  double e = d / 3600;

  return 23.43929167 - e +
         nutat_obl(greenwich_day, greenwich_month, greenwich_year);
}

/**
 * \brief Nutation amount to be added in ecliptic longitude, in degrees.
 *
 * Original macro name: NutatLong
 */
double nutat_long(double gd, int gm, int gy) {
  double dj = civil_date_to_julian_date(gd, gm, gy) - 2415020;
  double t = dj / 36525;
  double t2 = t * t;

  double a = 100.0021358 * t;
  double b = 360 * (a - floor(a));

  double l1 = 279.6967 + 0.000303 * t2 + b;
  double l2 = 2 * degrees_to_radians(l1);

  a = 1336.855231 * t;
  b = 360 * (a - floor(a));

  double d1 = 270.4342 - 0.001133 * t2 + b;
  double d2 = 2 * degrees_to_radians(d1);

  a = 99.99736056 * t;
  b = 360 * (a - floor(a));

  double m1 = 358.4758 - 0.00015 * t2 + b;
  m1 = degrees_to_radians(m1);

  a = 1325.552359 * t;
  b = 360 * (a - floor(a));

  double m2 = 296.1046 + 0.009192 * t2 + b;
  m2 = degrees_to_radians(m2);

  a = 5.372616667 * t;
  b = 360 * (a - floor(a));

  double n1 = 259.1833 + 0.002078 * t2 - b;
  n1 = degrees_to_radians(n1);

  double n2 = 2.0 * n1;

  double dp = (-17.2327 - 0.01737 * t) * sin(n1);
  dp = dp + (-1.2729 - 0.00013 * t) * sin(l2) + 0.2088 * sin(n2);
  dp = dp - 0.2037 * sin(d2) + (0.1261 - 0.00031 * t) * sin(m1);
  dp = dp + 0.0675 * sin(m2) - (0.0497 - 0.00012 * t) * sin(l2 + m1);
  dp = dp - 0.0342 * sin(d2 - n1) - 0.0261 * sin(d2 + m2);
  dp = dp + 0.0214 * sin(l2 - m1) - 0.0149 * sin(l2 - d2 + m2);
  dp = dp + 0.0124 * sin(l2 - n1) + 0.0114 * sin(d2 - m2);

  return dp / 3600;
}

/**
 * \brief Nutation of Obliquity
 *
 * Original macro name: NutatObl
 */
double nutat_obl(double greenwich_day, int greenwich_month,
                 int greenwich_year) {
  double dj = civil_date_to_julian_date(greenwich_day, greenwich_month,
                                        greenwich_year) -
              2415020;
  double t = dj / 36525;
  double t2 = t * t;

  double a = 100.0021358 * t;
  double b = 360 * (a - floor(a));

  double l1 = 279.6967 + 0.000303 * t2 + b;
  double l2 = 2 * degrees_to_radians(l1);

  a = 1336.855231 * t;
  b = 360 * (a - floor(a));

  double d1 = 270.4342 - 0.001133 * t2 + b;
  double d2 = 2 * degrees_to_radians(d1);

  a = 99.99736056 * t;
  b = 360 * (a - floor(a));

  double m1 = degrees_to_radians(358.4758 - 0.00015 * t2 + b);

  a = 1325.552359 * t;
  b = 360 * (a - floor(a));

  double m2 = degrees_to_radians(296.1046 + 0.009192 * t2 + b);

  a = 5.372616667 * t;
  b = 360 * (a - floor(a));

  double n1 = degrees_to_radians(259.1833 + 0.002078 * t2 - b);

  double n2 = 2 * n1;

  double ddo = (9.21 + 0.00091 * t) * cos(n1);
  ddo = ddo + (0.5522 - 0.00029 * t) * cos(l2) - 0.0904 * cos(n2);
  ddo = ddo + 0.0884 * cos(d2) + 0.0216 * cos(l2 + m1);
  ddo = ddo + 0.0183 * cos(d2 - n1) + 0.0113 * cos(d2 + m2);
  ddo = ddo - 0.0093 * cos(l2 - m1) - 0.0066 * cos(l2 - n1);

  return ddo / 3600;
}

/**
 * \brief Convert Local Sidereal Time to Greenwich Sidereal Time
 *
 * Original macro name: LSTGST
 */
double local_sidereal_time_to_greenwich_sidereal_time(double local_hours,
                                                      double local_minutes,
                                                      double local_seconds,
                                                      double longitude) {
  double a = hms_dh(local_hours, local_minutes, local_seconds);
  double b = longitude / 15;
  double c = a - b;

  return c - (24 * floor(c / 24));
}

/**
 * \brief Convert Greenwich Sidereal Time to Universal Time
 *
 * Original macro name: GSTUT
 */
double greenwich_sidereal_time_to_universal_time(
    double greenwich_sidereal_hours, double greenwich_sidereal_minutes,
    double greenwich_sidereal_seconds, double greenwich_day,
    int greenwich_month, int greenwich_year) {
  double a =
      civil_date_to_julian_date(greenwich_day, greenwich_month, greenwich_year);
  double b = a - 2451545;
  double c = b / 36525;
  double d = 6.697374558 + (2400.051336 * c) + (0.000025862 * c * c);
  double e = d - (24 * floor(d / 24));
  double f = hms_dh(greenwich_sidereal_hours, greenwich_sidereal_minutes,
                    greenwich_sidereal_seconds);
  double g = f - e;
  double h = g - (24 * floor(g / 24));

  return h * 0.9972695663;
}

/**
 * \brief Calculate Sun's ecliptic longitude
 *
 * Original macro name: SunLong
 */
double sun_long(double lch, double lcm, double lcs, int ds, int zc, double ld,
                int lm, int ly) {
  double aa = local_civil_time_greenwich_day(lch, lcm, lcs, ds, zc, ld, lm, ly);
  int bb = local_civil_time_greenwich_month(lch, lcm, lcs, ds, zc, ld, lm, ly);
  int cc = local_civil_time_greenwich_year(lch, lcm, lcs, ds, zc, ld, lm, ly);
  double ut =
      local_civil_time_to_universal_time(lch, lcm, lcs, ds, zc, ld, lm, ly);
  double dj = civil_date_to_julian_date(aa, bb, cc) - 2415020;
  double t = (dj / 36525) + (ut / 876600);
  double t2 = t * t;
  double a = 100.0021359 * t;
  double b = 360.0 * (a - floor(a));

  double l = 279.69668 + 0.0003025 * t2 + b;
  a = 99.99736042 * t;
  b = 360 * (a - floor(a));

  double m1 = 358.47583 - (0.00015 + 0.0000033 * t) * t2 + b;
  double ec = 0.01675104 - 0.0000418 * t - 0.000000126 * t2;

  double am = degrees_to_radians(m1);
  double at = true_anomaly(am, ec);

  a = 62.55209472 * t;
  b = 360 * (a - floor(a));

  double a1 = degrees_to_radians(153.23 + b);
  a = 125.1041894 * t;
  b = 360 * (a - floor(a));

  double b1 = degrees_to_radians(216.57 + b);
  a = 91.56766028 * t;
  b = 360 * (a - floor(a));

  double c1 = degrees_to_radians(312.69 + b);
  a = 1236.853095 * t;
  b = 360 * (a - floor(a));

  double d1 = degrees_to_radians(350.74 - 0.00144 * t2 + b);
  double e1 = degrees_to_radians(231.19 + 20.2 * t);
  a = 183.1353208 * t;
  b = 360 * (a - floor(a));
  double h1 = degrees_to_radians(353.4 + b);

  double d2 = 0.00134 * cos(a1) + 0.00154 * cos(b1) + 0.002 * cos(c1);
  d2 = d2 + 0.00179 * sin(d1) + 0.00178 * sin(e1);
  double d3 = 0.00000543 * sin(a1) + 0.00001575 * sin(b1);
  d3 = d3 + 0.00001627 * sin(c1) + 0.00003076 * cos(d1);

  double sr = at + degrees_to_radians(l - m1 + d2);
  double tp = 6.283185308;

  sr = sr - tp * floor(sr / tp);

  return w_to_degrees(sr);
}

/**
 * \brief Calculate Sun's angular diameter in decimal degrees
 *
 * Original macro name: SunDia
 */
double sun_dia(double lch, double lcm, double lcs, int ds, int zc, double ld,
               int lm, int ly) {
  double a = sun_dist(lch, lcm, lcs, ds, zc, ld, lm, ly);

  return 0.533128 / a;
}

/**
 * \brief Calculate Sun's distance from the Earth in astronomical units
 *
 * Original macro name: SunDist
 */
double sun_dist(double lch, double lcm, double lcs, int ds, int zc, double ld,
                int lm, int ly) {
  double aa = local_civil_time_greenwich_day(lch, lcm, lcs, ds, zc, ld, lm, ly);
  int bb = local_civil_time_greenwich_month(lch, lcm, lcs, ds, zc, ld, lm, ly);
  int cc = local_civil_time_greenwich_year(lch, lcm, lcs, ds, zc, ld, lm, ly);
  double ut =
      local_civil_time_to_universal_time(lch, lcm, lcs, ds, zc, ld, lm, ly);
  double dj = civil_date_to_julian_date(aa, bb, cc) - 2415020;

  double t = (dj / 36525) + (ut / 876600);
  double t2 = t * t;

  double a = 100.0021359 * t;
  double b = 360 * (a - floor(a));
  a = 99.99736042 * t;
  b = 360 * (a - floor(a));
  double m1 = 358.47583 - (0.00015 + 0.0000033 * t) * t2 + b;
  double ec = 0.01675104 - 0.0000418 * t - 0.000000126 * t2;

  double am = degrees_to_radians(m1);
  double ae = eccentric_anomaly(am, ec);

  a = 62.55209472 * t;
  b = 360 * (a - floor(a));
  double a1 = degrees_to_radians(153.23 + b);
  a = 125.1041894 * t;
  b = 360 * (a - floor(a));
  double b1 = degrees_to_radians(216.57 + b);
  a = 91.56766028 * t;
  b = 360 * (a - floor(a));
  double c1 = degrees_to_radians(312.69 + b);
  a = 1236.853095 * t;
  b = 360 * (a - floor(a));
  double d1 = degrees_to_radians(350.74 - 0.00144 * t2 + b);
  double e1 = degrees_to_radians(231.19 + 20.2 * t);
  a = 183.1353208 * t;
  b = 360 * (a - floor(a));
  double h1 = degrees_to_radians(353.4 + b);

  double d3 = (0.00000543 * sin(a1) + 0.00001575 * sin(b1)) +
              (0.00001627 * sin(c1) + 0.00003076 * cos(d1)) +
              (0.00000927 * sin(h1));

  return 1.0000002 * (1 - ec * cos(ae)) + d3;
}

/**
 * \brief Solve Kepler's equation, and return value of the true anomaly in
 * radians
 *
 * Original macro name: TrueAnomaly
 */
double true_anomaly(double am, double ec) {
  double tp = 6.283185308;
  double m = am - tp * floor(am / tp);
  double ae = m;

  while (1 == 1) {
    double d = ae - (ec * sin(ae)) - m;
    if (std::abs(d) < 0.000001) {
      break;
    }
    d = d / (1.0 - (ec * cos(ae)));
    ae = ae - d;
  }
  double a = sqrt((1 + ec) / (1 - ec)) * tan(ae / 2);
  double at = 2.0 * atan(a);

  return at;
}

/**
 * \brief Solve Kepler's equation, and return value of the eccentric anomaly in
 * radians
 *
 * Original macro name: EccentricAnomaly
 */
double eccentric_anomaly(double am, double ec) {
  double tp = 6.283185308;
  double m = am - tp * floor(am / tp);
  double ae = m;

  while (1 == 1) {
    double d = ae - (ec * sin(ae)) - m;

    if (std::abs(d) < 0.000001) {
      break;
    }

    d = d / (1 - (ec * cos(ae)));
    ae = ae - d;
  }

  return ae;
}

/**
 * \brief Calculate effects of refraction
 *
 * Original macro name: Refract
 */
double refract(double y2, pa_types::coordinate_type sw, double pr, double tr) {
  double y = degrees_to_radians(y2);

  double d = (sw == pa_types::coordinate_type::actual) ? -1.0 : 1.0;

  if (d == -1) {
    double y3 = y;
    double y1 = y;
    double r1 = 0.0;

    while (1 == 1) {
      double y_new = y1 + r1;
      double rf_new = refract_l3035(pr, tr, y_new, d);

      if (y < -0.087)
        return 0;

      double r2 = rf_new;

      if ((r2 == 0) || (std::abs(r2 - r1) < 0.000001)) {
        double q_new = y3;

        return w_to_degrees(q_new + rf_new);
      }

      r1 = r2;
    }
  }

  double rf = refract_l3035(pr, tr, y, d);

  if (y < -0.087)
    return 0;

  double q = y;

  return w_to_degrees(q + rf);
}

/**
 * \brief Helper function for Refract
 */
double refract_l3035(double pr, double tr, double y, double d) {
  if (y < 0.2617994) {
    if (y < -0.087)
      return 0;

    double yd = w_to_degrees(y);
    double a = ((0.00002 * yd + 0.0196) * yd + 0.1594) * pr;
    double b = (273.0 + tr) * ((0.0845 * yd + 0.505) * yd + 1);

    return degrees_to_radians(-(a / b) * d);
  }

  return -d * 0.00007888888 * pr / ((273.0 + tr) * tan(y));
}

/**
 * \brief Calculate corrected hour angle in decimal hours
 *
 * Original macro name: ParallaxHA
 */
double parallax_ha(double hh, double hm, double hs, double dd, double dm,
                   double ds, pa_types::coordinate_type sw, double gp,
                   double ht, double hp) {
  double a = degrees_to_radians(gp);
  double c1 = cos(a);
  double s1 = sin(a);

  double u = atan(0.996647 * s1 / c1);
  double c2 = cos(u);
  double s2 = sin(u);
  double b = ht / 6378160;

  double rs = (0.996647 * s2) + (b * s1);

  double rc = c2 + (b * c1);
  double tp = 6.283185308;

  double rp = 1.0 / sin(degrees_to_radians(hp));

  double x =
      degrees_to_radians(degree_hours_to_decimal_degrees(hms_dh(hh, hm, hs)));
  double x1 = x;
  double y = degrees_to_radians(
      degrees_minutes_seconds_to_decimal_degrees(dd, dm, ds));
  double y1 = y;

  double d = (sw == pa_types::coordinate_type::actual) ? 1.0 : -1.0;

  if (d == 1) {
    std::tuple<double, double> result = parallax_ha_l2870(x, y, rc, rp, rs, tp);

    return decimal_degrees_to_degree_hours(w_to_degrees(std::get<0>(result)));
  }

  double p1 = 0.0;
  double q1 = 0.0;
  double x_loop = x;
  double y_loop = y;

  while (1 == 1) {
    std::tuple<double, double> result =
        parallax_ha_l2870(x_loop, y_loop, rc, rp, rs, tp);

    double p2 = std::get<0>(result) - x_loop;
    double q2 = std::get<1>(result) - y_loop;

    double aa = std::abs(p2 - p1);
    double bb = std::abs(q2 - q1);

    if ((aa < 0.000001) && (bb < 0.000001)) {
      double p = x1 - p2;

      return decimal_degrees_to_degree_hours(w_to_degrees(p));
    }

    x_loop = x1 - p2;
    y_loop = y1 - q2;
    p1 = p2;
    q1 = q2;
  }
}

/**
 * \brief Helper function for parallax_ha
 *
 * @return tuple<double p, double q>
 */
std::tuple<double, double> parallax_ha_l2870(double x, double y, double rc,
                                             double rp, double rs, double tp) {
  double cx = cos(x);
  double sy = sin(y);
  double cy = cos(y);

  double aa = (rc * sin(x)) / ((rp * cy) - (rc * cx));

  double dx = atan(aa);
  double p = x + dx;
  double cp = cos(p);

  p = p - tp * floor(p / tp);
  double q = atan(cp * (rp * sy - rs) / (rp * cy * cx - rc));

  return std::tuple<double, double>{p, q};
}

/**
 * \brief Calculate corrected declination in decimal degrees
 *
 * Original macro name: ParallaxDec
 */
double parallax_dec(double hh, double hm, double hs, double dd, double dm,
                    double ds, pa_types::coordinate_type sw, double gp,
                    double ht, double hp) {
  double a = degrees_to_radians(gp);
  double c1 = cos(a);
  double s1 = sin(a);

  double u = atan(0.996647 * s1 / c1);

  double c2 = cos(u);
  double s2 = sin(u);
  double b = ht / 6378160;
  double rs = (0.996647 * s2) + (b * s1);

  double rc = c2 + (b * c1);
  double tp = 6.283185308;

  double rp = 1.0 / sin(degrees_to_radians(hp));

  double x =
      degrees_to_radians(degree_hours_to_decimal_degrees(hms_dh(hh, hm, hs)));
  double x1 = x;

  double y = degrees_to_radians(
      degrees_minutes_seconds_to_decimal_degrees(dd, dm, ds));
  double y1 = y;

  double d = (sw == pa_types::coordinate_type::actual) ? 1.0 : -1.0;

  if (d == 1) {
    std::tuple<double, double> result =
        parallax_dec_l2870(x, y, rc, rp, rs, tp);

    return w_to_degrees(std::get<1>(result));
  }

  double p1 = 0.0;
  double q1 = 0.0;

  double x_loop = x;
  double y_loop = y;

  while (1 == 1) {
    std::tuple<double, double> result =
        parallax_dec_l2870(x_loop, y_loop, rc, rp, rs, tp);
    double p2 = std::get<0>(result) - x_loop;
    double q2 = std::get<1>(result) - y_loop;
    double aa = std::abs(p2 - p1);

    if ((aa < 0.000001) && (b < 0.000001)) {
      double q = y1 - q2;

      return w_to_degrees(q);
    }
    x_loop = x1 - p2;
    y_loop = y1 - q2;
    p1 = p2;
    q1 = q2;
  }
}

/**
 * \brief Helper function for parallax_dec
 *
 * @return tuple<double p, double q>
 */
std::tuple<double, double> parallax_dec_l2870(double x, double y, double rc,
                                              double rp, double rs, double tp) {
  double cx = cos(x);
  double sy = sin(y);
  double cy = cos(y);

  double aa = (rc * sin(x)) / ((rp * cy) - (rc * cx));
  double dx = atan(aa);
  double p = x + dx;
  double cp = cos(p);

  p = p - tp * floor(p / tp);
  double q = atan(cp * (rp * sy - rs) / (rp * cy * cx - rc));

  return std::tuple<double, double>{p, q};
}

/**
 * \brief Calculate geocentric ecliptic longitude for the Moon
 *
 * Original macro name: MoonLong
 */
double moon_long(double lh, double lm, double ls, int ds, int zc, double dy,
                 int mn, int yr) {
  double ut =
      local_civil_time_to_universal_time(lh, lm, ls, ds, zc, dy, mn, yr);
  double gd = local_civil_time_greenwich_day(lh, lm, ls, ds, zc, dy, mn, yr);
  int gm = local_civil_time_greenwich_month(lh, lm, ls, ds, zc, dy, mn, yr);
  int gy = local_civil_time_greenwich_year(lh, lm, ls, ds, zc, dy, mn, yr);
  double t = ((civil_date_to_julian_date(gd, gm, gy) - 2415020) / 36525) +
             (ut / 876600);
  double t2 = t * t;

  double m1 = 27.32158213;
  double m2 = 365.2596407;
  double m3 = 27.55455094;
  double m4 = 29.53058868;
  double m5 = 27.21222039;
  double m6 = 6798.363307;
  double q = civil_date_to_julian_date(gd, gm, gy) - 2415020 + (ut / 24);
  m1 = q / m1;
  m2 = q / m2;
  m3 = q / m3;
  m4 = q / m4;
  m5 = q / m5;
  m6 = q / m6;
  m1 = 360 * (m1 - floor(m1));
  m2 = 360 * (m2 - floor(m2));
  m3 = 360 * (m3 - floor(m3));
  m4 = 360 * (m4 - floor(m4));
  m5 = 360 * (m5 - floor(m5));
  m6 = 360 * (m6 - floor(m6));

  double ml = 270.434164 + m1 - (0.001133 - 0.0000019 * t) * t2;
  double ms = 358.475833 + m2 - (0.00015 + 0.0000033 * t) * t2;
  double md = 296.104608 + m3 + (0.009192 + 0.0000144 * t) * t2;
  double me1 = 350.737486 + m4 - (0.001436 - 0.0000019 * t) * t2;
  double mf = 11.250889 + m5 - (0.003211 + 0.0000003 * t) * t2;
  double na = 259.183275 - m6 + (0.002078 + 0.0000022 * t) * t2;
  double a = degrees_to_radians(51.2 + 20.2 * t);
  double s1 = sin(a);
  double s2 = sin(degrees_to_radians(na));
  double b = 346.56 + (132.87 - 0.0091731 * t) * t;
  double s3 = 0.003964 * sin(degrees_to_radians(b));
  double c = degrees_to_radians(na + 275.05 - 2.3 * t);
  double s4 = sin(c);
  ml = ml + 0.000233 * s1 + s3 + 0.001964 * s2;
  ms = ms - 0.001778 * s1;
  md = md + 0.000817 * s1 + s3 + 0.002541 * s2;
  mf = mf + s3 - 0.024691 * s2 - 0.004328 * s4;
  me1 = me1 + 0.002011 * s1 + s3 + 0.001964 * s2;
  double e = 1.0 - (0.002495 + 0.00000752 * t) * t;
  double e2 = e * e;
  ml = degrees_to_radians(ml);
  ms = degrees_to_radians(ms);
  me1 = degrees_to_radians(me1);
  mf = degrees_to_radians(mf);
  md = degrees_to_radians(md);

  double l = 6.28875 * sin(md) + 1.274018 * sin(2 * me1 - md);
  l = l + 0.658309 * sin(2 * me1) + 0.213616 * sin(2 * md);
  l = l - e * 0.185596 * sin(ms) - 0.114336 * sin(2 * mf);
  l = l + 0.058793 * sin(2 * (me1 - md));
  l = l + 0.057212 * e * sin(2 * me1 - ms - md) + 0.05332 * sin(2 * me1 + md);
  l = l + 0.045874 * e * sin(2 * me1 - ms) + 0.041024 * e * sin(md - ms);
  l = l - 0.034718 * sin(me1) - e * 0.030465 * sin(ms + md);
  l = l + 0.015326 * sin(2 * (me1 - mf)) - 0.012528 * sin(2 * mf + md);
  l = l - 0.01098 * sin(2 * mf - md) + 0.010674 * sin(4 * me1 - md);
  l = l + 0.010034 * sin(3 * md) + 0.008548 * sin(4 * me1 - 2 * md);
  l = l - e * 0.00791 * sin(ms - md + 2 * me1) -
      e * 0.006783 * sin(2 * me1 + ms);
  l = l + 0.005162 * sin(md - me1) + e * 0.005 * sin(ms + me1);
  l = l + 0.003862 * sin(4 * me1) + e * 0.004049 * sin(md - ms + 2 * me1);
  l = l + 0.003996 * sin(2 * (md + me1)) + 0.003665 * sin(2 * me1 - 3 * md);
  l = l + e * 0.002695 * sin(2 * md - ms) + 0.002602 * sin(md - 2 * (mf + me1));
  l = l + e * 0.002396 * sin(2 * (me1 - md) - ms) - 0.002349 * sin(md + me1);
  l = l + e2 * 0.002249 * sin(2 * (me1 - ms)) - e * 0.002125 * sin(2 * md + ms);
  l = l - e2 * 0.002079 * sin(2 * ms) +
      e2 * 0.002059 * sin(2 * (me1 - ms) - md);
  l = l - 0.001773 * sin(md + 2 * (me1 - mf)) - 0.001595 * sin(2 * (mf + me1));
  l = l + e * 0.00122 * sin(4 * me1 - ms - md) - 0.00111 * sin(2 * (md + mf));
  l = l + 0.000892 * sin(md - 3 * me1) - e * 0.000811 * sin(ms + md + 2 * me1);
  l = l + e * 0.000761 * sin(4 * me1 - ms - 2 * md);
  l = l + e2 * 0.000704 * sin(md - 2 * (ms + me1));
  l = l + e * 0.000693 * sin(ms - 2 * (md - me1));
  l = l + e * 0.000598 * sin(2 * (me1 - mf) - ms);
  l = l + 0.00055 * sin(md + 4 * me1) + 0.000538 * sin(4 * md);
  l = l + e * 0.000521 * sin(4 * me1 - ms) + 0.000486 * sin(2 * md - me1);
  l = l + e2 * 0.000717 * sin(md - 2 * ms);

  double mm = unwind(ml + degrees_to_radians(l));

  return w_to_degrees(mm);
}

/**
 * \brief Calculate geocentric ecliptic latitude for the Moon
 *
 * Original macro name: MoonLat
 */
double moon_lat(double lh, double lm, double ls, int ds, int zc, double dy,
                int mn, int yr) {
  double ut =
      local_civil_time_to_universal_time(lh, lm, ls, ds, zc, dy, mn, yr);
  double gd = local_civil_time_greenwich_day(lh, lm, ls, ds, zc, dy, mn, yr);
  int gm = local_civil_time_greenwich_month(lh, lm, ls, ds, zc, dy, mn, yr);
  int gy = local_civil_time_greenwich_year(lh, lm, ls, ds, zc, dy, mn, yr);
  double t = ((civil_date_to_julian_date(gd, gm, gy) - 2415020) / 36525) +
             (ut / 876600);
  double t2 = t * t;

  double m1 = 27.32158213;
  double m2 = 365.2596407;
  double m3 = 27.55455094;
  double m4 = 29.53058868;
  double m5 = 27.21222039;
  double m6 = 6798.363307;
  double q = civil_date_to_julian_date(gd, gm, gy) - 2415020 + (ut / 24);
  m1 = q / m1;
  m2 = q / m2;
  m3 = q / m3;
  m4 = q / m4;
  m5 = q / m5;
  m6 = q / m6;
  m1 = 360 * (m1 - floor(m1));
  m2 = 360 * (m2 - floor(m2));
  m3 = 360 * (m3 - floor(m3));
  m4 = 360 * (m4 - floor(m4));
  m5 = 360 * (m5 - floor(m5));
  m6 = 360 * (m6 - floor(m6));

  double ml = 270.434164 + m1 - (0.001133 - 0.0000019 * t) * t2;
  double ms = 358.475833 + m2 - (0.00015 + 0.0000033 * t) * t2;
  double md = 296.104608 + m3 + (0.009192 + 0.0000144 * t) * t2;
  double me1 = 350.737486 + m4 - (0.001436 - 0.0000019 * t) * t2;
  double mf = 11.250889 + m5 - (0.003211 + 0.0000003 * t) * t2;
  double na = 259.183275 - m6 + (0.002078 + 0.0000022 * t) * t2;
  double a = degrees_to_radians(51.2 + 20.2 * t);
  double s1 = sin(a);
  double s2 = sin(degrees_to_radians(na));
  double b = 346.56 + (132.87 - 0.0091731 * t) * t;
  double s3 = 0.003964 * sin(degrees_to_radians(b));
  double c = degrees_to_radians(na + 275.05 - 2.3 * t);
  double s4 = sin(c);
  ml = ml + 0.000233 * s1 + s3 + 0.001964 * s2;
  ms = ms - 0.001778 * s1;
  md = md + 0.000817 * s1 + s3 + 0.002541 * s2;
  mf = mf + s3 - 0.024691 * s2 - 0.004328 * s4;
  me1 = me1 + 0.002011 * s1 + s3 + 0.001964 * s2;
  double e = 1.0 - (0.002495 + 0.00000752 * t) * t;
  double e2 = e * e;
  ms = degrees_to_radians(ms);
  na = degrees_to_radians(na);
  me1 = degrees_to_radians(me1);
  mf = degrees_to_radians(mf);
  md = degrees_to_radians(md);

  double g = 5.128189 * sin(mf) + 0.280606 * sin(md + mf);
  g = g + 0.277693 * sin(md - mf) + 0.173238 * sin(2 * me1 - mf);
  g = g + 0.055413 * sin(2 * me1 + mf - md) + 0.046272 * sin(2 * me1 - mf - md);
  g = g + 0.032573 * sin(2 * me1 + mf) + 0.017198 * sin(2 * md + mf);
  g = g + 0.009267 * sin(2 * me1 + md - mf) + 0.008823 * sin(2 * md - mf);
  g = g + e * 0.008247 * sin(2 * me1 - ms - mf) +
      0.004323 * sin(2 * (me1 - md) - mf);
  g = g + 0.0042 * sin(2 * me1 + mf + md) +
      e * 0.003372 * sin(mf - ms - 2 * me1);
  g = g + e * 0.002472 * sin(2 * me1 + mf - ms - md);
  g = g + e * 0.002222 * sin(2 * me1 + mf - ms);
  g = g + e * 0.002072 * sin(2 * me1 - mf - ms - md);
  g = g + e * 0.001877 * sin(mf - ms + md) + 0.001828 * sin(4 * me1 - mf - md);
  g = g - e * 0.001803 * sin(mf + ms) - 0.00175 * sin(3 * mf);
  g = g + e * 0.00157 * sin(md - ms - mf) - 0.001487 * sin(mf + me1);
  g = g - e * 0.001481 * sin(mf + ms + md) + e * 0.001417 * sin(mf - ms - md);
  g = g + e * 0.00135 * sin(mf - ms) + 0.00133 * sin(mf - me1);
  g = g + 0.001106 * sin(mf + 3 * md) + 0.00102 * sin(4 * me1 - mf);
  g = g + 0.000833 * sin(mf + 4 * me1 - md) + 0.000781 * sin(md - 3 * mf);
  g = g + 0.00067 * sin(mf + 4 * me1 - 2 * md) +
      0.000606 * sin(2 * me1 - 3 * mf);
  g = g + 0.000597 * sin(2 * (me1 + md) - mf);
  g = g + e * 0.000492 * sin(2 * me1 + md - ms - mf) +
      0.00045 * sin(2 * (md - me1) - mf);
  g = g + 0.000439 * sin(3 * md - mf) + 0.000423 * sin(mf + 2 * (me1 + md));
  g = g + 0.000422 * sin(2 * me1 - mf - 3 * md) -
      e * 0.000367 * sin(ms + mf + 2 * me1 - md);
  g = g - e * 0.000353 * sin(ms + mf + 2 * me1) + 0.000331 * sin(mf + 4 * me1);
  g = g + e * 0.000317 * sin(2 * me1 + mf - ms + md);
  g = g + e2 * 0.000306 * sin(2 * (me1 - ms) - mf) -
      0.000283 * sin(md + 3 * mf);

  double w1 = 0.0004664 * cos(na);
  double w2 = 0.0000754 * cos(c);
  double bm = degrees_to_radians(g) * (1.0 - w1 - w2);

  return w_to_degrees(bm);
}

/**
 * \brief Calculate horizontal parallax for the Moon
 *
 * Original macro name: MoonHP
 */
double moon_hp(double lh, double lm, double ls, int ds, int zc, double dy,
               int mn, int yr) {
  double ut =
      local_civil_time_to_universal_time(lh, lm, ls, ds, zc, dy, mn, yr);
  double gd = local_civil_time_greenwich_day(lh, lm, ls, ds, zc, dy, mn, yr);
  int gm = local_civil_time_greenwich_month(lh, lm, ls, ds, zc, dy, mn, yr);
  int gy = local_civil_time_greenwich_year(lh, lm, ls, ds, zc, dy, mn, yr);
  double t = ((civil_date_to_julian_date(gd, gm, gy) - 2415020) / 36525) +
             (ut / 876600);
  double t2 = t * t;

  double m1 = 27.32158213;
  double m2 = 365.2596407;
  double m3 = 27.55455094;
  double m4 = 29.53058868;
  double m5 = 27.21222039;
  double m6 = 6798.363307;
  double q = civil_date_to_julian_date(gd, gm, gy) - 2415020 + (ut / 24);
  m1 = q / m1;
  m2 = q / m2;
  m3 = q / m3;
  m4 = q / m4;
  m5 = q / m5;
  m6 = q / m6;
  m1 = 360 * (m1 - floor(m1));
  m2 = 360 * (m2 - floor(m2));
  m3 = 360 * (m3 - floor(m3));
  m4 = 360 * (m4 - floor(m4));
  m5 = 360 * (m5 - floor(m5));
  m6 = 360 * (m6 - floor(m6));

  double ml = 270.434164 + m1 - (0.001133 - 0.0000019 * t) * t2;
  double ms = 358.475833 + m2 - (0.00015 + 0.0000033 * t) * t2;
  double md = 296.104608 + m3 + (0.009192 + 0.0000144 * t) * t2;
  double me1 = 350.737486 + m4 - (0.001436 - 0.0000019 * t) * t2;
  double mf = 11.250889 + m5 - (0.003211 + 0.0000003 * t) * t2;
  double na = 259.183275 - m6 + (0.002078 + 0.0000022 * t) * t2;
  double a = degrees_to_radians(51.2 + 20.2 * t);
  double s1 = sin(a);
  double s2 = sin(degrees_to_radians(na));
  double b = 346.56 + (132.87 - 0.0091731 * t) * t;
  double s3 = 0.003964 * sin(degrees_to_radians(b));
  double c = degrees_to_radians(na + 275.05 - 2.3 * t);
  double s4 = sin(c);
  ml = ml + 0.000233 * s1 + s3 + 0.001964 * s2;
  ms = ms - 0.001778 * s1;
  md = md + 0.000817 * s1 + s3 + 0.002541 * s2;
  mf = mf + s3 - 0.024691 * s2 - 0.004328 * s4;
  me1 = me1 + 0.002011 * s1 + s3 + 0.001964 * s2;
  double e = 1.0 - (0.002495 + 0.00000752 * t) * t;
  double e2 = e * e;
  ms = degrees_to_radians(ms);
  me1 = degrees_to_radians(me1);
  mf = degrees_to_radians(mf);
  md = degrees_to_radians(md);

  double pm = 0.950724 + 0.051818 * cos(md) + 0.009531 * cos(2 * me1 - md);
  pm = pm + 0.007843 * cos(2 * me1) + 0.002824 * cos(2 * md);
  pm = pm + 0.000857 * cos(2 * me1 + md) + e * 0.000533 * cos(2 * me1 - ms);
  pm = pm + e * 0.000401 * cos(2 * me1 - md - ms);
  pm = pm + e * 0.00032 * cos(md - ms) - 0.000271 * cos(me1);
  pm = pm - e * 0.000264 * cos(ms + md) - 0.000198 * cos(2 * mf - md);
  pm = pm + 0.000173 * cos(3 * md) + 0.000167 * cos(4 * me1 - md);
  pm = pm - e * 0.000111 * cos(ms) + 0.000103 * cos(4 * me1 - 2 * md);
  pm = pm - 0.000084 * cos(2 * md - 2 * me1) - e * 0.000083 * cos(2 * me1 + ms);
  pm = pm + 0.000079 * cos(2 * me1 + 2 * md) + 0.000072 * cos(4 * me1);
  pm = pm + e * 0.000064 * cos(2 * me1 - ms + md) -
       e * 0.000063 * cos(2 * me1 + ms - md);
  pm = pm + e * 0.000041 * cos(ms + me1) + e * 0.000035 * cos(2 * md - ms);
  pm = pm - 0.000033 * cos(3 * md - 2 * me1) - 0.00003 * cos(md + me1);
  pm = pm - 0.000029 * cos(2 * (mf - me1)) - e * 0.000029 * cos(2 * md + ms);
  pm = pm + e2 * 0.000026 * cos(2 * (me1 - ms)) -
       0.000023 * cos(2 * (mf - me1) + md);
  pm = pm + e * 0.000019 * cos(4 * me1 - ms - md);

  return pm;
}

/**
 * \brief Convert angle in radians to equivalent angle in degrees.
 *
 * Original macro name: Unwind
 */
double unwind(double w) { return w - 6.283185308 * floor(w / 6.283185308); }

} // namespace pa_macros