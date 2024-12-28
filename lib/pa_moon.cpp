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
PAMoon::PrecisePositionOfMoon(double lctHour, double lctMin, double lctSec,
                              bool isDaylightSaving, int zoneCorrectionHours,
                              double localDateDay, int localDateMonth,
                              int localDateYear) {
  int daylightSaving = isDaylightSaving ? 1 : 0;

  double gdateDay = LocalCivilTimeGreenwichDay(
      lctHour, lctMin, lctSec, daylightSaving, zoneCorrectionHours,
      localDateDay, localDateMonth, localDateYear);
  int gdateMonth = LocalCivilTimeGreenwichMonth(
      lctHour, lctMin, lctSec, daylightSaving, zoneCorrectionHours,
      localDateDay, localDateMonth, localDateYear);
  int gdateYear = LocalCivilTimeGreenwichYear(
      lctHour, lctMin, lctSec, daylightSaving, zoneCorrectionHours,
      localDateDay, localDateMonth, localDateYear);

  CMoonLongLatHP moonResult = MoonLongLatHP(
      lctHour, lctMin, lctSec, daylightSaving, zoneCorrectionHours,
      localDateDay, localDateMonth, localDateYear);

  double nutationInLongitudeDeg = NutatLong(gdateDay, gdateMonth, gdateYear);
  double correctedLongDeg =
      moonResult.longitudeDegrees + nutationInLongitudeDeg;
  double earthMoonDistanceKM =
      6378.14 / sin(DegreesToRadians(moonResult.horizontalParallax));
  double moonRAHours1 = DecimalDegreesToDegreeHours(
      EclipticRightAscension(correctedLongDeg, 0, 0, moonResult.latitudeDegrees,
                             0, 0, gdateDay, gdateMonth, gdateYear));
  double moonDecDeg1 =
      EclipticDeclination(correctedLongDeg, 0, 0, moonResult.latitudeDegrees, 0,
                          0, gdateDay, gdateMonth, gdateYear);

  int moonRAHour = DecimalHoursHour(moonRAHours1);
  int moonRAMin = DecimalHoursMinute(moonRAHours1);
  double moonRASec = DecimalHoursSecond(moonRAHours1);
  double moonDecDeg = DecimalDegreesDegrees(moonDecDeg1);
  double moonDecMin = DecimalDegreesMinutes(moonDecDeg1);
  double moonDecSec = DecimalDegreesSeconds(moonDecDeg1);
  double earthMoonDistKM = Round(earthMoonDistanceKM, 0);
  double moonHorParallaxDeg = Round(moonResult.horizontalParallax, 6);

  return CMoonPrecisePosition(moonRAHour, moonRAMin, moonRASec, moonDecDeg,
                              moonDecMin, moonDecSec, earthMoonDistKM,
                              moonHorParallaxDeg);
}

/**
 * Calculate Moon phase and position angle of bright limb.
 */
