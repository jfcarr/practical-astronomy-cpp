#include "pa_moon.h"
#include "pa_data.h"
#include "pa_macros.h"
#include "pa_models.h"
#include "pa_util.h"
#include <cmath>
#include <string>

using namespace pa_types;
using namespace pa_models;
using namespace pa_util;
using namespace pa_macros;

/**
 * Calculate approximate position of the Moon.
 */
CMoonApproximatePosition
PAMoon::ApproximatePositionOfMoon(double lctHour, double lctMin, double lctSec,
                                  bool isDaylightSaving,
                                  int zoneCorrectionHours, double localDateDay,
                                  int localDateMonth, int localDateYear) {
  int daylightSaving = isDaylightSaving ? 1 : 0;

  double l0 = 91.9293359879052;
  double p0 = 130.143076320618;
  double n0 = 291.682546643194;
  double i = 5.145396;

  double gdateDay = LocalCivilTimeGreenwichDay(
      lctHour, lctMin, lctSec, daylightSaving, zoneCorrectionHours,
      localDateDay, localDateMonth, localDateYear);
  int gdateMonth = LocalCivilTimeGreenwichMonth(
      lctHour, lctMin, lctSec, daylightSaving, zoneCorrectionHours,
      localDateDay, localDateMonth, localDateYear);
  int gdateYear = LocalCivilTimeGreenwichYear(
      lctHour, lctMin, lctSec, daylightSaving, zoneCorrectionHours,
      localDateDay, localDateMonth, localDateYear);

  double utHours = LocalCivilTimeToUniversalTime(
      lctHour, lctMin, lctSec, daylightSaving, zoneCorrectionHours,
      localDateDay, localDateMonth, localDateYear);
  double dDays = CivilDateToJulianDate(gdateDay, gdateMonth, gdateYear) -
                 CivilDateToJulianDate(0.0, 1, 2010) + utHours / 24;
  double sunLongDeg =
      SunLong(lctHour, lctMin, lctSec, daylightSaving, zoneCorrectionHours,
              localDateDay, localDateMonth, localDateYear);
  double sunMeanAnomalyRad = SunMeanAnomaly(
      lctHour, lctMin, lctSec, daylightSaving, zoneCorrectionHours,
      localDateDay, localDateMonth, localDateYear);
  double lmDeg = UnwindDeg(13.1763966 * dDays + l0);
  double mmDeg = UnwindDeg(lmDeg - 0.1114041 * dDays - p0);
  double nDeg = UnwindDeg(n0 - (0.0529539 * dDays));
  double evDeg =
      1.2739 * sin(DegreesToRadians(2.0 * (lmDeg - sunLongDeg) - mmDeg));
  double aeDeg = 0.1858 * sin(sunMeanAnomalyRad);
  double a3Deg = 0.37 * sin(sunMeanAnomalyRad);
  double mmdDeg = mmDeg + evDeg - aeDeg - a3Deg;
  double ecDeg = 6.2886 * sin(DegreesToRadians(mmdDeg));
  double a4Deg = 0.214 * sin(2.0 * DegreesToRadians(mmdDeg));
  double ldDeg = lmDeg + evDeg + ecDeg - aeDeg + a4Deg;
  double vDeg = 0.6583 * sin(2.0 * DegreesToRadians(ldDeg - sunLongDeg));
  double lddDeg = ldDeg + vDeg;
  double ndDeg = nDeg - 0.16 * sin(sunMeanAnomalyRad);
  double y = sin(DegreesToRadians(lddDeg - ndDeg)) * cos(DegreesToRadians(i));
  double x = cos(DegreesToRadians(lddDeg - ndDeg));

  double moonLongDeg = UnwindDeg(WToDegrees(atan2(y, x)) + ndDeg);
  double moonLatDeg = WToDegrees(
      asin(sin(DegreesToRadians(lddDeg - ndDeg)) * sin(DegreesToRadians(i))));
  double moonRAHours1 = DecimalDegreesToDegreeHours(EclipticRightAscension(
      moonLongDeg, 0, 0, moonLatDeg, 0, 0, gdateDay, gdateMonth, gdateYear));
  double moonDecDeg1 = EclipticDeclination(moonLongDeg, 0, 0, moonLatDeg, 0, 0,
                                           gdateDay, gdateMonth, gdateYear);

  int moonRAHour = DecimalHoursHour(moonRAHours1);
  int moonRAMin = DecimalHoursMinute(moonRAHours1);
  double moonRASec = DecimalHoursSecond(moonRAHours1);
  double moonDecDeg = DecimalDegreesDegrees(moonDecDeg1);
  double moonDecMin = DecimalDegreesMinutes(moonDecDeg1);
  double moonDecSec = DecimalDegreesSeconds(moonDecDeg1);

  return CMoonApproximatePosition(moonRAHour, moonRAMin, moonRASec, moonDecDeg,
                                  moonDecMin, moonDecSec);
}

