#include "pa_macros.h"
#include "pa_data.h"
#include "pa_models.h"
#include "pa_types.h"
#include "pa_util.h"
#include <cmath>
#include <string.h>
#include <tuple>
#include <vector>

using namespace pa_types;
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
double HmsToDh(double hours, double minutes, double seconds) {
  double fHours = hours;
  double fMinutes = minutes;
  double fSeconds = seconds;

  double a = std::abs(fSeconds) / 60;
  double b = (std::abs(fMinutes) + a) / 60;
  double c = std::abs(fHours) + b;

  return (fHours < 0 || fMinutes < 0 || fSeconds < 0) ? -c : c;
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
int DecimalHoursHour(double decimalHours) {
  double a = std::abs(decimalHours);
  double b = a * 3600;
  double c = Round(b - 60 * floor(b / 60), 2);
  double e = (c == 60) ? b + 60 : b;

  return (decimalHours < 0) ? (int)-(floor(e / 3600)) : (int)floor(e / 3600);
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
int DecimalHoursMinute(double decimalHours) {
  double a = std::abs(decimalHours);
  double b = a * 3600;
  double c = Round(b - 60 * floor(b / 60), 2);
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
double DecimalHoursSecond(double decimalHours) {
  double a = std::abs(decimalHours);
  double b = a * 3600;
  double c = Round(b - 60 * floor(b / 60), 2);
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
double CivilDateToJulianDate(double day, double month, double year) {
  double fDay = (double)day;
  double fMonth = (double)month;
  double fYear = (double)year;

  double y = (fMonth < 3) ? fYear - 1 : fYear;
  double m = (fMonth < 3) ? fMonth + 12 : fMonth;

  double b;

  if (fYear > 1582) {
    double a = floor(y / 100);
    b = 2 - a + floor(a / 4);
  } else {
    if (fYear == 1582 && fMonth > 10) {
      double a = floor(y / 100);
      b = 2 - a + floor(a / 4);
    } else {
      if (fYear == 1582 && fMonth == 10 && fDay >= 15) {
        double a = floor(y / 100);
        b = 2 - a + floor(a / 4);
      } else
        b = 0;
    }
  }

  double c = (y < 0) ? floor(((365.25 * y) - 0.75)) : floor(365.25 * y);
  double d = floor(30.6001 * (m + 1.0));

  return b + c + d + fDay + 1720994.5;
}

/**
 * \brief Returns the day part of a Julian Date
 *
 * Original macro name: JDCDay
 */
double JulianDateDay(double julianDate) {
  double i = floor(julianDate + 0.5);
  double f = julianDate + 0.5 - i;
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
int JulianDateMonth(double julianDate) {
  double i = floor(julianDate + 0.5);
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
int JulianDateYear(double julianDate) {
  double i = floor(julianDate + 0.5);
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
double RightAscensionToHourAngle(double raHours, double raMinutes,
                                 double raSeconds, double lctHours,
                                 double lctMinutes, double lctSeconds,
                                 int daylightSaving, int zoneCorrection,
                                 double localDay, int localMonth, int localYear,
                                 double geographicalLongitude) {
  double a = LocalCivilTimeToUniversalTime(lctHours, lctMinutes, lctSeconds,
                                           daylightSaving, zoneCorrection,
                                           localDay, localMonth, localYear);
  double b = LocalCivilTimeGreenwichDay(lctHours, lctMinutes, lctSeconds,
                                        daylightSaving, zoneCorrection,
                                        localDay, localMonth, localYear);
  int c = LocalCivilTimeGreenwichMonth(lctHours, lctMinutes, lctSeconds,
                                       daylightSaving, zoneCorrection, localDay,
                                       localMonth, localYear);
  int d = LocalCivilTimeGreenwichYear(lctHours, lctMinutes, lctSeconds,
                                      daylightSaving, zoneCorrection, localDay,
                                      localMonth, localYear);
  double e = UniversalTimeToGreenwichSiderealTime(a, 0, 0, b, c, d);
  double f =
      GreenwichSiderealTimeToLocalSiderealTime(e, 0, 0, geographicalLongitude);
  double g = HmsToDh(raHours, raMinutes, raSeconds);
  double h = f - g;

  return (h < 0) ? 24 + h : h;
}

/**
 * \brief Convert Hour Angle to Right Ascension
 *
 * Original macro name: HARA
 */
double HourAngleToRightAscension(double hourAngleHours, double hourAngleMinutes,
                                 double hourAngleSeconds, double lctHours,
                                 double lctMinutes, double lctSeconds,
                                 int daylightSaving, int zoneCorrection,
                                 double localDay, int localMonth, int localYear,
                                 double geographicalLongitude) {
  double a = LocalCivilTimeToUniversalTime(lctHours, lctMinutes, lctSeconds,
                                           daylightSaving, zoneCorrection,
                                           localDay, localMonth, localYear);
  double b = LocalCivilTimeGreenwichDay(lctHours, lctMinutes, lctSeconds,
                                        daylightSaving, zoneCorrection,
                                        localDay, localMonth, localYear);
  int c = LocalCivilTimeGreenwichMonth(lctHours, lctMinutes, lctSeconds,
                                       daylightSaving, zoneCorrection, localDay,
                                       localMonth, localYear);
  int d = LocalCivilTimeGreenwichYear(lctHours, lctMinutes, lctSeconds,
                                      daylightSaving, zoneCorrection, localDay,
                                      localMonth, localYear);
  double e = UniversalTimeToGreenwichSiderealTime(a, 0, 0, b, c, d);
  double f =
      GreenwichSiderealTimeToLocalSiderealTime(e, 0, 00, geographicalLongitude);
  double g = HmsToDh(hourAngleHours, hourAngleMinutes, hourAngleSeconds);
  double h = f - g;

  return (h < 0) ? 24 + h : h;
}

/**
 * \brief Convert Local Civil Time to Universal Time
 *
 * Original macro name: LctUT
 */
double LocalCivilTimeToUniversalTime(double lctHours, double lctMinutes,
                                     double lctSeconds, int daylightSaving,
                                     int zoneCorrection, double localDay,
                                     int localMonth, int localYear) {
  double a = HmsToDh(lctHours, lctMinutes, lctSeconds);
  double b = a - daylightSaving - zoneCorrection;
  double c = localDay + (b / 24);
  double d = CivilDateToJulianDate(c, localMonth, localYear);
  double e = JulianDateDay(d);
  double e1 = floor(e);

  return 24 * (e - e1);
}

/**
 * \brief Convert Universal Time to Local Civil Time
 *
 * Original macro name: UTLct
 */
double UniversalTimeToLocalCivilTime(double uHours, double uMinutes,
                                     double uSeconds, int daylightSaving,
                                     int zoneCorrection, double greenwichDay,
                                     int greenwichMonth, int greenwichYear) {
  double a = HmsToDh(uHours, uMinutes, uSeconds);
  double b = a + zoneCorrection;
  double c = b + daylightSaving;
  double d =
      CivilDateToJulianDate(greenwichDay, greenwichMonth, greenwichYear) +
      (c / 24);
  double e = JulianDateDay(d);
  double e1 = floor(e);

  return 24 * (e - e1);
}

/**
 * Get Local Civil Day for Universal Time
 *
 * Original macro name: UTLcDay
 */
double UniversalTimeLocalCivilDay(double u_hours, double u_minutes,
                                  double u_seconds, int daylight_saving,
                                  int zone_correction, double greenwich_day,
                                  int greenwich_month, int greenwich_year) {
  double a = HmsToDh(u_hours, u_minutes, u_seconds);
  double b = a + zone_correction;
  double c = b + daylight_saving;
  double d =
      CivilDateToJulianDate(greenwich_day, greenwich_month, greenwich_year) +
      (c / 24.0);
  double e = JulianDateDay(d);
  double e1 = floor(e);

  return e1;
}

/**
 * Get Local Civil Month for Universal Time
 *
 * Original macro name: UTLcMonth
 */
int UniversalTimeLocalCivilMonth(double u_hours, double u_minutes,
                                 double u_seconds, int daylight_saving,
                                 int zone_correction, double greenwich_day,
                                 int greenwich_month, int greenwich_year) {
  double a = HmsToDh(u_hours, u_minutes, u_seconds);
  double b = a + zone_correction;
  double c = b + daylight_saving;
  double d =
      CivilDateToJulianDate(greenwich_day, greenwich_month, greenwich_year) +
      (c / 24.0);

  return JulianDateMonth(d);
}

/**
 * Get Local Civil Year for Universal Time
 *
 * Original macro name: UTLcYear
 */
int UniversalTimeLocalCivilYear(double u_hours, double u_minutes,
                                double u_seconds, int daylight_saving,
                                int zone_correction, double greenwich_day,
                                int greenwich_month, int greenwich_year) {
  double a = HmsToDh(u_hours, u_minutes, u_seconds);
  double b = a + zone_correction;
  double c = b + daylight_saving;
  double d =
      CivilDateToJulianDate(greenwich_day, greenwich_month, greenwich_year) +
      (c / 24.0);

  return JulianDateYear(d);
}

/**
 * \brief Determine Greenwich Day for Local Time
 *
 * Original macro name: LctGDay
 */
double LocalCivilTimeGreenwichDay(double lctHours, double lctMinutes,
                                  double lctSeconds, int daylightSaving,
                                  int zoneCorrection, double localDay,
                                  int localMonth, int localYear) {
  double a = HmsToDh(lctHours, lctMinutes, lctSeconds);
  double b = a - daylightSaving - zoneCorrection;
  double c = localDay + (b / 24);
  double d = CivilDateToJulianDate(c, localMonth, localYear);
  double e = JulianDateDay(d);

  return floor(e);
}

/**
 * \brief Determine Greenwich Month for Local Time
 *
 * Original macro name: LctGMonth
 */
double LocalCivilTimeGreenwichMonth(double lctHours, double lctMinutes,
                                    double lctSeconds, int daylightSaving,
                                    int zoneCorrection, double localDay,
                                    int localMonth, int localYear) {
  double a = HmsToDh(lctHours, lctMinutes, lctSeconds);
  double b = a - daylightSaving - zoneCorrection;
  double c = localDay + (b / 24);
  double d = CivilDateToJulianDate(c, localMonth, localYear);

  return JulianDateMonth(d);
}

/**
 * \brief Determine Greenwich Year for Local Time
 *
 * Original macro name: LctGYear
 */
double LocalCivilTimeGreenwichYear(double lctHours, double lctMinutes,
                                   double lctSeconds, int daylightSaving,
                                   int zoneCorrection, double localDay,
                                   int localMonth, int localYear) {
  double a = HmsToDh(lctHours, lctMinutes, lctSeconds);
  double b = a - daylightSaving - zoneCorrection;
  double c = localDay + (b / 24);
  double d = CivilDateToJulianDate(c, localMonth, localYear);

  return JulianDateYear(d);
}

/**
 * \brief Convert Universal Time to Greenwich Sidereal Time
 *
 * Original macro name: UTGST
 */
double UniversalTimeToGreenwichSiderealTime(double uHours, double uMinutes,
                                            double uSeconds,
                                            double greenwichDay,
                                            int greenwichMonth,
                                            int greenwichYear) {
  double a = CivilDateToJulianDate(greenwichDay, greenwichMonth, greenwichYear);
  double b = a - 2451545;
  double c = b / 36525;
  double d = 6.697374558 + (2400.051336 * c) + (0.000025862 * c * c);
  double e = d - (24 * floor(d / 24));
  double f = HmsToDh(uHours, uMinutes, uSeconds);
  double g = f * 1.002737909;
  double h = e + g;

  return h - (24 * floor(h / 24));
}

/**
 * \brief Convert Greenwich Sidereal Time to Local Sidereal Time
 *
 * Original macro name: GSTLST
 */
double GreenwichSiderealTimeToLocalSiderealTime(double greenwichHours,
                                                double greenwichMinutes,
                                                double greenwichSeconds,
                                                double geographicalLongitude) {
  double a = HmsToDh(greenwichHours, greenwichMinutes, greenwichSeconds);
  double b = geographicalLongitude / 15;
  double c = a + b;

  return c - (24 * floor(c / 24));
}

/**
 * \brief Convert Equatorial Coordinates to Azimuth (in decimal degrees)
 *
 * Original macro name: EQAz
 */
double EquatorialCoordinatesToAzimuth(
    double hourAngleHours, double hourAngleMinutes, double hourAngleSeconds,
    double declinationDegrees, double declinationMinutes,
    double declinationSeconds, double geographicalLatitude) {
  double a = HmsToDh(hourAngleHours, hourAngleMinutes, hourAngleSeconds);
  double b = a * 15;
  double c = DegreesToRadians(b);
  double d = DegreesMinutesSecondsToDecimalDegrees(
      declinationDegrees, declinationMinutes, declinationSeconds);
  double e = DegreesToRadians(d);
  double f = DegreesToRadians(geographicalLatitude);
  double g = sin(e) * sin(f) + cos(e) * cos(f) * cos(c);
  double h = -cos(e) * cos(f) * sin(c);
  double i = sin(e) - (sin(f) * g);
  double j = WToDegrees(atan2(h, i));

  return j - 360.0 * floor(j / 360);
}

/**
 * \brief Convert Equatorial Coordinates to Altitude (in decimal degrees)
 *
 * Original macro name: EQAlt
 */
double EquatorialCoordinatesToAltitude(
    double hourAngleHours, double hourAngleMinutes, double hourAngleSeconds,
    double declinationDegrees, double declinationMinutes,
    double declinationSeconds, double geographicalLatitude) {
  double a = HmsToDh(hourAngleHours, hourAngleMinutes, hourAngleSeconds);
  double b = a * 15;
  double c = DegreesToRadians(b);
  double d = DegreesMinutesSecondsToDecimalDegrees(
      declinationDegrees, declinationMinutes, declinationSeconds);
  double e = DegreesToRadians(d);
  double f = DegreesToRadians(geographicalLatitude);
  double g = sin(e) * sin(f) + cos(e) * cos(f) * cos(c);

  return WToDegrees(asin(g));
}

/**
 * \brief Convert Degrees Minutes Seconds to Decimal Degrees
 *
 * Original macro name: DMSDD
 */
double DegreesMinutesSecondsToDecimalDegrees(double degrees, double minutes,
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
double WToDegrees(double w) { return w * 57.29577951; }

/**
 * \brief Return Degrees part of Decimal Degrees
 *
 * Original macro name: DDDeg
 */
double DecimalDegreesDegrees(double decimalDegrees) {
  double a = std::abs(decimalDegrees);
  double b = a * 3600;
  double c = Round(b - 60 * floor(b / 60), 2);
  double e = (c == 60) ? 60 : b;

  return (decimalDegrees < 0) ? -(floor(e / 3600)) : floor(e / 3600);
}

/**
 * \brief Return Minutes part of Decimal Degrees
 *
 * Original macro name: DDMin
 */
double DecimalDegreesMinutes(double decimalDegrees) {
  double a = std::abs(decimalDegrees);
  double b = a * 3600;
  double c = Round(b - 60 * floor(b / 60), 2);
  double e = (c == 60) ? b + 60 : b;

  return (int)floor(e / 60) % 60;
}

/**
 * \brief Return Seconds part of Decimal Degrees
 *
 * Original macro name: DDSec
 */
double DecimalDegreesSeconds(double decimalDegrees) {
  double a = std::abs(decimalDegrees);
  double b = a * 3600;
  double c = Round(b - 60 * floor(b / 60), 2);
  double d = (c == 60) ? 0 : c;

  return d;
}

/**
 * \brief Convert Decimal Degrees to Degree-Hours
 *
 * Original macro name: DDDH
 */
double DecimalDegreesToDegreeHours(double decimalDegrees) {
  return decimalDegrees / 15;
}

/**
 * \brief Convert Degree-Hours to Decimal Degrees
 *
 * Original macro name: DHDD
 */
double DegreeHoursToDecimalDegrees(double degreeHours) {
  return degreeHours * 15;
}

/**
 * \brief Convert Horizon Coordinates to Declination (in decimal degrees)
 *
 * Original macro name: HORDec
 */
double
HorizonCoordinatesToDeclination(double azimuthDegrees, double azimuthMinutes,
                                double azimuthSeconds, double altitudeDegrees,
                                double altitudeMinutes, double altitudeSeconds,
                                double geographicalLatitude) {
  double a = DegreesMinutesSecondsToDecimalDegrees(
      azimuthDegrees, azimuthMinutes, azimuthSeconds);
  double b = DegreesMinutesSecondsToDecimalDegrees(
      altitudeDegrees, altitudeMinutes, altitudeSeconds);
  double c = DegreesToRadians(a);
  double d = DegreesToRadians(b);
  double e = DegreesToRadians(geographicalLatitude);
  double f = sin(d) * sin(e) + cos(d) * cos(e) * cos(c);

  return WToDegrees(asin(f));
}

/**
 * \brief Convert Horizon Coordinates to Hour Angle (in decimal degrees)
 *
 * Original macro name: HORHa
 */
double
HorizonCoordinatesToHourAngle(double azimuthDegrees, double azimuthMinutes,
                              double azimuthSeconds, double altitudeDegrees,
                              double altitudeMinutes, double altitudeSeconds,
                              double geographicalLatitude) {
  double a = DegreesMinutesSecondsToDecimalDegrees(
      azimuthDegrees, azimuthMinutes, azimuthSeconds);
  double b = DegreesMinutesSecondsToDecimalDegrees(
      altitudeDegrees, altitudeMinutes, altitudeSeconds);
  double c = DegreesToRadians(a);
  double d = DegreesToRadians(b);
  double e = DegreesToRadians(geographicalLatitude);
  double f = sin(d) * sin(e) + cos(d) * cos(e) * cos(c);
  double g = -cos(d) * cos(e) * sin(c);
  double h = sin(d) - sin(e) * f;
  double i = DecimalDegreesToDegreeHours(WToDegrees(atan2(g, h)));

  return i - 24 * floor(i / 24);
}

/**
 * \brief Obliquity of the Ecliptic for a Greenwich Date
 *
 * Original macro name: Obliq
 */
double Obliq(double greenwichDay, int greenwichMonth, int greenwichYear) {
  double a = CivilDateToJulianDate(greenwichDay, greenwichMonth, greenwichYear);
  double b = a - 2415020;
  double c = (b / 36525) - 1;
  double d = c * (46.815 + c * (0.0006 - (c * 0.00181)));
  double e = d / 3600;

  return 23.43929167 - e +
         NutatObl(greenwichDay, greenwichMonth, greenwichYear);
}

/**
 * \brief Nutation amount to be added in ecliptic longitude, in degrees.
 *
 * Original macro name: NutatLong
 */
double NutatLong(double gd, int gm, int gy) {
  double dj = CivilDateToJulianDate(gd, gm, gy) - 2415020;
  double t = dj / 36525;
  double t2 = t * t;

  double a = 100.0021358 * t;
  double b = 360 * (a - floor(a));

  double l1 = 279.6967 + 0.000303 * t2 + b;
  double l2 = 2 * DegreesToRadians(l1);

  a = 1336.855231 * t;
  b = 360 * (a - floor(a));

  double d1 = 270.4342 - 0.001133 * t2 + b;
  double d2 = 2 * DegreesToRadians(d1);

  a = 99.99736056 * t;
  b = 360 * (a - floor(a));

  double m1 = 358.4758 - 0.00015 * t2 + b;
  m1 = DegreesToRadians(m1);

  a = 1325.552359 * t;
  b = 360 * (a - floor(a));

  double m2 = 296.1046 + 0.009192 * t2 + b;
  m2 = DegreesToRadians(m2);

  a = 5.372616667 * t;
  b = 360 * (a - floor(a));

  double n1 = 259.1833 + 0.002078 * t2 - b;
  n1 = DegreesToRadians(n1);

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
double NutatObl(double greenwichDay, int greenwichMonth, int greenwichYear) {
  double dj =
      CivilDateToJulianDate(greenwichDay, greenwichMonth, greenwichYear) -
      2415020;
  double t = dj / 36525;
  double t2 = t * t;

  double a = 100.0021358 * t;
  double b = 360 * (a - floor(a));

  double l1 = 279.6967 + 0.000303 * t2 + b;
  double l2 = 2 * DegreesToRadians(l1);

  a = 1336.855231 * t;
  b = 360 * (a - floor(a));

  double d1 = 270.4342 - 0.001133 * t2 + b;
  double d2 = 2 * DegreesToRadians(d1);

  a = 99.99736056 * t;
  b = 360 * (a - floor(a));

  double m1 = DegreesToRadians(358.4758 - 0.00015 * t2 + b);

  a = 1325.552359 * t;
  b = 360 * (a - floor(a));

  double m2 = DegreesToRadians(296.1046 + 0.009192 * t2 + b);

  a = 5.372616667 * t;
  b = 360 * (a - floor(a));

  double n1 = DegreesToRadians(259.1833 + 0.002078 * t2 - b);

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
double LocalSiderealTimeToGreenwichSiderealTime(double localHours,
                                                double localMinutes,
                                                double localSeconds,
                                                double longitude) {
  double a = HmsToDh(localHours, localMinutes, localSeconds);
  double b = longitude / 15;
  double c = a - b;

  return c - (24 * floor(c / 24));
}

/**
 * \brief Convert Greenwich Sidereal Time to Universal Time
 *
 * Original macro name: GSTUT
 */
double GreenwichSiderealTimeToUniversalTime(double greenwichSiderealHours,
                                            double greenwichSiderealMinutes,
                                            double greenwichSiderealSeconds,
                                            double greenwichDay,
                                            int greenwichMonth,
                                            int greenwichYear) {
  double a = CivilDateToJulianDate(greenwichDay, greenwichMonth, greenwichYear);
  double b = a - 2451545;
  double c = b / 36525;
  double d = 6.697374558 + (2400.051336 * c) + (0.000025862 * c * c);
  double e = d - (24 * floor(d / 24));
  double f = HmsToDh(greenwichSiderealHours, greenwichSiderealMinutes,
                     greenwichSiderealSeconds);
  double g = f - e;
  double h = g - (24 * floor(g / 24));

  return h * 0.9972695663;
}

/**
 * \brief Calculate Sun's ecliptic longitude
 *
 * Original macro name: SunLong
 */
double SunLong(double lch, double lcm, double lcs, int ds, int zc, double ld,
               int lm, int ly) {
  double aa = LocalCivilTimeGreenwichDay(lch, lcm, lcs, ds, zc, ld, lm, ly);
  int bb = LocalCivilTimeGreenwichMonth(lch, lcm, lcs, ds, zc, ld, lm, ly);
  int cc = LocalCivilTimeGreenwichYear(lch, lcm, lcs, ds, zc, ld, lm, ly);
  double ut = LocalCivilTimeToUniversalTime(lch, lcm, lcs, ds, zc, ld, lm, ly);
  double dj = CivilDateToJulianDate(aa, bb, cc) - 2415020;
  double t = (dj / 36525) + (ut / 876600);
  double t2 = t * t;
  double a = 100.0021359 * t;
  double b = 360.0 * (a - floor(a));

  double l = 279.69668 + 0.0003025 * t2 + b;
  a = 99.99736042 * t;
  b = 360 * (a - floor(a));

  double m1 = 358.47583 - (0.00015 + 0.0000033 * t) * t2 + b;
  double ec = 0.01675104 - 0.0000418 * t - 0.000000126 * t2;

  double am = DegreesToRadians(m1);
  double at = TrueAnomaly(am, ec);

  a = 62.55209472 * t;
  b = 360 * (a - floor(a));

  double a1 = DegreesToRadians(153.23 + b);
  a = 125.1041894 * t;
  b = 360 * (a - floor(a));

  double b1 = DegreesToRadians(216.57 + b);
  a = 91.56766028 * t;
  b = 360 * (a - floor(a));

  double c1 = DegreesToRadians(312.69 + b);
  a = 1236.853095 * t;
  b = 360 * (a - floor(a));

  double d1 = DegreesToRadians(350.74 - 0.00144 * t2 + b);
  double e1 = DegreesToRadians(231.19 + 20.2 * t);
  a = 183.1353208 * t;
  b = 360 * (a - floor(a));
  double h1 = DegreesToRadians(353.4 + b);

  double d2 = 0.00134 * cos(a1) + 0.00154 * cos(b1) + 0.002 * cos(c1);
  d2 = d2 + 0.00179 * sin(d1) + 0.00178 * sin(e1);
  double d3 = 0.00000543 * sin(a1) + 0.00001575 * sin(b1);
  d3 = d3 + 0.00001627 * sin(c1) + 0.00003076 * cos(d1);

  double sr = at + DegreesToRadians(l - m1 + d2);
  double tp = 6.283185308;

  sr = sr - tp * floor(sr / tp);

  return WToDegrees(sr);
}

/**
 * \brief Calculate Sun's angular diameter in decimal degrees
 *
 * Original macro name: SunDia
 */
double SunDia(double lch, double lcm, double lcs, int ds, int zc, double ld,
              int lm, int ly) {
  double a = SunDist(lch, lcm, lcs, ds, zc, ld, lm, ly);

  return 0.533128 / a;
}

/**
 * \brief Calculate Sun's distance from the Earth in astronomical units
 *
 * Original macro name: SunDist
 */
double SunDist(double lch, double lcm, double lcs, int ds, int zc, double ld,
               int lm, int ly) {
  double aa = LocalCivilTimeGreenwichDay(lch, lcm, lcs, ds, zc, ld, lm, ly);
  int bb = LocalCivilTimeGreenwichMonth(lch, lcm, lcs, ds, zc, ld, lm, ly);
  int cc = LocalCivilTimeGreenwichYear(lch, lcm, lcs, ds, zc, ld, lm, ly);
  double ut = LocalCivilTimeToUniversalTime(lch, lcm, lcs, ds, zc, ld, lm, ly);
  double dj = CivilDateToJulianDate(aa, bb, cc) - 2415020;

  double t = (dj / 36525) + (ut / 876600);
  double t2 = t * t;

  double a = 100.0021359 * t;
  double b = 360 * (a - floor(a));
  a = 99.99736042 * t;
  b = 360 * (a - floor(a));
  double m1 = 358.47583 - (0.00015 + 0.0000033 * t) * t2 + b;
  double ec = 0.01675104 - 0.0000418 * t - 0.000000126 * t2;

  double am = DegreesToRadians(m1);
  double ae = EccentricAnomaly(am, ec);

  a = 62.55209472 * t;
  b = 360 * (a - floor(a));
  double a1 = DegreesToRadians(153.23 + b);
  a = 125.1041894 * t;
  b = 360 * (a - floor(a));
  double b1 = DegreesToRadians(216.57 + b);
  a = 91.56766028 * t;
  b = 360 * (a - floor(a));
  double c1 = DegreesToRadians(312.69 + b);
  a = 1236.853095 * t;
  b = 360 * (a - floor(a));
  double d1 = DegreesToRadians(350.74 - 0.00144 * t2 + b);
  double e1 = DegreesToRadians(231.19 + 20.2 * t);
  a = 183.1353208 * t;
  b = 360 * (a - floor(a));
  double h1 = DegreesToRadians(353.4 + b);

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
double TrueAnomaly(double am, double ec) {
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
double EccentricAnomaly(double am, double ec) {
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
double Refract(double y2, ECoordinateType sw, double pr, double tr) {
  double y = DegreesToRadians(y2);

  double d = (sw == ECoordinateType::Actual) ? -1.0 : 1.0;

  if (d == -1) {
    double y3 = y;
    double y1 = y;
    double r1 = 0.0;

    while (1 == 1) {
      double yNew = y1 + r1;
      double rfNew = RefractL3035(pr, tr, yNew, d);

      if (y < -0.087)
        return 0;

      double r2 = rfNew;

      if ((r2 == 0) || (std::abs(r2 - r1) < 0.000001)) {
        double qNew = y3;

        return WToDegrees(qNew + rfNew);
      }

      r1 = r2;
    }
  }

  double rf = RefractL3035(pr, tr, y, d);

  if (y < -0.087)
    return 0;

  double q = y;

  return WToDegrees(q + rf);
}

/**
 * \brief Helper function for Refract
 */
double RefractL3035(double pr, double tr, double y, double d) {
  if (y < 0.2617994) {
    if (y < -0.087)
      return 0;

    double yd = WToDegrees(y);
    double a = ((0.00002 * yd + 0.0196) * yd + 0.1594) * pr;
    double b = (273.0 + tr) * ((0.0845 * yd + 0.505) * yd + 1);

    return DegreesToRadians(-(a / b) * d);
  }

  return -d * 0.00007888888 * pr / ((273.0 + tr) * tan(y));
}

/**
 * \brief Calculate corrected hour angle in decimal hours
 *
 * Original macro name: ParallaxHA
 */
double ParallaxHa(double hh, double hm, double hs, double dd, double dm,
                  double ds, ECoordinateType sw, double gp, double ht,
                  double hp) {
  double a = DegreesToRadians(gp);
  double c1 = cos(a);
  double s1 = sin(a);

  double u = atan(0.996647 * s1 / c1);
  double c2 = cos(u);
  double s2 = sin(u);
  double b = ht / 6378160;

  double rs = (0.996647 * s2) + (b * s1);

  double rc = c2 + (b * c1);
  double tp = 6.283185308;

  double rp = 1.0 / sin(DegreesToRadians(hp));

  double x = DegreesToRadians(DegreeHoursToDecimalDegrees(HmsToDh(hh, hm, hs)));
  double x1 = x;
  double y =
      DegreesToRadians(DegreesMinutesSecondsToDecimalDegrees(dd, dm, ds));
  double y1 = y;

  double d = (sw == ECoordinateType::Actual) ? 1.0 : -1.0;

  if (d == 1) {
    std::tuple<double, double> result = ParallaxHaL2870(x, y, rc, rp, rs, tp);

    return DecimalDegreesToDegreeHours(WToDegrees(std::get<0>(result)));
  }

  double p1 = 0.0;
  double q1 = 0.0;
  double xLoop = x;
  double yLoop = y;

  while (1 == 1) {
    std::tuple<double, double> result =
        ParallaxHaL2870(xLoop, yLoop, rc, rp, rs, tp);

    double p2 = std::get<0>(result) - xLoop;
    double q2 = std::get<1>(result) - yLoop;

    double aa = std::abs(p2 - p1);
    double bb = std::abs(q2 - q1);

    if ((aa < 0.000001) && (bb < 0.000001)) {
      double p = x1 - p2;

      return DecimalDegreesToDegreeHours(WToDegrees(p));
    }

    xLoop = x1 - p2;
    yLoop = y1 - q2;
    p1 = p2;
    q1 = q2;
  }
}

/**
 * \brief Helper function for parallax_ha
 *
 * @return tuple<double p, double q>
 */
std::tuple<double, double> ParallaxHaL2870(double x, double y, double rc,
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
double ParallaxDec(double hh, double hm, double hs, double dd, double dm,
                   double ds, ECoordinateType sw, double gp, double ht,
                   double hp) {
  double a = DegreesToRadians(gp);
  double c1 = cos(a);
  double s1 = sin(a);

  double u = atan(0.996647 * s1 / c1);

  double c2 = cos(u);
  double s2 = sin(u);
  double b = ht / 6378160;
  double rs = (0.996647 * s2) + (b * s1);

  double rc = c2 + (b * c1);
  double tp = 6.283185308;

  double rp = 1.0 / sin(DegreesToRadians(hp));

  double x = DegreesToRadians(DegreeHoursToDecimalDegrees(HmsToDh(hh, hm, hs)));
  double x1 = x;

  double y =
      DegreesToRadians(DegreesMinutesSecondsToDecimalDegrees(dd, dm, ds));
  double y1 = y;

  double d = (sw == ECoordinateType::Actual) ? 1.0 : -1.0;

  if (d == 1) {
    std::tuple<double, double> result = ParallaxDecL2870(x, y, rc, rp, rs, tp);

    return WToDegrees(std::get<1>(result));
  }

  double p1 = 0.0;
  double q1 = 0.0;

  double xLoop = x;
  double yLoop = y;

  while (1 == 1) {
    std::tuple<double, double> result =
        ParallaxDecL2870(xLoop, yLoop, rc, rp, rs, tp);
    double p2 = std::get<0>(result) - xLoop;
    double q2 = std::get<1>(result) - yLoop;
    double aa = std::abs(p2 - p1);

    if ((aa < 0.000001) && (b < 0.000001)) {
      double q = y1 - q2;

      return WToDegrees(q);
    }
    xLoop = x1 - p2;
    yLoop = y1 - q2;
    p1 = p2;
    q1 = q2;
  }
}

/**
 * \brief Helper function for parallax_dec
 *
 * @return tuple<double p, double q>
 */
std::tuple<double, double> ParallaxDecL2870(double x, double y, double rc,
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
double MoonLongitude(double lh, double lm, double ls, int ds, int zc, double dy,
                     int mn, int yr) {
  double ut = LocalCivilTimeToUniversalTime(lh, lm, ls, ds, zc, dy, mn, yr);
  double gd = LocalCivilTimeGreenwichDay(lh, lm, ls, ds, zc, dy, mn, yr);
  int gm = LocalCivilTimeGreenwichMonth(lh, lm, ls, ds, zc, dy, mn, yr);
  int gy = LocalCivilTimeGreenwichYear(lh, lm, ls, ds, zc, dy, mn, yr);
  double t =
      ((CivilDateToJulianDate(gd, gm, gy) - 2415020) / 36525) + (ut / 876600);
  double t2 = t * t;

  double m1 = 27.32158213;
  double m2 = 365.2596407;
  double m3 = 27.55455094;
  double m4 = 29.53058868;
  double m5 = 27.21222039;
  double m6 = 6798.363307;
  double q = CivilDateToJulianDate(gd, gm, gy) - 2415020 + (ut / 24);
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
  double a = DegreesToRadians(51.2 + 20.2 * t);
  double s1 = sin(a);
  double s2 = sin(DegreesToRadians(na));
  double b = 346.56 + (132.87 - 0.0091731 * t) * t;
  double s3 = 0.003964 * sin(DegreesToRadians(b));
  double c = DegreesToRadians(na + 275.05 - 2.3 * t);
  double s4 = sin(c);
  ml = ml + 0.000233 * s1 + s3 + 0.001964 * s2;
  ms = ms - 0.001778 * s1;
  md = md + 0.000817 * s1 + s3 + 0.002541 * s2;
  mf = mf + s3 - 0.024691 * s2 - 0.004328 * s4;
  me1 = me1 + 0.002011 * s1 + s3 + 0.001964 * s2;
  double e = 1.0 - (0.002495 + 0.00000752 * t) * t;
  double e2 = e * e;
  ml = DegreesToRadians(ml);
  ms = DegreesToRadians(ms);
  me1 = DegreesToRadians(me1);
  mf = DegreesToRadians(mf);
  md = DegreesToRadians(md);

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

  double mm = Unwind(ml + DegreesToRadians(l));

  return WToDegrees(mm);
}

/**
 * \brief Calculate geocentric ecliptic latitude for the Moon
 *
 * Original macro name: MoonLat
 */
double MoonLatitude(double lh, double lm, double ls, int ds, int zc, double dy,
                    int mn, int yr) {
  double ut = LocalCivilTimeToUniversalTime(lh, lm, ls, ds, zc, dy, mn, yr);
  double gd = LocalCivilTimeGreenwichDay(lh, lm, ls, ds, zc, dy, mn, yr);
  int gm = LocalCivilTimeGreenwichMonth(lh, lm, ls, ds, zc, dy, mn, yr);
  int gy = LocalCivilTimeGreenwichYear(lh, lm, ls, ds, zc, dy, mn, yr);
  double t =
      ((CivilDateToJulianDate(gd, gm, gy) - 2415020) / 36525) + (ut / 876600);
  double t2 = t * t;

  double m1 = 27.32158213;
  double m2 = 365.2596407;
  double m3 = 27.55455094;
  double m4 = 29.53058868;
  double m5 = 27.21222039;
  double m6 = 6798.363307;
  double q = CivilDateToJulianDate(gd, gm, gy) - 2415020 + (ut / 24);
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
  double a = DegreesToRadians(51.2 + 20.2 * t);
  double s1 = sin(a);
  double s2 = sin(DegreesToRadians(na));
  double b = 346.56 + (132.87 - 0.0091731 * t) * t;
  double s3 = 0.003964 * sin(DegreesToRadians(b));
  double c = DegreesToRadians(na + 275.05 - 2.3 * t);
  double s4 = sin(c);
  ml = ml + 0.000233 * s1 + s3 + 0.001964 * s2;
  ms = ms - 0.001778 * s1;
  md = md + 0.000817 * s1 + s3 + 0.002541 * s2;
  mf = mf + s3 - 0.024691 * s2 - 0.004328 * s4;
  me1 = me1 + 0.002011 * s1 + s3 + 0.001964 * s2;
  double e = 1.0 - (0.002495 + 0.00000752 * t) * t;
  double e2 = e * e;
  ms = DegreesToRadians(ms);
  na = DegreesToRadians(na);
  me1 = DegreesToRadians(me1);
  mf = DegreesToRadians(mf);
  md = DegreesToRadians(md);

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
  double bm = DegreesToRadians(g) * (1.0 - w1 - w2);

  return WToDegrees(bm);
}

/**
 * Calculate distance from the Earth to the Moon (km)
 *
 * Original macro name: MoonDist
 */
double MoonDist(double lh, double lm, double ls, int ds, int zc, double dy,
                int mn, int yr) {
  double hp =
      DegreesToRadians(MoonHorizontalParallax(lh, lm, ls, ds, zc, dy, mn, yr));
  double r = 6378.14 / sin(hp);

  return r;
}

/**
 * Calculate the Moon's angular diameter (degrees)
 *
 * Original macro name: MoonSize
 */
double MoonSize(double lh, double lm, double ls, int ds, int zc, double dy,
                int mn, int yr) {
  double hp =
      DegreesToRadians(MoonHorizontalParallax(lh, lm, ls, ds, zc, dy, mn, yr));
  double r = 6378.14 / sin(hp);
  double th = 384401.0 * 0.5181 / r;

  return th;
}

/**
 * \brief Calculate horizontal parallax for the Moon
 *
 * Original macro name: MoonHP
 */
double MoonHorizontalParallax(double lh, double lm, double ls, int ds, int zc,
                              double dy, int mn, int yr) {
  double ut = LocalCivilTimeToUniversalTime(lh, lm, ls, ds, zc, dy, mn, yr);
  double gd = LocalCivilTimeGreenwichDay(lh, lm, ls, ds, zc, dy, mn, yr);
  int gm = LocalCivilTimeGreenwichMonth(lh, lm, ls, ds, zc, dy, mn, yr);
  int gy = LocalCivilTimeGreenwichYear(lh, lm, ls, ds, zc, dy, mn, yr);
  double t =
      ((CivilDateToJulianDate(gd, gm, gy) - 2415020) / 36525) + (ut / 876600);
  double t2 = t * t;

  double m1 = 27.32158213;
  double m2 = 365.2596407;
  double m3 = 27.55455094;
  double m4 = 29.53058868;
  double m5 = 27.21222039;
  double m6 = 6798.363307;
  double q = CivilDateToJulianDate(gd, gm, gy) - 2415020 + (ut / 24);
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
  double a = DegreesToRadians(51.2 + 20.2 * t);
  double s1 = sin(a);
  double s2 = sin(DegreesToRadians(na));
  double b = 346.56 + (132.87 - 0.0091731 * t) * t;
  double s3 = 0.003964 * sin(DegreesToRadians(b));
  double c = DegreesToRadians(na + 275.05 - 2.3 * t);
  double s4 = sin(c);
  ml = ml + 0.000233 * s1 + s3 + 0.001964 * s2;
  ms = ms - 0.001778 * s1;
  md = md + 0.000817 * s1 + s3 + 0.002541 * s2;
  mf = mf + s3 - 0.024691 * s2 - 0.004328 * s4;
  me1 = me1 + 0.002011 * s1 + s3 + 0.001964 * s2;
  double e = 1.0 - (0.002495 + 0.00000752 * t) * t;
  double e2 = e * e;
  ms = DegreesToRadians(ms);
  me1 = DegreesToRadians(me1);
  mf = DegreesToRadians(mf);
  md = DegreesToRadians(md);

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
double Unwind(double w) { return w - 6.283185308 * floor(w / 6.283185308); }

/**
 * Convert angle in degrees to equivalent angle in the range 0 to 360 degrees.
 *
 * Original macro name: UnwindDeg
 */
double UnwindDeg(double w) { return w - 360 * floor(w / 360); }

/**
 * \brief Mean ecliptic longitude of the Sun at the epoch
 *
 * Original macro name: SunElong
 */
double SunELong(double gd, int gm, int gy) {
  double t = (CivilDateToJulianDate(gd, gm, gy) - 2415020) / 36525;
  double t2 = t * t;
  double x = 279.6966778 + 36000.76892 * t + 0.0003025 * t2;

  return x - 360 * floor(x / 360);
}

/**
 * \brief Longitude of the Sun at perigee
 *
 * Original macro name: SunPeri
 */
double SunPerigee(double gd, int gm, int gy) {
  double t = (CivilDateToJulianDate(gd, gm, gy) - 2415020) / 36525;
  double t2 = t * t;
  double x = 281.2208444 + 1.719175 * t + 0.000452778 * t2;

  return x - 360 * floor(x / 360);
}

/**
 * \brief Eccentricity of the Sun-Earth orbit
 *
 * Original macro name: SunEcc
 */
double SunEccentricity(double gd, int gm, int gy) {
  double t = (CivilDateToJulianDate(gd, gm, gy) - 2415020) / 36525;
  double t2 = t * t;

  return 0.01675104 - 0.0000418 * t - 0.000000126 * t2;
}

/**
 * \brief Ecliptic - Declination (degrees)
 *
 * Original macro name: ECDec
 */
double EclipticDeclination(double eld, double elm, double els, double bd,
                           double bm, double bs, double gd, int gm, int gy) {
  double a =
      DegreesToRadians(DegreesMinutesSecondsToDecimalDegrees(eld, elm, els));
  double b =
      DegreesToRadians(DegreesMinutesSecondsToDecimalDegrees(bd, bm, bs));
  double c = DegreesToRadians(Obliq(gd, gm, gy));
  double d = sin(b) * cos(c) + cos(b) * sin(c) * sin(a);

  return WToDegrees(asin(d));
}

/**
 * \brief Ecliptic - Right Ascension (degrees)
 *
 * Original macro name: ECRA
 */
double EclipticRightAscension(double eld, double elm, double els, double bd,
                              double bm, double bs, double gd, int gm, int gy) {
  double a =
      DegreesToRadians(DegreesMinutesSecondsToDecimalDegrees(eld, elm, els));
  double b =
      DegreesToRadians(DegreesMinutesSecondsToDecimalDegrees(bd, bm, bs));
  double c = DegreesToRadians(Obliq(gd, gm, gy));
  double d = sin(a) * cos(c) - tan(b) * sin(c);
  double e = cos(a);
  double f = WToDegrees(atan2(d, e));

  return f - 360 * floor(f / 360);
}

/**
 * \brief Calculate Sun's true anomaly, i.e., how much its orbit deviates from a
 * true circle to an ellipse.
 *
 * Original macro name: SunTrueAnomaly
 */
double SunTrueAnomaly(double lch, double lcm, double lcs, int ds, int zc,
                      double ld, int lm, int ly) {
  double aa = LocalCivilTimeGreenwichDay(lch, lcm, lcs, ds, zc, ld, lm, ly);
  int bb = LocalCivilTimeGreenwichMonth(lch, lcm, lcs, ds, zc, ld, lm, ly);
  int cc = LocalCivilTimeGreenwichYear(lch, lcm, lcs, ds, zc, ld, lm, ly);
  double ut = LocalCivilTimeToUniversalTime(lch, lcm, lcs, ds, zc, ld, lm, ly);
  double dj = CivilDateToJulianDate(aa, bb, cc) - 2415020;

  double t = (dj / 36525) + (ut / 876600);
  double t2 = t * t;

  double a = 99.99736042 * t;
  double b = 360 * (a - floor(a));

  double m1 = 358.47583 - (0.00015 + 0.0000033 * t) * t2 + b;
  double ec = 0.01675104 - 0.0000418 * t - 0.000000126 * t2;

  double am = DegreesToRadians(m1);

  return WToDegrees(TrueAnomaly(am, ec));
}

/**
 * \brief Calculate the Sun's mean anomaly.
 *
 * Original macro name: SunMeanAnomaly
 */
double SunMeanAnomaly(double lch, double lcm, double lcs, int ds, int zc,
                      double ld, int lm, int ly) {
  double aa = LocalCivilTimeGreenwichDay(lch, lcm, lcs, ds, zc, ld, lm, ly);
  int bb = LocalCivilTimeGreenwichMonth(lch, lcm, lcs, ds, zc, ld, lm, ly);
  int cc = LocalCivilTimeGreenwichYear(lch, lcm, lcs, ds, zc, ld, lm, ly);
  double ut = LocalCivilTimeToUniversalTime(lch, lcm, lcs, ds, zc, ld, lm, ly);
  double dj = CivilDateToJulianDate(aa, bb, cc) - 2415020;
  double t = (dj / 36525) + (ut / 876600);
  double t2 = t * t;
  double a = 100.0021359 * t;
  double b = 360 * (a - floor(a));
  double m1 = 358.47583 - (0.00015 + 0.0000033 * t) * t2 + b;
  double am = Unwind(DegreesToRadians(m1));

  return am;
}

/**
 * \brief Calculate local civil time of sunrise.
 *
 * Original macro name: SunriseLCT
 */
double SunriseLocalCivilTime(double ld, int lm, int ly, int ds, int zc,
                             double gl, double gp) {
  double di = 0.8333333;
  double gd = LocalCivilTimeGreenwichDay(12, 0, 0, ds, zc, ld, lm, ly);
  int gm = LocalCivilTimeGreenwichMonth(12, 0, 0, ds, zc, ld, lm, ly);
  int gy = LocalCivilTimeGreenwichYear(12, 0, 0, ds, zc, ld, lm, ly);
  double sr = SunLong(12, 0, 0, ds, zc, ld, lm, ly);

  std::tuple<double, double, double, double, ERiseSetStatus> result1 =
      SunriseLocalCivilTimeL3710(gd, gm, gy, sr, di, gp);

  double xx;
  if (std::get<4>(result1) != ERiseSetStatus::Ok) {
    xx = -99.0;
  } else {
    double x = LocalSiderealTimeToGreenwichSiderealTime(std::get<3>(result1), 0,
                                                        0, gl);
    double ut = GreenwichSiderealTimeToUniversalTime(x, 0, 0, gd, gm, gy);

    if (EGstUt(x, 0, 0, gd, gm, gy) != EWarningFlags::Ok) {
      xx = -99.0;
    } else {
      sr = SunLong(ut, 0, 0, 0, 0, gd, gm, gy);
      std::tuple<double, double, double, double, ERiseSetStatus> result2 =
          SunriseLocalCivilTimeL3710(gd, gm, gy, sr, di, gp);

      if (std::get<4>(result2) != ERiseSetStatus::Ok) {
        xx = -99.0;
      } else {
        x = LocalSiderealTimeToGreenwichSiderealTime(std::get<3>(result2), 0, 0,
                                                     gl);
        ut = GreenwichSiderealTimeToUniversalTime(x, 0, 0, gd, gm, gy);
        xx = UniversalTimeToLocalCivilTime(ut, 0, 0, ds, zc, gd, gm, gy);
      }
    }
  }

  return xx;
}

/**
 * \brief Calculate local civil time of sunset.
 *
 * Original macro name: SunsetLCT
 */
double SunsetLocalCivilTime(double ld, int lm, int ly, int ds, int zc,
                            double gl, double gp) {
  double di = 0.8333333;
  double gd = LocalCivilTimeGreenwichDay(12, 0, 0, ds, zc, ld, lm, ly);
  int gm = LocalCivilTimeGreenwichMonth(12, 0, 0, ds, zc, ld, lm, ly);
  int gy = LocalCivilTimeGreenwichYear(12, 0, 0, ds, zc, ld, lm, ly);
  double sr = SunLong(12, 0, 0, ds, zc, ld, lm, ly);

  std::tuple<double, double, double, double, ERiseSetStatus> result1 =
      SunsetLocalCivilTimeL3710(gd, gm, gy, sr, di, gp);

  double xx;
  if (std::get<4>(result1) != ERiseSetStatus::Ok) {
    xx = -99.0;
  } else {
    double x = LocalSiderealTimeToGreenwichSiderealTime(std::get<3>(result1), 0,
                                                        0, gl);
    double ut = GreenwichSiderealTimeToUniversalTime(x, 0, 0, gd, gm, gy);

    if (EGstUt(x, 0, 0, gd, gm, gy) != EWarningFlags::Ok) {
      xx = -99.0;
    } else {
      sr = SunLong(ut, 0, 0, 0, 0, gd, gm, gy);
      std::tuple<double, double, double, double, ERiseSetStatus> result2 =
          SunsetLocalCivilTimeL3710(gd, gm, gy, sr, di, gp);

      if (std::get<4>(result2) != ERiseSetStatus::Ok) {
        xx = -99;
      } else {
        x = LocalSiderealTimeToGreenwichSiderealTime(std::get<3>(result2), 0, 0,
                                                     gl);
        ut = GreenwichSiderealTimeToUniversalTime(x, 0, 0, gd, gm, gy);
        xx = UniversalTimeToLocalCivilTime(ut, 0, 0, ds, zc, gd, gm, gy);
      }
    }
  }

  return xx;
}

/**
 * \brief Helper function for sunrise_lct()
 *
 * @return tuple<double a, double x, double y, double la,
 * rise_set_status s>
 */
std::tuple<double, double, double, double, ERiseSetStatus>
SunriseLocalCivilTimeL3710(double gd, int gm, int gy, double sr, double di,
                           double gp) {
  double a = sr + NutatLong(gd, gm, gy) - 0.005694;
  double x = EclipticRightAscension(a, 0, 0, 0, 0, 0, gd, gm, gy);
  double y = EclipticDeclination(a, 0, 0, 0, 0, 0, gd, gm, gy);
  double la = RiseSetLocalSiderealTimeRise(DecimalDegreesToDegreeHours(x), 0, 0,
                                           y, 0, 0, di, gp);
  ERiseSetStatus s =
      ERiseSet(DecimalDegreesToDegreeHours(x), 0.0, 0.0, y, 0.0, 0.0, di, gp);

  return std::tuple<double, double, double, double, ERiseSetStatus>{a, x, y, la,
                                                                    s};
}

/**
 * \brief Helper function for sunset_lct().
 *
 * @return tuple<double a, double x, double y, double la,
 * rise_set_status s>
 */
std::tuple<double, double, double, double, ERiseSetStatus>
SunsetLocalCivilTimeL3710(double gd, int gm, int gy, double sr, double di,
                          double gp) {
  double a = sr + NutatLong(gd, gm, gy) - 0.005694;
  double x = EclipticRightAscension(a, 0.0, 0.0, 0.0, 0.0, 0.0, gd, gm, gy);
  double y = EclipticDeclination(a, 0.0, 0.0, 0.0, 0.0, 0.0, gd, gm, gy);
  double la = RiseSetLocalSiderealTimeSet(DecimalDegreesToDegreeHours(x), 0, 0,
                                          y, 0, 0, di, gp);
  ERiseSetStatus s =
      ERiseSet(DecimalDegreesToDegreeHours(x), 0, 0, y, 0, 0, di, gp);

  return std::tuple<double, double, double, double, ERiseSetStatus>{a, x, y, la,
                                                                    s};
}

/**
 * \brief Local sidereal time of rise, in hours.
 *
 * Original macro name: RSLSTR
 */
double RiseSetLocalSiderealTimeRise(double rah, double ram, double ras,
                                    double dd, double dm, double ds, double vd,
                                    double g) {
  double a = HmsToDh(rah, ram, ras);
  double b = DegreesToRadians(DegreeHoursToDecimalDegrees(a));
  double c =
      DegreesToRadians(DegreesMinutesSecondsToDecimalDegrees(dd, dm, ds));
  double d = DegreesToRadians(vd);
  double e = DegreesToRadians(g);
  double f = -(sin(d) + sin(e) * sin(c)) / (cos(e) * cos(c));
  double h = (std::abs(f) < 1) ? acos(f) : 0;
  double i = DecimalDegreesToDegreeHours(WToDegrees(b - h));

  return i - 24 * floor(i / 24);
}

/**
 * \brief Local sidereal time of setting, in hours.
 *
 * Original macro name: RSLSTS
 */
double RiseSetLocalSiderealTimeSet(double rah, double ram, double ras,
                                   double dd, double dm, double ds, double vd,
                                   double g) {
  double a = HmsToDh(rah, ram, ras);
  double b = DegreesToRadians(DegreeHoursToDecimalDegrees(a));
  double c =
      DegreesToRadians(DegreesMinutesSecondsToDecimalDegrees(dd, dm, ds));
  double d = DegreesToRadians(vd);
  double e = DegreesToRadians(g);
  double f = -(sin(d) + sin(e) * sin(c)) / (cos(e) * cos(c));
  double h = (std::abs(f) < 1) ? acos(f) : 0;
  double i = DecimalDegreesToDegreeHours(WToDegrees(b + h));

  return i - 24 * floor(i / 24);
}

/**
 * \brief Rise/Set status
 */
ERiseSetStatus ERiseSet(double rah, double ram, double ras, double dd,
                        double dm, double ds, double vd, double g) {
  double a = HmsToDh(rah, ram, ras);
  double c =
      DegreesToRadians(DegreesMinutesSecondsToDecimalDegrees(dd, dm, ds));
  double d = DegreesToRadians(vd);
  double e = DegreesToRadians(g);
  double f = -(sin(d) + sin(e) * sin(c)) / (cos(e) * cos(c));

  ERiseSetStatus return_value = ERiseSetStatus::Ok;
  if (f >= 1)
    return_value = ERiseSetStatus::NeverRises;
  if (f <= -1)
    return_value = ERiseSetStatus::Circumpolar;

  return return_value;
}

/**
 * \brief Status of conversion of Greenwich Sidereal Time to Universal Time.
 *
 * Original macro name: eGSTUT
 */
EWarningFlags EGstUt(double gsh, double gsm, double gss, double gd, int gm,
                     int gy) {
  double a = CivilDateToJulianDate(gd, gm, gy);
  double b = a - 2451545;
  double c = b / 36525;
  double d = 6.697374558 + (2400.051336 * c) + (0.000025862 * c * c);
  double e = d - (24 * floor(d / 24));
  double f = HmsToDh(gsh, gsm, gss);
  double g = f - e;
  double h = g - (24 * floor(g / 24));

  return ((h * 0.9972695663) < (4.0 / 60.0)) ? EWarningFlags::Warning
                                             : EWarningFlags::Ok;
}

/**
 * \brief Sunrise/Sunset calculation status.
 *
 * Original macro name: eSunRS
 */
ERiseSetStatus ESunRiseSetCalcStatus(double ld, int lm, int ly, int ds, int zc,
                                     double gl, double gp) {
  double di = 0.8333333;
  double gd = LocalCivilTimeGreenwichDay(12, 0, 0, ds, zc, ld, lm, ly);
  int gm = LocalCivilTimeGreenwichMonth(12, 0, 0, ds, zc, ld, lm, ly);
  int gy = LocalCivilTimeGreenwichYear(12, 0, 0, ds, zc, ld, lm, ly);
  double sr = SunLong(12, 0, 0, ds, zc, ld, lm, ly);

  std::tuple<double, double, double, double, ERiseSetStatus> result1 =
      ESunRiseSetCalcStatusL3710(gd, gm, gy, sr, di, gp);

  if (std::get<4>(result1) != ERiseSetStatus::Ok) {
    return std::get<4>(result1);
  } else {
    double x = LocalSiderealTimeToGreenwichSiderealTime(std::get<3>(result1), 0,
                                                        0, gl);
    double ut = GreenwichSiderealTimeToUniversalTime(x, 0, 0, gd, gm, gy);
    sr = SunLong(ut, 0, 0, 0, 0, gd, gm, gy);
    std::tuple<double, double, double, double, ERiseSetStatus> result2 =
        ESunRiseSetCalcStatusL3710(gd, gm, gy, sr, di, gp);
    if (std::get<4>(result2) != ERiseSetStatus::Ok) {
      return std::get<4>(result2);
    } else {
      x = LocalSiderealTimeToGreenwichSiderealTime(std::get<3>(result2), 0, 0,
                                                   gl);

      if (EGstUt(x, 0, 0, gd, gm, gy) != EWarningFlags::Ok)

        return ERiseSetStatus::GstToUtConversionWarning;
    }

    return std::get<4>(result2);
  }
}

/// <summary>
/// Helper function for e_sun_rs()
/// </summary>
std::tuple<double, double, double, double, ERiseSetStatus>
ESunRiseSetCalcStatusL3710(double gd, int gm, int gy, double sr, double di,
                           double gp) {
  double a = sr + NutatLong(gd, gm, gy) - 0.005694;
  double x = EclipticRightAscension(a, 0, 0, 0, 0, 0, gd, gm, gy);
  double y = EclipticDeclination(a, 0, 0, 0, 0, 0, gd, gm, gy);
  double la = RiseSetLocalSiderealTimeRise(DecimalDegreesToDegreeHours(x), 0, 0,
                                           y, 0, 0, di, gp);
  ERiseSetStatus s =
      ERiseSet(DecimalDegreesToDegreeHours(x), 0, 0, y, 0, 0, di, gp);

  return std::tuple<double, double, double, double, ERiseSetStatus>{a, x, y, la,
                                                                    s};
}

/**
 * \brief Calculate azimuth of sunrise.
 *
 * Original macro name: SunriseAz
 */
double SunriseAzimuth(double ld, int lm, int ly, int ds, int zc, double gl,
                      double gp) {
  double di = 0.8333333;
  double gd = LocalCivilTimeGreenwichDay(12, 0, 0, ds, zc, ld, lm, ly);
  int gm = LocalCivilTimeGreenwichMonth(12, 0, 0, ds, zc, ld, lm, ly);
  int gy = LocalCivilTimeGreenwichYear(12, 0, 0, ds, zc, ld, lm, ly);
  double sr = SunLong(12, 0, 0, ds, zc, ld, lm, ly);

  std::tuple<double, double, double, double, ERiseSetStatus> result1 =
      SunriseAzimuthL3710(gd, gm, gy, sr, di, gp);

  if (std::get<4>(result1) != ERiseSetStatus::Ok) {
    return -99.0;
  }

  double x =
      LocalSiderealTimeToGreenwichSiderealTime(std::get<3>(result1), 0, 0, gl);
  double ut = GreenwichSiderealTimeToUniversalTime(x, 0, 0, gd, gm, gy);

  if (EGstUt(x, 0, 0, gd, gm, gy) != EWarningFlags::Ok) {
    return -99.0;
  }

  sr = SunLong(ut, 0, 0, 0, 0, gd, gm, gy);
  std::tuple<double, double, double, double, ERiseSetStatus> result2 =
      SunriseAzimuthL3710(gd, gm, gy, sr, di, gp);

  if (std::get<4>(result2) != ERiseSetStatus::Ok) {
    return -99.0;
  }

  return RiseSetAzimuthRise(DecimalDegreesToDegreeHours(x), 0, 0,
                            std::get<2>(result2), 0.0, 0.0, di, gp);
}

/**
 * \brief Helper function for sunrise_az()
 */
std::tuple<double, double, double, double, ERiseSetStatus>
SunriseAzimuthL3710(double gd, int gm, int gy, double sr, double di,
                    double gp) {
  double a = sr + NutatLong(gd, gm, gy) - 0.005694;
  double x = EclipticRightAscension(a, 0, 0, 0, 0, 0, gd, gm, gy);
  double y = EclipticDeclination(a, 0, 0, 0, 0, 0, gd, gm, gy);
  double la = RiseSetLocalSiderealTimeRise(DecimalDegreesToDegreeHours(x), 0, 0,
                                           y, 0, 0, di, gp);
  ERiseSetStatus s =
      ERiseSet(DecimalDegreesToDegreeHours(x), 0, 0, y, 0, 0, di, gp);

  return std::tuple<double, double, double, double, ERiseSetStatus>{a, x, y, la,
                                                                    s};
}

/**
 * \brief Calculate azimuth of sunset.
 *
 * Original macro name: SunsetAz
 */
double SunsetAzimuth(double ld, int lm, int ly, int ds, int zc, double gl,
                     double gp) {
  double di = 0.8333333;
  double gd = LocalCivilTimeGreenwichDay(12, 0, 0, ds, zc, ld, lm, ly);
  int gm = LocalCivilTimeGreenwichMonth(12, 0, 0, ds, zc, ld, lm, ly);
  int gy = LocalCivilTimeGreenwichYear(12, 0, 0, ds, zc, ld, lm, ly);
  double sr = SunLong(12, 0, 0, ds, zc, ld, lm, ly);

  std::tuple<double, double, double, double, ERiseSetStatus> result1 =
      SunsetAzimuthL3710(gd, gm, gy, sr, di, gp);

  if (std::get<4>(result1) != ERiseSetStatus::Ok) {
    return -99.0;
  }

  double x =
      LocalSiderealTimeToGreenwichSiderealTime(std::get<3>(result1), 0, 0, gl);
  double ut = GreenwichSiderealTimeToUniversalTime(x, 0, 0, gd, gm, gy);

  if (EGstUt(x, 0, 0, gd, gm, gy) != EWarningFlags::Ok) {
    return -99.0;
  }

  sr = SunLong(ut, 0, 0, 0, 0, gd, gm, gy);

  std::tuple<double, double, double, double, ERiseSetStatus> result2 =
      SunsetAzimuthL3710(gd, gm, gy, sr, di, gp);

  if (std::get<4>(result2) != ERiseSetStatus::Ok) {
    return -99.0;
  }

  return RiseSetAzimuthSet(DecimalDegreesToDegreeHours(x), 0, 0,
                           std::get<2>(result2), 0, 0, di, gp);
}

/**
 * \brief Helper function for sunset_az()
 *
 * @return tuple<double a, double x, double y, double la,
 * RiseSetStatus s>
 */
std::tuple<double, double, double, double, ERiseSetStatus>
SunsetAzimuthL3710(double gd, int gm, int gy, double sr, double di, double gp) {
  double a = sr + NutatLong(gd, gm, gy) - 0.005694;
  double x = EclipticRightAscension(a, 0, 0, 0, 0, 0, gd, gm, gy);
  double y = EclipticDeclination(a, 0, 0, 0, 0, 0, gd, gm, gy);
  double la = RiseSetLocalSiderealTimeSet(DecimalDegreesToDegreeHours(x), 0, 0,
                                          y, 0, 0, di, gp);
  ERiseSetStatus s =
      ERiseSet(DecimalDegreesToDegreeHours(x), 0, 0, y, 0, 0, di, gp);

  return std::tuple<double, double, double, double, ERiseSetStatus>{a, x, y, la,
                                                                    s};
}

/**
 * \brief Azimuth of rising, in degrees.
 *
 * Original macro name: RSAZR
 */
double RiseSetAzimuthRise(double rah, double ram, double ras, double dd,
                          double dm, double ds, double vd, double g) {
  double a = HmsToDh(rah, ram, ras);
  double c =
      DegreesToRadians(DegreesMinutesSecondsToDecimalDegrees(dd, dm, ds));
  double d = DegreesToRadians(vd);
  double e = DegreesToRadians(g);
  double f = (sin(c) + sin(d) * sin(e)) / (cos(d) * cos(e));
  double h = (ERiseSet(rah, ram, ras, dd, dm, ds, vd, g) == ERiseSetStatus::Ok)
                 ? acos(f)
                 : 0;
  double i = WToDegrees(h);

  return i - 360 * floor(i / 360);
}

/**
 * \brief Azimuth of setting, in degrees.
 *
 * Original macro name: RSAZS
 */
double RiseSetAzimuthSet(double rah, double ram, double ras, double dd,
                         double dm, double ds, double vd, double g) {
  double a = HmsToDh(rah, ram, ras);
  double c =
      DegreesToRadians(DegreesMinutesSecondsToDecimalDegrees(dd, dm, ds));
  double d = DegreesToRadians(vd);
  double e = DegreesToRadians(g);
  double f = (sin(c) + sin(d) * sin(e)) / (cos(d) * cos(e));
  double h = (ERiseSet(rah, ram, ras, dd, dm, ds, vd, g) == ERiseSetStatus::Ok)
                 ? acos(f)
                 : 0;
  double i = 360 - WToDegrees(h);

  return i - 360 * floor(i / 360);
}

/**
 * \brief Calculate morning twilight start, in local time.
 *
 * Original macro name: TwilightAMLCT
 */
double TwilightAMLocalCivilTime(double ld, int lm, int ly, int ds, int zc,
                                double gl, double gp, ETwilightType tt) {
  double di = (double)tt;

  double gd = LocalCivilTimeGreenwichDay(12, 0, 0, ds, zc, ld, lm, ly);
  int gm = LocalCivilTimeGreenwichMonth(12, 0, 0, ds, zc, ld, lm, ly);
  int gy = LocalCivilTimeGreenwichYear(12, 0, 0, ds, zc, ld, lm, ly);
  double sr = SunLong(12, 0, 0, ds, zc, ld, lm, ly);

  std::tuple<double, double, double, double, ERiseSetStatus> result1 =
      TwilightAMLocalCivilTime_L3710(gd, gm, gy, sr, di, gp);

  if (std::get<4>(result1) != ERiseSetStatus::Ok) {
    return -99.0;
  }

  double x =
      LocalSiderealTimeToGreenwichSiderealTime(std::get<3>(result1), 0, 0, gl);
  double ut = GreenwichSiderealTimeToUniversalTime(x, 0, 0, gd, gm, gy);

  if (EGstUt(x, 0, 0, gd, gm, gy) != EWarningFlags::Ok) {
    return -99.0;
  }

  sr = SunLong(ut, 0, 0, 0, 0, gd, gm, gy);

  std::tuple<double, double, double, double, ERiseSetStatus> result2 =
      TwilightAMLocalCivilTime_L3710(gd, gm, gy, sr, di, gp);

  if (std::get<4>(result2) != ERiseSetStatus::Ok) {
    return -99.0;
  }

  x = LocalSiderealTimeToGreenwichSiderealTime(std::get<3>(result2), 0, 0, gl);
  ut = GreenwichSiderealTimeToUniversalTime(x, 0, 0, gd, gm, gy);

  double xx = UniversalTimeToLocalCivilTime(ut, 0, 0, ds, zc, gd, gm, gy);

  return xx;
}

/**
 * \brief Helper function for twilight_am_lct()
 *
 * @return tuple <double a, double x, double y, double la,
 * RiseSetStatus s>
 */
std::tuple<double, double, double, double, ERiseSetStatus>
TwilightAMLocalCivilTime_L3710(double gd, int gm, int gy, double sr, double di,
                               double gp) {
  double a = sr + NutatLong(gd, gm, gy) - 0.005694;
  double x = EclipticRightAscension(a, 0, 0, 0, 0, 0, gd, gm, gy);
  double y = EclipticDeclination(a, 0, 0, 0, 0, 0, gd, gm, gy);
  double la = RiseSetLocalSiderealTimeRise(DecimalDegreesToDegreeHours(x), 0, 0,
                                           y, 0, 0, di, gp);
  ERiseSetStatus s =
      ERiseSet(DecimalDegreesToDegreeHours(x), 0, 0, y, 0, 0, di, gp);

  return std::tuple<double, double, double, double, ERiseSetStatus>{a, x, y, la,
                                                                    s};
}

/**
 * \brief Calculate evening twilight end, in local time.
 *
 * Original macro name: TwilightPMLCT
 */
double TwilightPMLocalCivilTime(double ld, int lm, int ly, int ds, int zc,
                                double gl, double gp, ETwilightType tt) {
  double di = (double)tt;

  double gd = LocalCivilTimeGreenwichDay(12, 0, 0, ds, zc, ld, lm, ly);
  int gm = LocalCivilTimeGreenwichMonth(12, 0, 0, ds, zc, ld, lm, ly);
  int gy = LocalCivilTimeGreenwichYear(12, 0, 0, ds, zc, ld, lm, ly);
  double sr = SunLong(12, 0, 0, ds, zc, ld, lm, ly);

  std::tuple<double, double, double, double, ERiseSetStatus> result1 =
      TwilightPMLocalCivilTime_L3710(gd, gm, gy, sr, di, gp);

  if (std::get<4>(result1) != ERiseSetStatus::Ok) {
    return 0.0;
  }

  double x =
      LocalSiderealTimeToGreenwichSiderealTime(std::get<3>(result1), 0, 0, gl);
  double ut = GreenwichSiderealTimeToUniversalTime(x, 0, 0, gd, gm, gy);

  if (EGstUt(x, 0, 0, gd, gm, gy) != EWarningFlags::Ok) {
    return 0.0;
  }

  sr = SunLong(ut, 0, 0, 0, 0, gd, gm, gy);

  std::tuple<double, double, double, double, ERiseSetStatus> result2 =
      TwilightPMLocalCivilTime_L3710(gd, gm, gy, sr, di, gp);

  if (std::get<4>(result2) != ERiseSetStatus::Ok) {
    return 0.0;
  }

  x = LocalSiderealTimeToGreenwichSiderealTime(std::get<3>(result2), 0, 0, gl);
  ut = GreenwichSiderealTimeToUniversalTime(x, 0, 0, gd, gm, gy);

  return UniversalTimeToLocalCivilTime(ut, 0, 0, ds, zc, gd, gm, gy);
}

/**
 * \brief Helper function for twilight_pm_lct()
 *
 * @return tuple <double a, double x, double y, double la,
 * RiseSetStatus s>
 */
std::tuple<double, double, double, double, ERiseSetStatus>
TwilightPMLocalCivilTime_L3710(double gd, int gm, int gy, double sr, double di,
                               double gp) {
  double a = sr + NutatLong(gd, gm, gy) - 0.005694;
  double x = EclipticRightAscension(a, 0, 0, 0, 0, 0, gd, gm, gy);
  double y = EclipticDeclination(a, 0, 0, 0, 0, 0, gd, gm, gy);
  double la = RiseSetLocalSiderealTimeSet(DecimalDegreesToDegreeHours(x), 0, 0,
                                          y, 0, 0, di, gp);
  ERiseSetStatus s =
      ERiseSet(DecimalDegreesToDegreeHours(x), 0, 0, y, 0, 0, di, gp);

  return std::tuple<double, double, double, double, ERiseSetStatus>{a, x, y, la,
                                                                    s};
}

/**
 * \brief Twilight calculation status.
 *
 * Original macro name: eTwilight
 */
ETwilightStatus ETwilight(double ld, int lm, int ly, int ds, int zc, double gl,
                          double gp, ETwilightType tt) {
  double di = (double)tt;

  double gd = LocalCivilTimeGreenwichDay(12, 0, 0, ds, zc, ld, lm, ly);
  int gm = LocalCivilTimeGreenwichMonth(12, 0, 0, ds, zc, ld, lm, ly);
  int gy = LocalCivilTimeGreenwichYear(12, 0, 0, ds, zc, ld, lm, ly);
  double sr = SunLong(12, 0, 0, ds, zc, ld, lm, ly);

  std::tuple<double, double, double, double, ETwilightStatus> result1 =
      ETwilight_L3710(gd, gm, gy, sr, di, gp);

  if (std::get<4>(result1) != ETwilightStatus::Ok) {
    return std::get<4>(result1);
  }

  double x =
      LocalSiderealTimeToGreenwichSiderealTime(std::get<3>(result1), 0, 0, gl);
  double ut = GreenwichSiderealTimeToUniversalTime(x, 0, 0, gd, gm, gy);
  sr = SunLong(ut, 0, 0, 0, 0, gd, gm, gy);

  std::tuple<double, double, double, double, ETwilightStatus> result2 =
      ETwilight_L3710(gd, gm, gy, sr, di, gp);

  if (std::get<4>(result2) != ETwilightStatus::Ok) {
    return std::get<4>(result2);
  }

  x = LocalSiderealTimeToGreenwichSiderealTime(std::get<3>(result2), 0, 0, gl);

  if (EGstUt(x, 0, 0, gd, gm, gy) != EWarningFlags::Ok) {
    return ETwilightStatus::ConversionError;
  }

  return std::get<4>(result2);
}

/**
 * \brief Helper function for e_twilight()
 *
 * @return std::tuple <double a, double x, double y, double la,
 * TwilightStatus ts>
 */
std::tuple<double, double, double, double, ETwilightStatus>
ETwilight_L3710(double gd, int gm, int gy, double sr, double di, double gp) {

  double a = sr + NutatLong(gd, gm, gy) - 0.005694;
  double x = EclipticRightAscension(a, 0, 0, 0, 0, 0, gd, gm, gy);
  double y = EclipticDeclination(a, 0, 0, 0, 0, 0, gd, gm, gy);
  double la = RiseSetLocalSiderealTimeRise(DecimalDegreesToDegreeHours(x), 0, 0,
                                           y, 0, 0, di, gp);
  ERiseSetStatus s =
      ERiseSet(DecimalDegreesToDegreeHours(x), 0, 0, y, 0, 0, di, gp);

  ETwilightStatus ts = ETwilightStatus::Ok;

  if (s == ERiseSetStatus::Circumpolar) {
    ts = ETwilightStatus::LastsAllNight;
  }

  if (s == ERiseSetStatus::NeverRises) {
    ts = ETwilightStatus::SunTooFarBelowHorizon;
  }

  return std::tuple<double, double, double, double, ETwilightStatus>{a, x, y,
                                                                     la, ts};
}

/**
 * \brief Calculate the angle between two celestial objects
 *
 * Original macro name: Angle
 */
double Angle(double xx1, double xm1, double xs1, double dd1, double dm1,
             double ds1, double xx2, double xm2, double xs2, double dd2,
             double dm2, double ds2, EAngleMeasure s) {
  double a = (s == EAngleMeasure::Hours)
                 ? DegreeHoursToDecimalDegrees(HmsToDh(xx1, xm1, xs1))
                 : DegreesMinutesSecondsToDecimalDegrees(xx1, xm1, xs1);
  double b = DegreesToRadians(a);
  double c = DegreesMinutesSecondsToDecimalDegrees(dd1, dm1, ds1);
  double d = DegreesToRadians(c);
  double e = (s == EAngleMeasure::Hours)
                 ? DegreeHoursToDecimalDegrees(HmsToDh(xx2, xm2, xs2))
                 : DegreesMinutesSecondsToDecimalDegrees(xx2, xm2, xs2);
  double f = DegreesToRadians(e);
  double g = DegreesMinutesSecondsToDecimalDegrees(dd2, dm2, ds2);
  double h = DegreesToRadians(g);
  double i = acos(sin(d) * sin(h) + cos(d) * cos(h) * cos(b - f));

  return WToDegrees(i);
}

/**
 * Calculate several planetary properties.
 */
pa_models::CPlanetCoordinates PlanetCoordinates(double lh, double lm, double ls,
                                                int ds, int zc, double dy,
                                                int mn, int yr, std::string s) {
  double a11 = 178.179078;
  double a12 = 415.2057519;
  double a13 = 0.0003011;
  double a14 = 0.0;
  double a21 = 75.899697;
  double a22 = 1.5554889;
  double a23 = 0.0002947;
  double a24 = 0.0;
  double a31 = 0.20561421;
  double a32 = 0.00002046;
  double a33 = -0.00000003;
  double a34 = 0.0;
  double a41 = 7.002881;
  double a42 = 0.0018608;
  double a43 = -0.0000183;
  double a44 = 0.0;
  double a51 = 47.145944;
  double a52 = 1.1852083;
  double a53 = 0.0001739;
  double a54 = 0.0;
  double a61 = 0.3870986;
  double a62 = 6.74;
  double a63 = -0.42;

  double b11 = 342.767053;
  double b12 = 162.5533664;
  double b13 = 0.0003097;
  double b14 = 0.0;
  double b21 = 130.163833;
  double b22 = 1.4080361;
  double b23 = -0.0009764;
  double b24 = 0.0;
  double b31 = 0.00682069;
  double b32 = -0.00004774;
  double b33 = 0.000000091;
  double b34 = 0.0;
  double b41 = 3.393631;
  double b42 = 0.0010058;
  double b43 = -0.000001;
  double b44 = 0.0;
  double b51 = 75.779647;
  double b52 = 0.89985;
  double b53 = 0.00041;
  double b54 = 0.0;
  double b61 = 0.7233316;
  double b62 = 16.92;
  double b63 = -4.4;

  double c11 = 293.737334;
  double c12 = 53.17137642;
  double c13 = 0.0003107;
  double c14 = 0.0;
  double c21 = 334.218203;
  double c22 = 1.8407584;
  double c23 = 0.0001299;
  double c24 = -0.00000119;
  double c31 = 0.0933129;
  double c32 = 0.000092064;
  double c33 = -0.000000077;
  double c34 = 0.0;
  double c41 = 1.850333;
  double c42 = -0.000675;
  double c43 = 0.0000126;
  double c44 = 0.0;
  double c51 = 48.786442;
  double c52 = 0.7709917;
  double c53 = -0.0000014;
  double c54 = -0.00000533;
  double c61 = 1.5236883;
  double c62 = 9.36;
  double c63 = -1.52;

  double d11 = 238.049257;
  double d12 = 8.434172183;
  double d13 = 0.0003347;
  double d14 = -0.00000165;
  double d21 = 12.720972;
  double d22 = 1.6099617;
  double d23 = 0.00105627;
  double d24 = -0.00000343;
  double d31 = 0.04833475;
  double d32 = 0.00016418;
  double d33 = -0.0000004676;
  double d34 = -0.0000000017;
  double d41 = 1.308736;
  double d42 = -0.0056961;
  double d43 = 0.0000039;
  double d44 = 0.0;
  double d51 = 99.443414;
  double d52 = 1.01053;
  double d53 = 0.00035222;
  double d54 = -0.00000851;
  double d61 = 5.202561;
  double d62 = 196.74;
  double d63 = -9.4;

  double e11 = 266.564377;
  double e12 = 3.398638567;
  double e13 = 0.0003245;
  double e14 = -0.0000058;
  double e21 = 91.098214;
  double e22 = 1.9584158;
  double e23 = 0.00082636;
  double e24 = 0.00000461;
  double e31 = 0.05589232;
  double e32 = -0.0003455;
  double e33 = -0.000000728;
  double e34 = 0.00000000074;
  double e41 = 2.492519;
  double e42 = -0.0039189;
  double e43 = -0.00001549;
  double e44 = 0.00000004;
  double e51 = 112.790414;
  double e52 = 0.8731951;
  double e53 = -0.00015218;
  double e54 = -0.00000531;
  double e61 = 9.554747;
  double e62 = 165.6;
  double e63 = -8.88;

  double f11 = 244.19747;
  double f12 = 1.194065406;
  double f13 = 0.000316;
  double f14 = -0.0000006;
  double f21 = 171.548692;
  double f22 = 1.4844328;
  double f23 = 0.0002372;
  double f24 = -0.00000061;
  double f31 = 0.0463444;
  double f32a = -0.00002658;
  double f33 = 0.000000077;
  double f34 = 0.0;
  double f41 = 0.772464;
  double f42 = 0.0006253;
  double f43 = 0.0000395;
  double f44 = 0.0;
  double f51 = 73.477111;
  double f52 = 0.4986678;
  double f53 = 0.0013117;
  double f54 = 0.0;
  double f61 = 19.21814;
  double f62 = 65.8;
  double f63 = -7.19;

  double g11 = 84.457994;
  double g12 = 0.6107942056;
  double g13 = 0.0003205;
  double g14 = -0.0000006;
  double g21 = 46.727364;
  double g22 = 1.4245744;
  double g23 = 0.00039082;
  double g24 = -0.000000605;
  double g31 = 0.00899704;
  double g32 = 0.00000633;
  double g33 = -0.000000002;
  double g34 = 0.0;
  double g41 = 1.779242;
  double g42 = -0.0095436;
  double g43 = -0.0000091;
  double g44 = 0.0;
  double g51 = 130.681389;
  double g52 = 1.098935;
  double g53 = 0.00024987;
  double g54 = -0.000004718;
  double g61 = 30.10957;
  double g62 = 62.2;
  double g63 = -6.87;

  std::vector<pa_data::PlanetDataPrecise> pl;

  pl.push_back(pa_data::PlanetDataPrecise("", 0, 0, 0, 0, 0, 0, 0, 0, 0, 0));

  int ip = 0;
  double b = LocalCivilTimeToUniversalTime(lh, lm, ls, ds, zc, dy, mn, yr);
  double gd = LocalCivilTimeGreenwichDay(lh, lm, ls, ds, zc, dy, mn, yr);
  int gm = LocalCivilTimeGreenwichMonth(lh, lm, ls, ds, zc, dy, mn, yr);
  int gy = LocalCivilTimeGreenwichYear(lh, lm, ls, ds, zc, dy, mn, yr);
  double a = CivilDateToJulianDate(gd, gm, gy);
  double t = ((a - 2415020.0) / 36525.0) + (b / 876600.0);

  double a0 = a11;
  double a1 = a12;
  double a2 = a13;
  double a3 = a14;
  double b0 = a21;
  double b1 = a22;
  double b2 = a23;
  double b3 = a24;
  double c0 = a31;
  double c1 = a32;
  double c2 = a33;
  double c3 = a34;
  double d0 = a41;
  double d1 = a42;
  double d2 = a43;
  double d3 = a44;
  double e0 = a51;
  double e1 = a52;
  double e2 = a53;
  double e3 = a54;
  double f = a61;
  double g = a62;
  double h = a63;
  double aa = a1 * t;
  b = 360.0 * (aa - floor(aa));
  double c = a0 + b + (a3 * t + a2) * t * t;

  pl.push_back(pa_data::PlanetDataPrecise(
      "Mercury", c - 360.0 * floor(c / 360.0),
      (a1 * 0.009856263) + (a2 + a3) / 36525.0,
      ((b3 * t + b2) * t + b1) * t + b0, ((c3 * t + c2) * t + c1) * t + c0,
      ((d3 * t + d2) * t + d1) * t + d0, ((e3 * t + e2) * t + e1) * t + e0, f,
      g, h, 0));

  a0 = b11;
  a1 = b12;
  a2 = b13;
  a3 = b14;
  b0 = b21;
  b1 = b22;
  b2 = b23;
  b3 = b24;
  c0 = b31;
  c1 = b32;
  c2 = b33;
  c3 = b34;
  d0 = b41;
  d1 = b42;
  d2 = b43;
  d3 = b44;
  e0 = b51;
  e1 = b52;
  e2 = b53;
  e3 = b54;
  f = b61;
  g = b62;
  h = b63;
  aa = a1 * t;
  b = 360.0 * (aa - floor(aa));
  c = a0 + b + (a3 * t + a2) * t * t;

  pl.push_back(pa_data::PlanetDataPrecise(
      "Venus", c - 360.0 * floor(c / 360.0),
      (a1 * 0.009856263) + (a2 + a3) / 36525.0,
      ((b3 * t + b2) * t + b1) * t + b0, ((c3 * t + c2) * t + c1) * t + c0,
      ((d3 * t + d2) * t + d1) * t + d0, ((e3 * t + e2) * t + e1) * t + e0, f,
      g, h, 0));

  a0 = c11;
  a1 = c12;
  a2 = c13;
  a3 = c14;
  b0 = c21;
  b1 = c22;
  b2 = c23;
  b3 = c24;
  c0 = c31;
  c1 = c32;
  c2 = c33;
  c3 = c34;
  d0 = c41;
  d1 = c42;
  d2 = c43;
  d3 = c44;
  e0 = c51;
  e1 = c52;
  e2 = c53;
  e3 = c54;
  f = c61;
  g = c62;
  h = c63;

  aa = a1 * t;
  b = 360.0 * (aa - floor(aa));
  c = a0 + b + (a3 * t + a2) * t * t;

  pl.push_back(pa_data::PlanetDataPrecise(
      "Mars", c - 360.0 * floor(c / 360.0),
      (a1 * 0.009856263) + (a2 + a3) / 36525.0,
      ((b3 * t + b2) * t + b1) * t + b0, ((c3 * t + c2) * t + c1) * t + c0,
      ((d3 * t + d2) * t + d1) * t + d0, ((e3 * t + e2) * t + e1) * t + e0, f,
      g, h, 0));

  a0 = d11;
  a1 = d12;
  a2 = d13;
  a3 = d14;
  b0 = d21;
  b1 = d22;
  b2 = d23;
  b3 = d24;
  c0 = d31;
  c1 = d32;
  c2 = d33;
  c3 = d34;
  d0 = d41;
  d1 = d42;
  d2 = d43;
  d3 = d44;
  e0 = d51;
  e1 = d52;
  e2 = d53;
  e3 = d54;
  f = d61;
  g = d62;
  h = d63;

  aa = a1 * t;
  b = 360.0 * (aa - floor(aa));
  c = a0 + b + (a3 * t + a2) * t * t;

  pl.push_back(pa_data::PlanetDataPrecise(
      "Jupiter", c - 360.0 * floor(c / 360.0),
      (a1 * 0.009856263) + (a2 + a3) / 36525.0,
      ((b3 * t + b2) * t + b1) * t + b0, ((c3 * t + c2) * t + c1) * t + c0,
      ((d3 * t + d2) * t + d1) * t + d0, ((e3 * t + e2) * t + e1) * t + e0, f,
      g, h, 0));

  a0 = e11;
  a1 = e12;
  a2 = e13;
  a3 = e14;
  b0 = e21;
  b1 = e22;
  b2 = e23;
  b3 = e24;
  c0 = e31;
  c1 = e32;
  c2 = e33;
  c3 = e34;
  d0 = e41;
  d1 = e42;
  d2 = e43;
  d3 = e44;
  e0 = e51;
  e1 = e52;
  e2 = e53;
  e3 = e54;
  f = e61;
  g = e62;
  h = e63;

  aa = a1 * t;
  b = 360.0 * (aa - floor(aa));
  c = a0 + b + (a3 * t + a2) * t * t;

  pl.push_back(pa_data::PlanetDataPrecise(
      "Saturn", c - 360.0 * floor(c / 360.0),
      (a1 * 0.009856263) + (a2 + a3) / 36525.0,
      ((b3 * t + b2) * t + b1) * t + b0, ((c3 * t + c2) * t + c1) * t + c0,
      ((d3 * t + d2) * t + d1) * t + d0, ((e3 * t + e2) * t + e1) * t + e0, f,
      g, h, 0));

  a0 = f11;
  a1 = f12;
  a2 = f13;
  a3 = f14;
  b0 = f21;
  b1 = f22;
  b2 = f23;
  b3 = f24;
  c0 = f31;
  c1 = f32a;
  c2 = f33;
  c3 = f34;
  d0 = f41;
  d1 = f42;
  d2 = f43;
  d3 = f44;
  e0 = f51;
  e1 = f52;
  e2 = f53;
  e3 = f54;
  f = f61;
  g = f62;
  h = f63;

  aa = a1 * t;
  b = 360.0 * (aa - floor(aa));
  c = a0 + b + (a3 * t + a2) * t * t;

  pl.push_back(pa_data::PlanetDataPrecise(
      "Uranus", c - 360.0 * floor(c / 360.0),
      (a1 * 0.009856263) + (a2 + a3) / 36525.0,
      ((b3 * t + b2) * t + b1) * t + b0, ((c3 * t + c2) * t + c1) * t + c0,
      ((d3 * t + d2) * t + d1) * t + d0, ((e3 * t + e2) * t + e1) * t + e0, f,
      g, h, 0));

  a0 = g11;
  a1 = g12;
  a2 = g13;
  a3 = g14;
  b0 = g21;
  b1 = g22;
  b2 = g23;
  b3 = g24;
  c0 = g31;
  c1 = g32;
  c2 = g33;
  c3 = g34;
  d0 = g41;
  d1 = g42;
  d2 = g43;
  d3 = g44;
  e0 = g51;
  e1 = g52;
  e2 = g53;
  e3 = g54;
  f = g61;
  g = g62;
  h = g63;

  aa = a1 * t;
  b = 360.0 * (aa - floor(aa));
  c = a0 + b + (a3 * t + a2) * t * t;

  pl.push_back(pa_data::PlanetDataPrecise(
      "Neptune", c - 360.0 * floor(c / 360.0),
      (a1 * 0.009856263) + (a2 + a3) / 36525.0,
      ((b3 * t + b2) * t + b1) * t + b0, ((c3 * t + c2) * t + c1) * t + c0,
      ((d3 * t + d2) * t + d1) * t + d0, ((e3 * t + e2) * t + e1) * t + e0, f,
      g, h, 0));

  pa_data::PlanetDataPrecise check_planet =
      pa_data::getPrecisePlanetData(s, pl);

  if (check_planet.name == "NoMatch") {
    return (pa_models::CPlanetCoordinates){
        WToDegrees(Unwind(0)), WToDegrees(Unwind(0)), WToDegrees(Unwind(0)),
        WToDegrees(Unwind(0)), WToDegrees(Unwind(0)), WToDegrees(Unwind(0)),
        WToDegrees(Unwind(0))};
  }

  double li = 0.0;
  double ms = SunMeanAnomaly(lh, lm, ls, ds, zc, dy, mn, yr);
  double sr = DegreesToRadians(SunLong(lh, lm, ls, ds, zc, dy, mn, yr));
  double re = SunDist(lh, lm, ls, ds, zc, dy, mn, yr);
  double lg = sr + M_PI;

  double l0 = 0.0;
  double s0 = 0.0;
  double p0 = 0.0;
  double vo = 0.0;
  double lp1 = 0.0;
  double ll = 0.0;
  double rd = 0.0;
  double pd = 0.0;
  double sp = 0.0;
  double ci = 0.0;

  for (int k = 1; k <= 3; k++) {
    for (int i = 0; i < pl.size(); i++) {
      pl[i].ap_value =
          DegreesToRadians(pl[i].value1 - pl[i].value3 - li * pl[i].value2);
    }

    double qa = 0.0;
    double qb = 0.0;
    double qc = 0.0;
    double qd = 0.0;
    double qe = 0.0;
    double qf = 0.0;
    double qg = 0.0;

    if (s == "Mercury") {
      pa_models::CPlanetLongLatL4685 temp_result = PlanetLongL4685(pl);
      qa = temp_result.qa;
      qb = temp_result.qb;
    }

    if (s == "Venus") {
      pa_models::CPlanetLongLatL4735 temp_result = PlanetLongL4735(pl, ms, t);

      qa = temp_result.qa;
      qb = temp_result.qb;
      qc = temp_result.qc;
      qe = temp_result.qe;
    }

    if (s == "Mars") {
      pa_models::CPlanetLongLatL4810 temp_result = PlanetLongL4810(pl, ms);

      qc = temp_result.qc;
      qe = temp_result.qe;
      qa = temp_result.qa;
      qb = temp_result.qb;
    }

    pa_data::PlanetDataPrecise match_planet =
        pa_data::getPrecisePlanetData(s, pl);

    if ((s == "Jupiter") || (s == "Saturn") || (s == "Uranus") ||
        (s == "Neptune")) {
      pa_models::CPlanetLongLatL4945 temp_result =
          PlanetLongL4945(t, match_planet);

      qa = temp_result.qa;
      qb = temp_result.qb;
      qc = temp_result.qc;
      qd = temp_result.qd;
      qe = temp_result.qe;
      qf = temp_result.qf;
      qg = temp_result.qg;
    }

    double ec = match_planet.value4 + qd;
    double am = match_planet.ap_value + qe;
    double at = TrueAnomaly(am, ec);
    double pvv =
        (match_planet.value7 + qf) * (1.0 - ec * ec) / (1.0 + ec * cos(at));
    double lp = WToDegrees(at) + match_planet.value3 + WToDegrees(qc - qe);
    lp = DegreesToRadians(lp);
    double om = DegreesToRadians(match_planet.value6);
    double lo = lp - om;
    double so = sin(lo);
    double co = cos(lo);
    double inn = DegreesToRadians(match_planet.value5);
    pvv += qb;
    sp = so * sin(inn);
    double y = so * cos(inn);
    double ps = asin(sp) + qg;
    sp = sin(ps);
    pd = atan2(y, co) + om + DegreesToRadians(qa);
    pd = Unwind(pd);
    ci = cos(ps);
    rd = pvv * ci;
    ll = pd - lg;
    double rh = re * re + pvv * pvv - 2.0 * re * pvv * ci * cos(ll);
    rh = sqrt(rh);
    li = rh * 0.005775518;

    if (k == 1) {
      l0 = pd;
      s0 = ps;
      p0 = pvv;
      vo = rh;
      lp1 = lp;
    }
  }

  double l1 = sin(ll);
  double l2 = cos(ll);

  double ep = (ip < 3) ? atan(-1.0 * rd * l1 / (re - rd * l2)) + lg + M_PI
                       : atan(re * l1 / (rd - re * l2)) + pd;
  ep = Unwind(ep);

  double bp = atan(rd * sp * sin(ep - pd) / (ci * re * l1));

  double planetLongitude = WToDegrees(Unwind(ep));
  double planetLatitude = WToDegrees(Unwind(bp));
  double planetDistanceAU = vo;
  double planetHLong1 = WToDegrees(lp1);
  double planetHLong2 = WToDegrees(l0);
  double planetHLat = WToDegrees(s0);
  double planetRVect = p0;

  return (pa_models::CPlanetCoordinates(planetLongitude, planetLatitude,
                                        planetDistanceAU, planetHLong1,
                                        planetHLong2, planetHLat, planetRVect));
}

/**
 * Helper function for PlanetCoordinates()
 */
pa_models::CPlanetLongLatL4685
PlanetLongL4685(std::vector<pa_data::PlanetDataPrecise> pl) {
  double qa =
      0.00204 * cos(5.0 * pl[2].ap_value - 2.0 * pl[1].ap_value + 0.21328);
  qa += 0.00103 * cos(2.0 * pl[2].ap_value - pl[1].ap_value - 2.8046);
  qa += 0.00091 * cos(2.0 * pl[4].ap_value - pl[1].ap_value - 0.64582);
  qa += 0.00078 * cos(5.0 * pl[2].ap_value - 3.0 * pl[1].ap_value + 0.17692);

  double qb =
      0.000007525 * cos(2.0 * pl[4].ap_value - pl[1].ap_value + 0.925251);
  qb +=
      0.000006802 * cos(5.0 * pl[2].ap_value - 3.0 * pl[1].ap_value - 4.53642);
  qb +=
      0.000005457 * cos(2.0 * pl[2].ap_value - 2.0 * pl[1].ap_value - 1.24246);
  qb += 0.000003569 * cos(5.0 * pl[2].ap_value - pl[1].ap_value - 1.35699);

  return (pa_models::CPlanetLongLatL4685(qa, qb));
}

/**
 * Helper function for PlanetCoordinates()
 */
pa_models::CPlanetLongLatL4735
PlanetLongL4735(std::vector<pa_data::PlanetDataPrecise> pl, double ms,
                double t) {
  double qc = 0.00077 * sin(4.1406 + t * 2.6227);
  qc = DegreesToRadians(qc);
  double qe = qc;

  double qa = 0.00313 * cos(2.0 * ms - 2.0 * pl[2].ap_value - 2.587);
  qa += 0.00198 * cos(3.0 * ms - 3.0 * pl[2].ap_value + 0.044768);
  qa += 0.00136 * cos(ms - pl[2].ap_value - 2.0788);
  qa += 0.00096 * cos(3.0 * ms - 2.0 * pl[2].ap_value - 2.3721);
  qa += 0.00082 * cos(pl[4].ap_value - pl[2].ap_value - 3.6318);

  double qb = 0.000022501 * cos(2.0 * ms - 2.0 * pl[2].ap_value - 1.01592);
  qb += 0.000019045 * cos(3.0 * ms - 3.0 * pl[2].ap_value + 1.61577);
  qb += 0.000006887 * cos(pl[4].ap_value - pl[2].ap_value - 2.06106);
  qb += 0.000005172 * cos(ms - pl[2].ap_value - 0.508065);
  qb += 0.00000362 * cos(5.0 * ms - 4.0 * pl[2].ap_value - 1.81877);
  qb += 0.000003283 * cos(4.0 * ms - 4.0 * pl[2].ap_value + 1.10851);
  qb +=
      0.000003074 * cos(2.0 * pl[4].ap_value - 2.0 * pl[2].ap_value - 0.962846);

  return (pa_models::CPlanetLongLatL4735(qa, qb, qc, qe));
}

/**
 * Helper function for PlanetCoordinates()
 */
pa_models::CPlanetLongLatL4810
PlanetLongL4810(std::vector<pa_data::PlanetDataPrecise> pl, double ms) {
  double a = 3.0 * pl[4].ap_value - 8.0 * pl[3].ap_value + 4.0 * ms;
  double sa = sin(a);
  double ca = cos(a);
  double qc = -(0.01133 * sa + 0.00933 * ca);
  qc = DegreesToRadians(qc);
  double qe = qc;

  double qa = 0.00705 * cos(pl[4].ap_value - pl[3].ap_value - 0.85448);
  qa += 0.00607 * cos(2.0 * pl[4].ap_value - pl[3].ap_value - 3.2873);
  qa += 0.00445 * cos(2.0 * pl[4].ap_value - 2.0 * pl[3].ap_value - 3.3492);
  qa += 0.00388 * cos(ms - 2.0 * pl[3].ap_value + 0.35771);
  qa += 0.00238 * cos(ms - pl[3].ap_value + 0.61256);
  qa += 0.00204 * cos(2.0 * ms - 3.0 * pl[3].ap_value + 2.7688);
  qa += 0.00177 * cos(3.0 * pl[3].ap_value - pl[2].ap_value - 1.0053);
  qa += 0.00136 * cos(2.0 * ms - 4.0 * pl[3].ap_value + 2.6894);
  qa += 0.00104 * cos(pl[4].ap_value + 0.30749);

  double qb = 0.000053227 * cos(pl[4].ap_value - pl[3].ap_value + 0.717864);
  qb +=
      0.000050989 * cos(2.0 * pl[4].ap_value - 2.0 * pl[3].ap_value - 1.77997);
  qb += 0.000038278 * cos(2.0 * pl[4].ap_value - pl[3].ap_value - 1.71617);
  qb += 0.000015996 * cos(ms - pl[3].ap_value - 0.969618);
  qb += 0.000014764 * cos(2.0 * ms - 3.0 * pl[3].ap_value + 1.19768);
  qb += 0.000008966 * cos(pl[4].ap_value - 2.0 * pl[3].ap_value + 0.761225);
  qb +=
      0.000007914 * cos(3.0 * pl[4].ap_value - 2.0 * pl[3].ap_value - 2.43887);
  qb +=
      0.000007004 * cos(2.0 * pl[4].ap_value - 3.0 * pl[3].ap_value - 1.79573);
  qb += 0.00000662 * cos(ms - 2.0 * pl[3].ap_value + 1.97575);
  qb += 0.00000493 * cos(3.0 * pl[4].ap_value - 3.0 * pl[3].ap_value - 1.33069);
  qb += 0.000004693 * cos(3.0 * ms - 5.0 * pl[3].ap_value + 3.32665);
  qb += 0.000004571 * cos(2.0 * ms - 4.0 * pl[3].ap_value + 4.27086);
  qb += 0.000004409 * cos(3.0 * pl[4].ap_value - pl[3].ap_value - 2.02158);

  return (pa_models::CPlanetLongLatL4810(a, sa, ca, qc, qe, qa, qb));
}

/**
 * Helper function for PlanetCoordinates()
 */
pa_models::CPlanetLongLatL4945
PlanetLongL4945(double t, pa_data::PlanetDataPrecise planet) {
  double qa = 0.0;
  double qb = 0.0;
  double qc = 0.0;
  double qd = 0.0;
  double qe = 0.0;
  double qf = 0.0;
  double qg = 0.0;
  double vk = 0.0;
  double ja = 0.0;
  double jb = 0.0;
  double jc = 0.0;

  double j1 = t / 5.0 + 0.1;
  double j2 = Unwind(4.14473 + 52.9691 * t);
  double j3 = Unwind(4.641118 + 21.32991 * t);
  double j4 = Unwind(4.250177 + 7.478172 * t);
  double j5 = 5.0 * j3 - 2.0 * j2;
  double j6 = 2.0 * j2 - 6.0 * j3 + 3.0 * j4;

  if ((planet.name == "Mercury") || (planet.name == "Venus") ||
      (planet.name == "Mars")) {
    return (pa_models::CPlanetLongLatL4945(qa, qb, qc, qd, qe, qf, qg));
  }

  if ((planet.name == "Jupiter") || (planet.name == "Saturn")) {
    double j7 = j3 - j2;
    double u1 = sin(j3);
    double u2 = cos(j3);
    double u3 = sin(2.0 * j3);
    double u4 = cos(2.0 * j3);
    double u5 = sin(j5);
    double u6 = cos(j5);
    double u7 = sin(2.0 * j5);
    double u8a = sin(j6);
    double u9 = sin(j7);
    double ua = cos(j7);
    double ub = sin(2.0 * j7);
    double uc = cos(2.0 * j7);
    double ud = sin(3.0 * j7);
    double ue = cos(3.0 * j7);
    double uf = sin(4.0 * j7);
    double ug = cos(4.0 * j7);
    double vh = cos(5.0 * j7);

    if (planet.name == "Saturn") {
      double ui = sin(3.0 * j3);
      double uj = cos(3.0 * j3);
      double uk = sin(4.0 * j3);
      double ul = cos(4.0 * j3);
      double vi = cos(2.0 * j5);
      double un = sin(5.0 * j7);
      double j8 = j4 - j3;
      double uo = sin(2.0 * j8);
      double up = cos(2.0 * j8);
      double uq = sin(3.0 * j8);
      double ur = cos(3.0 * j8);

      qc = 0.007581 * u7 - 0.007986 * u8a - 0.148811 * u9;
      qc -= (0.814181 - (0.01815 - 0.016714 * j1) * j1) * u5;
      qc -= (0.010497 - (0.160906 - 0.0041 * j1) * j1) * u6;
      qc = qc - 0.015208 * ud - 0.006339 * uf - 0.006244 * u1;
      qc = qc - 0.0165 * ub * u1 - 0.040786 * ub;
      qc = qc + (0.008931 + 0.002728 * j1) * u9 * u1 - 0.005775 * ud * u1;
      qc = qc + (0.081344 + 0.003206 * j1) * ua * u1 + 0.015019 * uc * u1;
      qc = qc + (0.085581 + 0.002494 * j1) * u9 * u2 + 0.014394 * uc * u2;
      qc = qc + (0.025328 - 0.003117 * j1) * ua * u2 + 0.006319 * ue * u2;
      qc = qc + 0.006369 * u9 * u3 + 0.009156 * ub * u3 + 0.007525 * uq * u3;
      qc = qc - 0.005236 * ua * u4 - 0.007736 * uc * u4 - 0.007528 * ur * u4;
      qc = DegreesToRadians(qc);

      qd = (-7927.0 + (2548.0 + 91.0 * j1) * j1) * u5;
      qd = qd + (13381.0 + (1226.0 - 253.0 * j1) * j1) * u6 +
           (248.0 - 121.0 * j1) * u7;
      qd = qd - (305.0 + 91.0 * j1) * vi + 412.0 * ub + 12415.0 * u1;
      qd = qd + (390.0 - 617.0 * j1) * u9 * u1 + (165.0 - 204.0 * j1) * ub * u1;
      qd = qd + 26599.0 * ua * u1 - 4687.0 * uc * u1 - 1870.0 * ue * u1 -
           821.0 * ug * u1;
      qd = qd - 377.0 * vh * u1 + 497.0 * up * u1 + (163.0 - 611.0 * j1) * u2;
      qd = qd - 12696.0 * u9 * u2 - 4200.0 * ub * u2 - 1503.0 * ud * u2 -
           619.0 * uf * u2;
      qd = qd - 268.0 * un * u2 - (282.0 + 1306.0 * j1) * ua * u2;
      qd = qd + (-86.0 + 230.0 * j1) * uc * u2 + 461.0 * uo * u2 - 350.0 * u3;
      qd = qd + (2211.0 - 286.0 * j1) * u9 * u3 - 2208.0 * ub * u3 -
           568.0 * ud * u3;
      qd = qd - 346.0 * uf * u3 - (2780.0 + 222.0 * j1) * ua * u3;
      qd = qd + (2022.0 + 263.0 * j1) * uc * u3 + 248.0 * ue * u3 +
           242.0 * uq * u3;
      qd = qd + 467.0 * ur * u3 - 490.0 * u4 - (2842.0 + 279.0 * j1) * u9 * u4;
      qd = qd + (128.0 + 226.0 * j1) * ub * u4 + 224.0 * ud * u4;
      qd = qd + (-1594.0 + 282.0 * j1) * ua * u4 +
           (2162.0 - 207.0 * j1) * uc * u4;
      qd = qd + 561.0 * ue * u4 + 343.0 * ug * u4 + 469.0 * uq * u4 -
           242.0 * ur * u4;
      qd = qd - 205.0 * u9 * ui + 262.0 * ud * ui + 208.0 * ua * uj -
           271.0 * ue * uj;
      qd = qd - 382.0 * ue * uk - 376.0 * ud * ul;
      qd *= 0.0000001;

      vk = (0.077108 + (0.007186 - 0.001533 * j1) * j1) * u5;
      vk -= 0.007075 * u9;
      vk += (0.045803 - (0.014766 + 0.000536 * j1) * j1) * u6;
      vk = vk - 0.072586 * u2 - 0.075825 * u9 * u1 - 0.024839 * ub * u1;
      vk = vk - 0.008631 * ud * u1 - 0.150383 * ua * u2;
      vk = vk + 0.026897 * uc * u2 + 0.010053 * ue * u2;
      vk = vk - (0.013597 + 0.001719 * j1) * u9 * u3 + 0.011981 * ub * u4;
      vk -= (0.007742 - 0.001517 * j1) * ua * u3;
      vk += (0.013586 - 0.001375 * j1) * uc * u3;
      vk -= (0.013667 - 0.001239 * j1) * u9 * u4;
      vk += (0.014861 + 0.001136 * j1) * ua * u4;
      vk -= (0.013064 + 0.001628 * j1) * uc * u4;
      qe = qc - (DegreesToRadians(vk) / planet.value4);

      qf = 572.0 * u5 - 1590.0 * ub * u2 + 2933.0 * u6 - 647.0 * ud * u2;
      qf = qf + 33629.0 * ua - 344.0 * uf * u2 - 3081.0 * uc + 2885.0 * ua * u2;
      qf = qf - 1423.0 * ue + (2172.0 + 102.0 * j1) * uc * u2 - 671.0 * ug;
      qf = qf + 296.0 * ue * u2 - 320.0 * vh - 267.0 * ub * u3 + 1098.0 * u1;
      qf = qf - 778.0 * ua * u3 - 2812.0 * u9 * u1 + 495.0 * uc * u3 +
           688.0 * ub * u1;
      qf = qf + 250.0 * ue * u3 - 393.0 * ud * u1 - 856.0 * u9 * u4 -
           228.0 * uf * u1;
      qf = qf + 441.0 * ub * u4 + 2138.0 * ua * u1 + 296.0 * uc * u4 -
           999.0 * uc * u1;
      qf = qf + 211.0 * ue * u4 - 642.0 * ue * u1 - 427.0 * u9 * ui -
           325.0 * ug * u1;
      qf = qf + 398.0 * ud * ui - 890.0 * u2 + 344.0 * ua * uj +
           2206.0 * u9 * u2;
      qf -= 427.0 * ue * uj;
      qf *= 0.000001;

      qg = 0.000747 * ua * u1 + 0.001069 * ua * u2 + 0.002108 * ub * u3;
      qg = qg + 0.001261 * uc * u3 + 0.001236 * ub * u4 - 0.002075 * uc * u4;
      qg = DegreesToRadians(qg);

      return (pa_models::CPlanetLongLatL4945(qa, qb, qc, qd, qe, qf, qg));
    }

    qc = (0.331364 - (0.010281 + 0.004692 * j1) * j1) * u5;
    qc += (0.003228 - (0.064436 - 0.002075 * j1) * j1) * u6;
    qc -= (0.003083 + (0.000275 - 0.000489 * j1) * j1) * u7;
    qc = qc + 0.002472 * u8a + 0.013619 * u9 + 0.018472 * ub;
    qc = qc + 0.006717 * ud + 0.002775 * uf + 0.006417 * ub * u1;
    qc = qc + (0.007275 - 0.001253 * j1) * u9 * u1 + 0.002439 * ud * u1;
    qc = qc - (0.035681 + 0.001208 * j1) * u9 * u2 - 0.003767 * uc * u1;
    qc = qc - (0.033839 + 0.001125 * j1) * ua * u1 - 0.004261 * ub * u2;
    qc = qc + (0.001161 * j1 - 0.006333) * ua * u2 + 0.002178 * u2;
    qc = qc - 0.006675 * uc * u2 - 0.002664 * ue * u2 - 0.002572 * u9 * u3;
    qc = qc - 0.003567 * ub * u3 + 0.002094 * ua * u4 + 0.003342 * uc * u4;
    qc = DegreesToRadians(qc);

    qd = (3606.0 + (130.0 - 43.0 * j1) * j1) * u5 + (1289.0 - 580.0 * j1) * u6;
    qd =
        qd - 6764.0 * u9 * u1 - 1110.0 * ub * u1 - 224.0 * ud * u1 - 204.0 * u1;
    qd = qd + (1284.0 + 116.0 * j1) * ua * u1 + 188.0 * uc * u1;
    qd = qd + (1460.0 + 130.0 * j1) * u9 * u2 + 224.0 * ub * u2 - 817.0 * u2;
    qd = qd + 6074.0 * u2 * ua + 992.0 * uc * u2 + 508.0 * ue * u2 +
         230.0 * ug * u2;
    qd = qd + 108.0 * vh * u2 - (956.0 + 73.0 * j1) * u9 * u3 + 448.0 * ub * u3;
    qd =
        qd + 137.0 * ud * u3 + (108.0 * j1 - 997.0) * ua * u3 + 480.0 * uc * u3;
    qd = qd + 148.0 * ue * u3 + (99.0 * j1 - 956.0) * u9 * u4 + 490.0 * ub * u4;
    qd = qd + 158.0 * ud * u4 + 179.0 * u4 + (1024.0 + 75.0 * j1) * ua * u4;
    qd = qd - 437.0 * uc * u4 - 132.0 * ue * u4;
    qd *= 0.0000001;

    vk = (0.007192 - 0.003147 * j1) * u5 - 0.004344 * u1;
    vk += (j1 * (0.000197 * j1 - 0.000675) - 0.020428) * u6;
    vk = vk + 0.034036 * ua * u1 + (0.007269 + 0.000672 * j1) * u9 * u1;
    vk = vk + 0.005614 * uc * u1 + 0.002964 * ue * u1 + 0.037761 * u9 * u2;
    vk = vk + 0.006158 * ub * u2 - 0.006603 * ua * u2 - 0.005356 * u9 * u3;
    vk = vk + 0.002722 * ub * u3 + 0.004483 * ua * u3;
    vk = vk - 0.002642 * uc * u3 + 0.004403 * u9 * u4;
    vk = vk - 0.002536 * ub * u4 + 0.005547 * ua * u4 - 0.002689 * uc * u4;
    qe = qc - (DegreesToRadians(vk) / planet.value4);

    qf = 205.0 * ua - 263.0 * u6 + 693.0 * uc + 312.0 * ue + 147.0 * ug +
         299.0 * u9 * u1;
    qf = qf + 181.0 * uc * u1 + 204.0 * ub * u2 + 111.0 * ud * u2 -
         337.0 * ua * u2;
    qf -= 111.0 * uc * u2;
    qf *= 0.000001;

    return (pa_models::CPlanetLongLatL4945(qa, qb, qc, qd, qe, qf, qg));
  }

  if ((planet.name == "Uranus") || (planet.name == "Neptune")) {
    double j8 = Unwind(1.46205 + 3.81337 * t);
    double j9 = 2.0 * j8 - j4;
    double vj = sin(j9);
    double uu = cos(j9);
    double uv = sin(2.0 * j9);
    double uw = cos(2.0 * j9);

    if (planet.name == "Neptune") {
      ja = j8 - j2;
      jb = j8 - j3;
      jc = j8 - j4;
      qc = (0.001089 * j1 - 0.589833) * vj;
      qc = qc + (0.004658 * j1 - 0.056094) * uu - 0.024286 * uv;
      qc = DegreesToRadians(qc);

      vk = 0.024039 * vj - 0.025303 * uu + 0.006206 * uv;
      vk -= 0.005992 * uw;
      qe = qc - (DegreesToRadians(vk) / planet.value4);

      qd = 4389.0 * vj + 1129.0 * uv + 4262.0 * uu + 1089.0 * uw;
      qd *= 0.0000001;

      qf = 8189.0 * uu - 817.0 * vj + 781.0 * uw;
      qf *= 0.000001;

      double vd = sin(2.0 * jc);
      double ve = cos(2.0 * jc);
      double vf = sin(j8);
      double vg = cos(j8);
      qa = -0.009556 * sin(ja) - 0.005178 * sin(jb);
      qa = qa + 0.002572 * vd - 0.002972 * ve * vf - 0.002833 * vd * vg;

      qg = 0.000336 * ve * vf + 0.000364 * vd * vg;
      qg = DegreesToRadians(qg);

      qb = -40596.0 + 4992.0 * cos(ja) + 2744.0 * cos(jb);
      qb = qb + 2044.0 * cos(jc) + 1051.0 * ve;
      qb *= 0.000001;

      return (pa_models::CPlanetLongLatL4945(qa, qb, qc, qd, qe, qf, qg));
    }

    ja = j4 - j2;
    jb = j4 - j3;
    jc = j8 - j4;
    qc = (0.864319 - 0.001583 * j1) * vj;
    qc = qc + (0.082222 - 0.006833 * j1) * uu + 0.036017 * uv;
    qc = qc - 0.003019 * uw + 0.008122 * sin(j6);
    qc = DegreesToRadians(qc);

    vk = 0.120303 * vj + 0.006197 * uv;
    vk += (0.019472 - 0.000947 * j1) * uu;
    qe = qc - (DegreesToRadians(vk) / planet.value4);

    qd = (163.0 * j1 - 3349.0) * vj + 20981.0 * uu + 1311.0 * uw;
    qd *= 0.0000001;

    qf = -0.003825 * uu;

    qa = (-0.038581 + (0.002031 - 0.00191 * j1) * j1) * cos(j4 + jb);
    qa += (0.010122 - 0.000988 * j1) * sin(j4 + jb);
    double a =
        (0.034964 - (0.001038 - 0.000868 * j1) * j1) * cos(2.0 * j4 + jb);
    qa = a + qa + 0.005594 * sin(j4 + 3.0 * jc) - 0.014808 * sin(ja);
    qa = qa - 0.005794 * sin(jb) + 0.002347 * cos(jb);
    qa = qa + 0.009872 * sin(jc) + 0.008803 * sin(2.0 * jc);
    qa -= 0.004308 * sin(3.0 * jc);

    double ux = sin(jb);
    double uy = cos(jb);
    double uz = sin(j4);
    double va = cos(j4);
    double vb = sin(2.0 * j4);
    double vc = cos(2.0 * j4);
    qg = (0.000458 * ux - 0.000642 * uy - 0.000517 * cos(4.0 * jc)) * uz;
    qg -= (0.000347 * ux + 0.000853 * uy + 0.000517 * sin(4.0 * jb)) * va;
    qg += 0.000403 * (cos(2.0 * jc) * vb + sin(2.0 * jc) * vc);
    qg = DegreesToRadians(qg);

    qb = -25948.0 + 4985.0 * cos(ja) - 1230.0 * va + 3354.0 * uy;
    qb = qb + 904.0 * cos(2.0 * jc) + 894.0 * (cos(jc) - cos(3.0 * jc));
    qb += (5795.0 * va - 1165.0 * uz + 1388.0 * vc) * ux;
    qb += (1351.0 * va + 5702.0 * uz + 1388.0 * vb) * uy;
    qb *= 0.000001;

    return (pa_models::CPlanetLongLatL4945(qa, qb, qc, qd, qe, qf, qg));
  }

  return (pa_models::CPlanetLongLatL4945(qa, qb, qc, qd, qe, qf, qg));
}

/**
 * Calculate longitude, latitude, and distance of parabolic-orbit comet.
 *
 * Original macro names: PcometLong, PcometLat, PcometDist
 */
pa_models::CCometLongLatDist
PCometLongLatDist(double lh, /** Local civil time, hour part. */
                  double lm, /** Local civil time, minutes part. */
                  double ls, /** Local civil time, seconds part. */
                  int ds,    /** Daylight Savings offset. */
                  int zc,    /** Time zone correction, in hours. */
                  double dy, /** Local date, day part. */
                  int mn,    /** Local date, month part. */
                  int yr,    /** Local date, year part. */
                  double td, /** Perihelion epoch (day) */
                  int tm,    /** Perihelion epoch (month) */
                  int ty,    /** Perihelion epoch (year) */
                  double q,  /** a (AU) */
                  double i,  /** Inclination (degrees) */
                  double p,  /** Perihelion (degrees) */
                  double n   /** Node (degrees) */
) {
  double gd = LocalCivilTimeGreenwichDay(lh, lm, ls, ds, zc, dy, mn, yr);
  int gm = LocalCivilTimeGreenwichMonth(lh, lm, ls, ds, zc, dy, mn, yr);
  int gy = LocalCivilTimeGreenwichYear(lh, lm, ls, ds, zc, dy, mn, yr);
  double ut = LocalCivilTimeToUniversalTime(lh, lm, ls, ds, zc, dy, mn, yr);
  double tpe = (ut / 365.242191) + CivilDateToJulianDate(gd, gm, gy) -
               CivilDateToJulianDate(td, tm, ty);
  double lg = DegreesToRadians(SunLong(lh, lm, ls, ds, zc, dy, mn, yr) + 180.0);
  double re = SunDist(lh, lm, ls, ds, zc, dy, mn, yr);

  double rh2 = 0.0;
  double rd = 0.0;
  double s3 = 0.0;
  double c3 = 0.0;
  double lc = 0.0;
  double s2 = 0.0;
  double c2 = 0.0;

  for (int k = 1; k < 3; k++) {
    double s = SolveCubic(0.0364911624 * tpe / (q * sqrt(q)));
    double nu = 2.0 * atan(s);
    double r = q * (1.0 + s * s);
    double l = nu + DegreesToRadians(p);
    double s1 = sin(l);
    double c1 = cos(l);
    double i1 = DegreesToRadians(i);
    s2 = s1 * sin(i1);
    double ps = asin(s2);
    double y = s1 * cos(i1);
    lc = atan2(y, c1) + DegreesToRadians(n);
    c2 = cos(ps);
    rd = r * c2;
    double ll = lc - lg;
    c3 = cos(ll);
    s3 = sin(ll);
    double rh = sqrt((re * re) + (r * r) - (2.0 * re * rd * c3 * cos(ps)));
    if (k == 1) {
      rh2 = sqrt((re * re) + (r * r) -
                 (2.0 * re * r * cos(ps) * cos(l + DegreesToRadians(n) - lg)));
    }
  }

  double ep;

  ep = (rd < re) ? atan(-rd * s3 / (re - (rd * c3))) + lg + 3.141592654
                 : atan(re * s3 / (rd - (re * c3))) + lc;
  ep = Unwind(ep);

  double tb = rd * s2 * sin(ep - lc) / (c2 * re * s3);
  double bp = atan(tb);

  double comet_long_deg = WToDegrees(ep);
  double comet_lat_deg = WToDegrees(bp);
  double comet_dist_au = rh2;

  return pa_models::CCometLongLatDist(comet_long_deg, comet_lat_deg,
                                      comet_dist_au);
}

/**
 * For W, in radians, return S, also in radians.
 *
 * Original macro name: SolveCubic
 */
double SolveCubic(double w) {
  double s = w / 3.0;

  while (1 == 1) {
    double s2 = s * s;
    double d = (s2 + 3.0) * s - w;

    if (fabs(d) < 0.000001) {
      return s;
    }

    s = ((2.0 * s * s2) + w) / (3.0 * (s2 + 1.0));
  }
}

/**
 * Calculate longitude, latitude, and horizontal parallax of the Moon.
 *
 * Original macro names: MoonLong, MoonLat, MoonHP
 */
pa_models::CMoonLongLatHP MoonLongLatHP(double lh, double lm, double ls, int ds,
                                        int zc, double dy, int mn, int yr) {
  double ut = LocalCivilTimeToUniversalTime(lh, lm, ls, ds, zc, dy, mn, yr);
  double gd = LocalCivilTimeGreenwichDay(lh, lm, ls, ds, zc, dy, mn, yr);
  int gm = LocalCivilTimeGreenwichMonth(lh, lm, ls, ds, zc, dy, mn, yr);
  int gy = LocalCivilTimeGreenwichYear(lh, lm, ls, ds, zc, dy, mn, yr);
  double t = ((CivilDateToJulianDate(gd, gm, gy) - 2415020.0) / 36525.0) +
             (ut / 876600.0);
  double t2 = t * t;

  double m1 = 27.32158213;
  double m2 = 365.2596407;
  double m3 = 27.55455094;
  double m4 = 29.53058868;
  double m5 = 27.21222039;
  double m6 = 6798.363307;
  double q = CivilDateToJulianDate(gd, gm, gy) - 2415020.0 + (ut / 24.0);
  m1 = q / m1;
  m2 = q / m2;
  m3 = q / m3;
  m4 = q / m4;
  m5 = q / m5;
  m6 = q / m6;
  m1 = 360.0 * (m1 - floor(m1));
  m2 = 360.0 * (m2 - floor(m2));
  m3 = 360.0 * (m3 - floor(m3));
  m4 = 360.0 * (m4 - floor(m4));
  m5 = 360.0 * (m5 - floor(m5));
  m6 = 360.0 * (m6 - floor(m6));

  double ml = 270.434164 + m1 - (0.001133 - 0.0000019 * t) * t2;
  double ms = 358.475833 + m2 - (0.00015 + 0.0000033 * t) * t2;
  double md = 296.104608 + m3 + (0.009192 + 0.0000144 * t) * t2;
  double me1 = 350.737486 + m4 - (0.001436 - 0.0000019 * t) * t2;
  double mf = 11.250889 + m5 - (0.003211 + 0.0000003 * t) * t2;
  double na = 259.183275 - m6 + (0.002078 + 0.0000022 * t) * t2;
  double a = DegreesToRadians(51.2 + 20.2 * t);
  double s1 = sin(a);
  double s2 = sin(DegreesToRadians(na));
  double b = 346.56 + (132.87 - 0.0091731 * t) * t;
  double s3 = 0.003964 * sin(DegreesToRadians(b));
  double c = DegreesToRadians(na + 275.05 - 2.3 * t);
  double s4 = sin(c);
  ml = ml + 0.000233 * s1 + s3 + 0.001964 * s2;
  ms -= 0.001778 * s1;
  md = md + 0.000817 * s1 + s3 + 0.002541 * s2;
  mf = mf + s3 - 0.024691 * s2 - 0.004328 * s4;
  me1 = me1 + 0.002011 * s1 + s3 + 0.001964 * s2;
  double e = 1.0 - (0.002495 + 0.00000752 * t) * t;
  double e2 = e * e;
  ml = DegreesToRadians(ml);
  ms = DegreesToRadians(ms);
  na = DegreesToRadians(na);
  me1 = DegreesToRadians(me1);
  mf = DegreesToRadians(mf);
  md = DegreesToRadians(md);

  // Longitude-specific
  double l = 6.28875 * sin(md) + 1.274018 * sin(2.0 * me1 - md);
  l = l + 0.658309 * sin(2.0 * me1) + 0.213616 * sin(2.0 * md);
  l = l - e * 0.185596 * sin(ms) - 0.114336 * sin(2.0 * mf);
  l += 0.058793 * sin(2.0 * (me1 - md));
  l = l + 0.057212 * e * sin(2.0 * me1 - ms - md) +
      0.05332 * sin(2.0 * me1 + md);
  l = l + 0.045874 * e * sin(2.0 * me1 - ms) + 0.041024 * e * sin(md - ms);
  l = l - 0.034718 * sin(me1) - e * 0.030465 * sin(ms + md);
  l = l + 0.015326 * sin(2.0 * (me1 - mf)) - 0.012528 * sin(2.0 * mf + md);
  l = l - 0.01098 * sin(2.0 * mf - md) + 0.010674 * sin(4.0 * me1 - md);
  l = l + 0.010034 * sin(3.0 * md) + 0.008548 * sin(4.0 * me1 - 2.0 * md);
  l = l - e * 0.00791 * sin(ms - md + 2.0 * me1) -
      e * 0.006783 * sin(2.0 * me1 + ms);
  l = l + 0.005162 * sin(md - me1) + e * 0.005 * sin(ms + me1);
  l = l + 0.003862 * sin(4.0 * me1) + e * 0.004049 * sin(md - ms + 2.0 * me1);
  l = l + 0.003996 * sin(2.0 * (md + me1)) +
      0.003665 * sin(2.0 * me1 - 3.0 * md);
  l = l + e * 0.002695 * sin(2.0 * md - ms) +
      0.002602 * sin(md - 2.0 * (mf + me1));
  l = l + e * 0.002396 * sin(2.0 * (me1 - md) - ms) - 0.002349 * sin(md + me1);
  l = l + e2 * 0.002249 * sin(2.0 * (me1 - ms)) -
      e * 0.002125 * sin(2.0 * md + ms);
  l = l - e2 * 0.002079 * sin(2.0 * ms) +
      e2 * 0.002059 * sin(2.0 * (me1 - ms) - md);
  l = l - 0.001773 * sin(md + 2.0 * (me1 - mf)) -
      0.001595 * sin(2.0 * (mf + me1));
  l = l + e * 0.00122 * sin(4.0 * me1 - ms - md) -
      0.00111 * sin(2.0 * (md + mf));
  l = l + 0.000892 * sin(md - 3.0 * me1) -
      e * 0.000811 * sin(ms + md + 2.0 * me1);
  l += e * 0.000761 * sin(4.0 * me1 - ms - 2.0 * md);
  l += e2 * 0.000704 * sin(md - 2.0 * (ms + me1));
  l += e * 0.000693 * sin(ms - 2.0 * (md - me1));
  l += e * 0.000598 * sin(2.0 * (me1 - mf) - ms);
  l = l + 0.00055 * sin(md + 4.0 * me1) + 0.000538 * sin(4.0 * md);
  l = l + e * 0.000521 * sin(4.0 * me1 - ms) + 0.000486 * sin(2.0 * md - me1);
  l += e2 * 0.000717 * sin(md - 2.0 * ms);
  double mm = Unwind(ml + DegreesToRadians(l));

  // Latitude-specific
  double g = 5.128189 * sin(mf) + 0.280606 * sin(md + mf);
  g = g + 0.277693 * sin(md - mf) + 0.173238 * sin(2.0 * me1 - mf);
  g = g + 0.055413 * sin(2.0 * me1 + mf - md) +
      0.046272 * sin(2.0 * me1 - mf - md);
  g = g + 0.032573 * sin(2.0 * me1 + mf) + 0.017198 * sin(2.0 * md + mf);
  g = g + 0.009267 * sin(2.0 * me1 + md - mf) + 0.008823 * sin(2.0 * md - mf);
  g = g + e * 0.008247 * sin(2.0 * me1 - ms - mf) +
      0.004323 * sin(2.0 * (me1 - md) - mf);
  g = g + 0.0042 * sin(2.0 * me1 + mf + md) +
      e * 0.003372 * sin(mf - ms - 2.0 * me1);
  g += e * 0.002472 * sin(2.0 * me1 + mf - ms - md);
  g += e * 0.002222 * sin(2.0 * me1 + mf - ms);
  g += e * 0.002072 * sin(2.0 * me1 - mf - ms - md);
  g = g + e * 0.001877 * sin(mf - ms + md) +
      0.001828 * sin(4.0 * me1 - mf - md);
  g = g - e * 0.001803 * sin(mf + ms) - 0.00175 * sin(3.0 * mf);
  g = g + e * 0.00157 * sin(md - ms - mf) - 0.001487 * sin(mf + me1);
  g = g - e * 0.001481 * sin(mf + ms + md) + e * 0.001417 * sin(mf - ms - md);
  g = g + e * 0.00135 * sin(mf - ms) + 0.00133 * sin(mf - me1);
  g = g + 0.001106 * sin(mf + 3.0 * md) + 0.00102 * sin(4.0 * me1 - mf);
  g = g + 0.000833 * sin(mf + 4.0 * me1 - md) + 0.000781 * sin(md - 3.0 * mf);
  g = g + 0.00067 * sin(mf + 4.0 * me1 - 2.0 * md) +
      0.000606 * sin(2.0 * me1 - 3.0 * mf);
  g += 0.000597 * sin(2.0 * (me1 + md) - mf);
  g = g + e * 0.000492 * sin(2.0 * me1 + md - ms - mf) +
      0.00045 * sin(2.0 * (md - me1) - mf);
  g = g + 0.000439 * sin(3.0 * md - mf) + 0.000423 * sin(mf + 2.0 * (me1 + md));
  g = g + 0.000422 * sin(2.0 * me1 - mf - 3.0 * md) -
      e * 0.000367 * sin(ms + mf + 2.0 * me1 - md);
  g = g - e * 0.000353 * sin(ms + mf + 2.0 * me1) +
      0.000331 * sin(mf + 4.0 * me1);
  g += e * 0.000317 * sin(2.0 * me1 + mf - ms + md);
  g = g + e2 * 0.000306 * sin(2.0 * (me1 - ms) - mf) -
      0.000283 * sin(md + 3.0 * mf);
  double w1 = 0.0004664 * cos(na);
  double w2 = 0.0000754 * cos(c);
  double bm = DegreesToRadians(g) * (1.0 - w1 - w2);

  // Horizontal parallax-specific
  double pm = 0.950724 + 0.051818 * cos(md) + 0.009531 * cos(2.0 * me1 - md);
  pm = pm + 0.007843 * cos(2.0 * me1) + 0.002824 * cos(2.0 * md);
  pm = pm + 0.000857 * cos(2.0 * me1 + md) + e * 0.000533 * cos(2.0 * me1 - ms);
  pm += e * 0.000401 * cos(2.0 * me1 - md - ms);
  pm = pm + e * 0.00032 * cos(md - ms) - 0.000271 * cos(me1);
  pm = pm - e * 0.000264 * cos(ms + md) - 0.000198 * cos(2.0 * mf - md);
  pm = pm + 0.000173 * cos(3.0 * md) + 0.000167 * cos(4.0 * me1 - md);
  pm = pm - e * 0.000111 * cos(ms) + 0.000103 * cos(4.0 * me1 - 2.0 * md);
  pm = pm - 0.000084 * cos(2.0 * md - 2.0 * me1) -
       e * 0.000083 * cos(2.0 * me1 + ms);
  pm = pm + 0.000079 * cos(2.0 * me1 + 2.0 * md) + 0.000072 * cos(4.0 * me1);
  pm = pm + e * 0.000064 * cos(2.0 * me1 - ms + md) -
       e * 0.000063 * cos(2.0 * me1 + ms - md);
  pm = pm + e * 0.000041 * cos(ms + me1) + e * 0.000035 * cos(2.0 * md - ms);
  pm = pm - 0.000033 * cos(3.0 * md - 2.0 * me1) - 0.00003 * cos(md + me1);
  pm =
      pm - 0.000029 * cos(2.0 * (mf - me1)) - e * 0.000029 * cos(2.0 * md + ms);
  pm = pm + e2 * 0.000026 * cos(2.0 * (me1 - ms)) -
       0.000023 * cos(2.0 * (mf - me1) + md);
  pm += e * 0.000019 * cos(4.0 * me1 - ms - md);

  double moonLongDeg = WToDegrees(mm);
  double moonLatDeg = WToDegrees(bm);
  double moonHorPara = pm;

  return pa_models::CMoonLongLatHP(moonLongDeg, moonLatDeg, moonHorPara);
}

/**
 * Calculate current phase of Moon.
 *
 * Original macro name: MoonPhase
 */
double MoonPhase(double lh, double lm, double ls, int ds, int zc, double dy,
                 int mn, int yr) {
  pa_models::CMoonLongLatHP moonResult =
      MoonLongLatHP(lh, lm, ls, ds, zc, dy, mn, yr);

  double cd = cos(DegreesToRadians(moonResult.longitudeDegrees -
                                   SunLong(lh, lm, ls, ds, zc, dy, mn, yr))) *
              cos(DegreesToRadians(moonResult.latitudeDegrees));
  double d = acos(cd);
  double sd = sin(d);
  double i =
      0.1468 * sd *
      (1.0 - 0.0549 * sin(MoonMeanAnomaly(lh, lm, ls, ds, zc, dy, mn, yr)));
  i /= (1.0 - 0.0167 * sin(SunMeanAnomaly(lh, lm, ls, ds, zc, dy, mn, yr)));
  i = 3.141592654 - d - DegreesToRadians(i);
  double k = (1.0 + cos(i)) / 2.0;

  return Round(k, 2);
}

/**
 * Calculate the Moon's mean anomaly.
 *
 * Original macro name: MoonMeanAnomaly
 */
double MoonMeanAnomaly(double lh, double lm, double ls, int ds, int zc,
                       double dy, int mn, int yr) {
  double ut = LocalCivilTimeToUniversalTime(lh, lm, ls, ds, zc, dy, mn, yr);
  double gd = LocalCivilTimeGreenwichDay(lh, lm, ls, ds, zc, dy, mn, yr);
  int gm = LocalCivilTimeGreenwichMonth(lh, lm, ls, ds, zc, dy, mn, yr);
  int gy = LocalCivilTimeGreenwichYear(lh, lm, ls, ds, zc, dy, mn, yr);
  double t = ((CivilDateToJulianDate(gd, gm, gy) - 2415020.0) / 36525.0) +
             (ut / 876600.0);
  double t2 = t * t;

  double m1 = 27.32158213;
  double m2 = 365.2596407;
  double m3 = 27.55455094;
  double m4 = 29.53058868;
  double m5 = 27.21222039;
  double m6 = 6798.363307;
  double q = CivilDateToJulianDate(gd, gm, gy) - 2415020.0 + (ut / 24.0);
  m1 = q / m1;
  m2 = q / m2;
  m3 = q / m3;
  m4 = q / m4;
  m5 = q / m5;
  m6 = q / m6;
  m1 = 360.0 * (m1 - floor(m1));
  m2 = 360.0 * (m2 - floor(m2));
  m3 = 360.0 * (m3 - floor(m3));
  m4 = 360.0 * (m4 - floor(m4));
  m5 = 360.0 * (m5 - floor(m5));
  m6 = 360.0 * (m6 - floor(m6));

  double ml = 270.434164 + m1 - (0.001133 - 0.0000019 * t) * t2;
  double ms = 358.475833 + m2 - (0.00015 + 0.0000033 * t) * t2;
  double md = 296.104608 + m3 + (0.009192 + 0.0000144 * t) * t2;
  double na = 259.183275 - m6 + (0.002078 + 0.0000022 * t) * t2;
  double a = DegreesToRadians(51.2 + 20.2 * t);
  double s1 = sin(a);
  double s2 = sin(DegreesToRadians(na));
  double b = 346.56 + (132.87 - 0.0091731 * t) * t;
  double s3 = 0.003964 * sin(DegreesToRadians(b));
  double c = DegreesToRadians(na + 275.05 - 2.3 * t);
  md = md + 0.000817 * s1 + s3 + 0.002541 * s2;

  return DegreesToRadians(md);
}

/**
 * Calculate Julian date of New Moon.
 *
 * Original macro name: NewMoon
 */
double NewMoon(int ds, int zc, double dy, int mn, int yr) {
  double d0 = LocalCivilTimeGreenwichDay(12.0, 0.0, 0.0, ds, zc, dy, mn, yr);
  int m0 = LocalCivilTimeGreenwichMonth(12.0, 0.0, 0.0, ds, zc, dy, mn, yr);
  int y0 = LocalCivilTimeGreenwichYear(12.0, 0.0, 0.0, ds, zc, dy, mn, yr);

  double j0 = CivilDateToJulianDate(0.0, 1, y0) - 2415020.0;
  double dj = CivilDateToJulianDate(d0, m0, y0) - 2415020.0;
  double k = Lint(((y0 - 1900.0 + ((dj - j0) / 365.0)) * 12.3685) + 0.5);
  double tn = k / 1236.85;
  double tf = (k + 0.5) / 1236.85;
  double t = tn;
  pa_models::CNewMoonFullMoonL6855 nmfm_result1 = NewMoonFullMoonL6855(k, t);
  double ni = nmfm_result1.a;
  double nf = nmfm_result1.b;
  t = tf;
  k += 0.5;
  pa_models::CNewMoonFullMoonL6855 nmfm_result2 = NewMoonFullMoonL6855(k, t);

  return ni + 2415020.0 + nf;
}

/**
 * Calculate Julian date of Full Moon.
 *
 * Original macro name: FullMoon
 */
double FullMoon(int ds, int zc, double dy, int mn, int yr) {
  double d0 = LocalCivilTimeGreenwichDay(12.0, 0.0, 0.0, ds, zc, dy, mn, yr);
  int m0 = LocalCivilTimeGreenwichMonth(12.0, 0.0, 0.0, ds, zc, dy, mn, yr);
  int y0 = LocalCivilTimeGreenwichYear(12.0, 0.0, 0.0, ds, zc, dy, mn, yr);

  double j0 = CivilDateToJulianDate(0.0, 1, y0) - 2415020.0;
  double dj = CivilDateToJulianDate(d0, m0, y0) - 2415020.0;
  double k = Lint(((y0 - 1900.0 + ((dj - j0) / 365.0)) * 12.3685) + 0.5);
  double tn = k / 1236.85;
  double tf = (k + 0.5) / 1236.85;
  double t = tn;
  pa_models::CNewMoonFullMoonL6855 nmfm_result1 = NewMoonFullMoonL6855(k, t);
  t = tf;
  k += 0.5;
  pa_models::CNewMoonFullMoonL6855 nmfm_result2 = NewMoonFullMoonL6855(k, t);
  double fi = nmfm_result2.a;
  double ff = nmfm_result2.b;

  return fi + 2415020.0 + ff;
}

/**
 * Helper function for NewMoon() and FullMoon()
 */
pa_models::CNewMoonFullMoonL6855 NewMoonFullMoonL6855(double k, double t) {
  double t2 = t * t;
  double e = 29.53 * k;
  double c = 166.56 + (132.87 - 0.009173 * t) * t;
  c = DegreesToRadians(c);
  double b = 0.00058868 * k + (0.0001178 - 0.000000155 * t) * t2;
  b = b + 0.00033 * sin(c) + 0.75933;
  double a = k / 12.36886;
  double a1 = 359.2242 + 360.0 * Fract(a) - (0.0000333 + 0.00000347 * t) * t2;
  double a2 = 306.0253 + 360.0 * Fract(k / 0.9330851);
  a2 += (0.0107306 + 0.00001236 * t) * t2;
  a = k / 0.9214926;
  double f = 21.2964 + 360.0 * Fract(a) - (0.0016528 + 0.00000239 * t) * t2;
  a1 = UnwindDeg(a1);
  a2 = UnwindDeg(a2);
  f = UnwindDeg(f);
  a1 = DegreesToRadians(a1);
  a2 = DegreesToRadians(a2);
  f = DegreesToRadians(f);

  double dd = (0.1734 - 0.000393 * t) * sin(a1) + 0.0021 * sin(2.0 * a1);
  dd = dd - 0.4068 * sin(a2) + 0.0161 * sin(2.0 * a2) - 0.0004 * sin(3.0 * a2);
  dd = dd + 0.0104 * sin(2.0 * f) - 0.0051 * sin(a1 + a2);
  dd = dd - 0.0074 * sin(a1 - a2) + 0.0004 * sin(2.0 * f + a1);
  dd = dd - 0.0004 * sin(2.0 * f - a1) - 0.0006 * sin(2.0 * f + a2) +
       0.001 * sin(2.0 * f - a2);
  dd += 0.0005 * sin(a1 + 2.0 * a2);
  double e1 = floor(e);
  b = b + dd + (e - e1);
  double b1 = floor(b);
  a = e1 + b1;
  b -= b1;

  return pa_models::CNewMoonFullMoonL6855(a, b, f);
}

/**
 * Original macro name: FRACT
 */
double Fract(double w) { return w - Lint(w); }

/**
 * Original macro name: LINT
 */
double Lint(double w) { return IInt(w) + IInt(((1.0 * Sign(w)) - 1.0) / 2.0); }

/**
 * Original macro name: IINT
 */
double IInt(double w) { return Sign(w) * floor(fabs(w)); }

/**
 * Calculate sign of number.
 */
double Sign(double number_to_check) {
  double sign_value = 0.0;

  if (number_to_check < 0.0)
    sign_value = -1.0;

  if (number_to_check > 0.0)
    sign_value = 1.0;

  return sign_value;
}

} // namespace pa_macros