CMoonPhase PAMoon::MoonPhase(double lctHour, double lctMin, double lctSec,
                             bool isDaylightSaving, int zoneCorrectionHours,
                             double localDateDay, int localDateMonth,
                             int localDateYear, EAccuracyLevel accuracyLevel) {
  int daylightSaving = isDaylightSaving ? 1 : 0;

  double gdateDay = LocalCivilTimeGreenwichDay(
      lctHour, lctMin, lctSec, daylightSaving, zoneCorrectionHours,
      localDateDay, localDateMonth, localDateYear);
  int gdateMonth = LocalCivilTimeGreenwichMonth(
      lctHour, lctMin, lctSec, daylightSaving, zoneCorrectionHours,
      localDateDay, localDateMonth, localDateYear);
  int gdateYear = LocalCivilTimeGreenwichYear(
      lctHour, lctMin, lctSec, daylightSaving, zoneCorrectionHours,
      localDateDay, localDateMonth, localDateYear);

  double sunLongDeg =
      SunLong(lctHour, lctMin, lctSec, daylightSaving, zoneCorrectionHours,
              localDateDay, localDateMonth, localDateYear);
  CMoonLongLatHP moonResult = MoonLongLatHP(
      lctHour, lctMin, lctSec, daylightSaving, zoneCorrectionHours,
      localDateDay, localDateMonth, localDateYear);
  double dRad = DegreesToRadians(moonResult.longitudeDegrees - sunLongDeg);

  double moonPhase1 =
      (accuracyLevel == EAccuracyLevel::Precise)
          ? pa_macros::MoonPhase(lctHour, lctMin, lctSec, daylightSaving,
                                 zoneCorrectionHours, localDateDay,
                                 localDateMonth, localDateYear)
          : (1.0 - cos(dRad)) / 2.0;

  double sunRARad = DegreesToRadians(EclipticRightAscension(
      sunLongDeg, 0, 0, 0, 0, 0, gdateDay, gdateMonth, gdateYear));
  double moonRARad = DegreesToRadians(EclipticRightAscension(
      moonResult.longitudeDegrees, 0, 0, moonResult.latitudeDegrees, 0, 0,
      gdateDay, gdateMonth, gdateYear));
  double sunDecRad = DegreesToRadians(EclipticDeclination(
      sunLongDeg, 0, 0, 0, 0, 0, gdateDay, gdateMonth, gdateYear));
  double moonDecRad = DegreesToRadians(EclipticDeclination(
      moonResult.longitudeDegrees, 0, 0, moonResult.latitudeDegrees, 0, 0,
      gdateDay, gdateMonth, gdateYear));

  double y = cos(sunDecRad) * sin(sunRARad - moonRARad);
  double x = cos(moonDecRad) * sin(sunDecRad) -
             sin(moonDecRad) * cos(sunDecRad) * cos(sunRARad - moonRARad);

  double chiDeg = WToDegrees(atan2(y, x));

  double moonPhase = Round(moonPhase1, 2);
  double brightLimbDeg = Round(chiDeg, 2);

  return CMoonPhase(moonPhase, brightLimbDeg);
}

/**
 * Calculate new moon and full moon instances.
 */
