#include "pa_datetime.h"
#include "pa_macros.h"
#include "pa_models.h"
#include "pa_types.h"
#include "pa_util.h"
#include <cmath>

using namespace pa_types;
using namespace pa_util;
using namespace pa_macros;
using namespace pa_models;

/**
 * \brief Gets the date of Easter for the year specified.
 *
 * @param input_year Input year.
 *
 * @return CMonthDayYear
 */
CMonthDayYear PADateTime::GetDateOfEaster(int inputYear) {
  double year = (double)inputYear;

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

  return CMonthDayYear(month, day, year);
}

/**
 * \brief Calculate day number for a date.
 *
 * @param month Month part of date.
 * @param day Day part of date.
 * @param year Year part of date.
 *
 * @return Day number.
 */
int PADateTime::CivilDateToDayNumber(int month, int day, int year) {
  if (month <= 2) {
    month--;
    month = (IsLeapYear(year) == true) ? month * 62 : month * 63;
    month = (int)floor((double)month / 2.0);
  } else {
    month = (int)floor(((double)month + 1.0) * 30.6);
    month = (IsLeapYear(year) == true) ? month - 62 : month - 63;
  }

  return month + day;
}

/**
 * \brief Convert a Civil Time to Decimal Hours
 *
 * @param hours Hour part of HH:MM:SS
 * @param minutes Minutes part of HH:MM:SS
 * @param seconds Seconds part of HH:MM:SS
 *
 * @return Decimal hours.
 */
double PADateTime::CivilTimeToDecimalHours(double hours, double minutes,
                                           double seconds) {
  return HmsToDh(hours, minutes, seconds);
}

/**
 * \brief Convert Decimal Hours to Civil Time
 *
 * @param decimal_hours Time as a decimal, e.g., 8.5 for 08:30:00
 *
 * @return CCivilTime
 */