/**
 * Calculate precise position of the Moon.
 */
CMoonPrecisePosition
PAMoon::PrecisePositionOfMoon(double lct_hour, double lct_min, double lct_sec,
                              bool is_daylight_saving,
                              int zone_correction_hours, double local_date_day,
                              int local_date_month, int local_date_year) {
  int daylight_saving = is_daylight_saving ? 1 : 0;

  double gdate_day = LocalCivilTimeGreenwichDay(
      lct_hour, lct_min, lct_sec, daylight_saving, zone_correction_hours,
      local_date_day, local_date_month, local_date_year);
  int gdate_month = LocalCivilTimeGreenwichMonth(
      lct_hour, lct_min, lct_sec, daylight_saving, zone_correction_hours,
      local_date_day, local_date_month, local_date_year);
  int gdate_year = LocalCivilTimeGreenwichYear(
      lct_hour, lct_min, lct_sec, daylight_saving, zone_correction_hours,
      local_date_day, local_date_month, local_date_year);

  CMoonLongLatHP moon_result = MoonLongLatHP(
      lct_hour, lct_min, lct_sec, daylight_saving, zone_correction_hours,
      local_date_day, local_date_month, local_date_year);

  double nutation_in_longitude_deg =
      NutatLong(gdate_day, gdate_month, gdate_year);
  double corrected_long_deg =
      moon_result.longitudeDegrees + nutation_in_longitude_deg;
  double earth_moon_distance_km =
      6378.14 / sin(DegreesToRadians(moon_result.horizontalParallax));
  double moon_ra_hours1 = DecimalDegreesToDegreeHours(EclipticRightAscension(
      corrected_long_deg, 0, 0, moon_result.latitudeDegrees, 0, 0, gdate_day,
      gdate_month, gdate_year));
  double moon_dec_deg1 =
      EclipticDeclination(corrected_long_deg, 0, 0, moon_result.latitudeDegrees,
                          0, 0, gdate_day, gdate_month, gdate_year);

  int moon_ra_hour = DecimalHoursHour(moon_ra_hours1);
  int moon_ra_min = DecimalHoursMinute(moon_ra_hours1);
  double moon_ra_sec = DecimalHoursSecond(moon_ra_hours1);
  double moon_dec_deg = DecimalDegreesDegrees(moon_dec_deg1);
  double moon_dec_min = DecimalDegreesMinutes(moon_dec_deg1);
  double moon_dec_sec = DecimalDegreesSeconds(moon_dec_deg1);
  double earth_moon_dist_km = Round(earth_moon_distance_km, 0);
  double moon_hor_parallax_deg = Round(moon_result.horizontalParallax, 6);

  return CMoonPrecisePosition(moon_ra_hour, moon_ra_min, moon_ra_sec,
                              moon_dec_deg, moon_dec_min, moon_dec_sec,
                              earth_moon_dist_km, moon_hor_parallax_deg);
}