CMoonNewFull PAMoon::TimesOfNewMoonAndFullMoon(bool isDaylightSaving,
                                               int zoneCorrectionHours,
                                               double localDateDay,
                                               int localDateMonth,
                                               int localDateYear) {
  int daylightSaving = isDaylightSaving ? 1 : 0;

  double jdOfNewMoonDays = NewMoon(daylightSaving, zoneCorrectionHours,
                                   localDateDay, localDateMonth, localDateYear);
  double jdOfFullMoonDays = FullMoon(3, zoneCorrectionHours, localDateDay,
                                     localDateMonth, localDateYear);

  double gDateOfNewMoonDay = JulianDateDay(jdOfNewMoonDays);
  double integerDay1 = floor(gDateOfNewMoonDay);
  int gDateOfNewMoonMonth = JulianDateMonth(jdOfNewMoonDays);
  int gDateOfNewMoonYear = JulianDateYear(jdOfNewMoonDays);

  double gDateOfFullMoonDay = JulianDateDay(jdOfFullMoonDays);
  double integerDay2 = floor(gDateOfFullMoonDay);
  int gDateOfFullMoonMonth = JulianDateMonth(jdOfFullMoonDays);
  int gDateOfFullMoonYear = JulianDateYear(jdOfFullMoonDays);

  double utOfNewMoonHours = 24.0 * (gDateOfNewMoonDay - integerDay1);
  double utOfFullMoonHours = 24.0 * (gDateOfFullMoonDay - integerDay2);
  double lctOfNewMoonHours = UniversalTimeToLocalCivilTime(
      utOfNewMoonHours + 0.008333, 0, 0, daylightSaving, zoneCorrectionHours,
      integerDay1, gDateOfNewMoonMonth, gDateOfNewMoonYear);
  double lctOfFullMoonHours = UniversalTimeToLocalCivilTime(
      utOfFullMoonHours + 0.008333, 0, 0, daylightSaving, zoneCorrectionHours,
      integerDay2, gDateOfFullMoonMonth, gDateOfFullMoonYear);

  int nmLTH = DecimalHoursHour(lctOfNewMoonHours);
  int nmLTM = DecimalHoursMinute(lctOfNewMoonHours);
  double nmLDD = UniversalTimeLocalCivilDay(
      utOfNewMoonHours, 0, 0, daylightSaving, zoneCorrectionHours, integerDay1,
      gDateOfNewMoonMonth, gDateOfNewMoonYear);
  int nmLDM = UniversalTimeLocalCivilMonth(
      utOfNewMoonHours, 0, 0, daylightSaving, zoneCorrectionHours, integerDay1,
      gDateOfNewMoonMonth, gDateOfNewMoonYear);
  int nmLDY = UniversalTimeLocalCivilYear(
      utOfNewMoonHours, 0, 0, daylightSaving, zoneCorrectionHours, integerDay1,
      gDateOfNewMoonMonth, gDateOfNewMoonYear);
  int fmLTH = DecimalHoursHour(lctOfFullMoonHours);
  int fmLTM = DecimalHoursMinute(lctOfFullMoonHours);
  double fmLDD = UniversalTimeLocalCivilDay(
      utOfFullMoonHours, 0, 0, daylightSaving, zoneCorrectionHours, integerDay2,
      gDateOfFullMoonMonth, gDateOfFullMoonYear);
  int fmLDM = UniversalTimeLocalCivilMonth(
      utOfFullMoonHours, 0, 0, daylightSaving, zoneCorrectionHours, integerDay2,
      gDateOfFullMoonMonth, gDateOfFullMoonYear);
  int fmLDY = UniversalTimeLocalCivilYear(
      utOfFullMoonHours, 0, 0, daylightSaving, zoneCorrectionHours, integerDay2,
      gDateOfFullMoonMonth, gDateOfFullMoonYear);

  return CMoonNewFull(nmLTH, nmLTM, nmLDD, nmLDM, nmLDY, fmLTH, fmLTM, fmLDD,
                      fmLDM, fmLDY);
}

/**
 * Calculate Moon's distance, angular diameter, and horizontal parallax.
 */
CMoonDistDiameterHP
PAMoon::MoonDistAngDiamHorParallax(double lctHour, double lctMin, double lctSec,
                                   bool isDaylightSaving,
                                   int zoneCorrectionHours, double localDateDay,
                                   int localDateMonth, int localDateYear) {
  int daylightSaving = isDaylightSaving ? 1 : 0;

  double moonDistance =
      MoonDist(lctHour, lctMin, lctSec, daylightSaving, zoneCorrectionHours,
               localDateDay, localDateMonth, localDateYear);
  double moonAngularDiameter =
      MoonSize(lctHour, lctMin, lctSec, daylightSaving, zoneCorrectionHours,
               localDateDay, localDateMonth, localDateYear);
  double moonHorizontalParallax = MoonHorizontalParallax(
      lctHour, lctMin, lctSec, daylightSaving, zoneCorrectionHours,
      localDateDay, localDateMonth, localDateYear);

  double earthMoonDist = Round(moonDistance, 0);
  double angDiameterDeg = DecimalDegreesDegrees(moonAngularDiameter + 0.008333);
  double angDiameterMin = DecimalDegreesMinutes(moonAngularDiameter + 0.008333);
  double horParallaxDeg = DecimalDegreesDegrees(moonHorizontalParallax);
  double horParallaxMin = DecimalDegreesMinutes(moonHorizontalParallax);
  double horParallaxSec = DecimalDegreesSeconds(moonHorizontalParallax);

  return CMoonDistDiameterHP(earthMoonDist, angDiameterDeg, angDiameterMin,
                             horParallaxDeg, horParallaxMin, horParallaxSec);
}