CCivilTime PADateTime::DecimalHoursToCivilTime(double decimalHours) {
  int hours = DecimalHoursHour(decimalHours);
  int minutes = DecimalHoursMinute(decimalHours);
  double seconds = DecimalHoursSecond(decimalHours);

  return CCivilTime(hours, minutes, seconds);
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
 * @return CUniversalTime
 */
CUniversalDateTime PADateTime::LocalCivilTimeToUniversalTime(
    double lctHours, double lctMinutes, double lctSeconds,
    bool isDaylightSavings, int zoneCorrection, double localDay, int localMonth,
    int localYear) {
  double lct = CivilTimeToDecimalHours(lctHours, lctMinutes, lctSeconds);

  int daylightSavingsOffset = (isDaylightSavings) ? 1 : 0;

  double utInterim = lct - daylightSavingsOffset - zoneCorrection;
  double gDayInterim = localDay + (utInterim / 24);

  double jd = CivilDateToJulianDate(gDayInterim, localMonth, localYear);

  double gDay = JulianDateDay(jd);
  int gMonth = JulianDateMonth(jd);
  int gYear = JulianDateYear(jd);

  double ut = 24 * (gDay - floor(gDay));

  return CUniversalDateTime(DecimalHoursHour(ut), DecimalHoursMinute(ut),
                            (int)DecimalHoursSecond(ut), (int)floor(gDay),
                            gMonth, gYear);
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
 * @return CCivilDateTime
 */
CCivilDateTime PADateTime::UniversalTimeToLocalCivilTime(
    double utHours, double utMinutes, double utSeconds, bool isDaylightSavings,
    int zoneCorrection, int gwDay, int gwMonth, int gwYear) {
  int dstValue = (isDaylightSavings) ? 1 : 0;
  double ut = HmsToDh(utHours, utMinutes, utSeconds);
  double zoneTime = ut + zoneCorrection;
  double localTime = zoneTime + dstValue;
  double localJdPlusLocalTime =
      CivilDateToJulianDate(gwDay, gwMonth, gwYear) + (localTime / 24);
  double localDay = JulianDateDay(localJdPlusLocalTime);
  double integerDay = floor(localDay);
  int localMonth = JulianDateMonth(localJdPlusLocalTime);
  int localYear = JulianDateYear(localJdPlusLocalTime);

  double lct = 24 * (localDay - integerDay);

  return CCivilDateTime(DecimalHoursHour(lct), DecimalHoursMinute(lct),
                        (int)DecimalHoursSecond(lct), (int)integerDay,
                        localMonth, localYear);
}

/**
 * \brief Convert Universal Time to Greenwich Sidereal Time
 *
 * @param ut_hours Universal time, hours part.
 * @param ut_minutes Universal time, minutes part.
 * @param ut_seconds Universal time, seconds part.
 * @param gw_day Greenwich date, day part.
 * @param gw_month Greenwich date, month part.
 * @param gw_year Greenwich date, year part.
 *
 * @return CGreenwichSiderealTime
 */
CGreenwichSiderealTime PADateTime::UniversalTimeToGreenwichSiderealTime(
    double utHours, double utMinutes, double utSeconds, double gwDay,
    int gwMonth, int gwYear) {
  double jd = CivilDateToJulianDate(gwDay, gwMonth, gwYear);
  double s = jd - 2451545.0;
  double t = s / 36525.0;
  double t01 = 6.697374558 + (2400.051336 * t) + (0.000025862 * t * t);
  double t02 = t01 - (24.0 * floor(t01 / 24.0));
  double ut = HmsToDh(utHours, utMinutes, utSeconds);
  double a = ut * 1.002737909;
  double gst1 = t02 + a;
  double gst2 = gst1 - (24.0 * floor(gst1 / 24.0));

  int gstHours = DecimalHoursHour(gst2);
  int gstMinutes = DecimalHoursMinute(gst2);
  double gstSeconds = DecimalHoursSecond(gst2);

  return CGreenwichSiderealTime(gstHours, gstMinutes, gstSeconds);
}

/**
 * Convert Greenwich Sidereal Time to Universal Time
 *
 * @param gst_hours Universal time, hours part.
 * @param gst_minutes Universal time, minutes part.
 * @param gst_seconds Universal time, seconds part.
 * @param gw_day Greenwich date, day part.
 * @param gw_month Greenwich date, month part.
 * @param gw_year Greenwich date, year part.
 *
 * @return CUniversalTime2
 */
CUniversalTime PADateTime::GreenwichSiderealTimeToUniversalTime(
    double gstHours, double gstMinutes, double gstSeconds, double gwDay,
    int gwMonth, int gwYear) {
  double jd = CivilDateToJulianDate(gwDay, gwMonth, gwYear);
  double s = jd - 2451545;
  double t = s / 36525;
  double t01 = 6.697374558 + (2400.051336 * t) + (0.000025862 * t * t);
  double t02 = t01 - (24 * floor(t01 / 24));
  double gstHours1 = HmsToDh(gstHours, gstMinutes, gstSeconds);

  double a = gstHours1 - t02;
  double b = a - (24 * floor(a / 24));
  double ut = b * 0.9972695663;
  int utHours = DecimalHoursHour(ut);
  int utMinutes = DecimalHoursMinute(ut);
  double utSeconds = DecimalHoursSecond(ut);

  EWarningFlags warningFlag =
      (ut < 0.065574) ? EWarningFlags::Warning : EWarningFlags::Ok;

  return CUniversalTime(utHours, utMinutes, utSeconds, warningFlag);
}

/**
 * \brief Convert Greenwich Sidereal Time to Local Sidereal Time
 *
 * @param gst_hours Greenwich sidereal time, hours part.
 * @param gst_minutes Greenwich sidereal time, minutes part.
 * @param gst_seconds Greenwich sidereal time, seconds part.
 * @param geographical_longitude Geographical longitude.
 *
 * @return CLocalSiderealTime
 */
CLocalSiderealTime PADateTime::GreenwichSiderealTimeToLocalSiderealTime(
    double gstHours, double gstMinutes, double gstSeconds,
    double geographicalLongitude) {
  double gst = HmsToDh(gstHours, gstMinutes, gstSeconds);
  double offset = geographicalLongitude / 15;
  double lstHours1 = gst + offset;
  double lstHours2 = lstHours1 - (24 * floor(lstHours1 / 24));

  int lstHours = DecimalHoursHour(lstHours2);
  int lstMinutes = DecimalHoursMinute(lstHours2);
  double lstSeconds = DecimalHoursSecond(lstHours2);

  return CLocalSiderealTime(lstHours, lstMinutes, lstSeconds);
}

/**
 * \brief Convert Local Sidereal Time to Greenwich Sidereal Time
 *
 * @param lst_hours Local sidereal time, hours part.
 * @param lst_minutes Local sidereal time, minutes part.
 * @param lst_seconds Local sidereal time, seconds part.
 * @param geographical_longitude Geographical longitude.
 *
 * @return CGreenwichSiderealTime
 */
CGreenwichSiderealTime PADateTime::LocalSiderealTimeToGreenwichSiderealTime(
    double lstHours, double lstMinutes, double lstSeconds,
    double geographicalLongitude) {
  double gst = HmsToDh(lstHours, lstMinutes, lstSeconds);
  double longHours = geographicalLongitude / 15;
  double gst1 = gst - longHours;
  double gst2 = gst1 - (24 * floor(gst1 / 24));

  int gstHours = DecimalHoursHour(gst2);
  int gstMinutes = DecimalHoursMinute(gst2);
  double gstSeconds = DecimalHoursSecond(gst2);

  return CGreenwichSiderealTime(gstHours, gstMinutes, gstSeconds);
}
