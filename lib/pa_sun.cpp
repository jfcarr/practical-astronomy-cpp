#include "pa_sun.h"
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
 * \brief Calculate approximate position of the sun for a local date and time.
 *
 * @return CApproximatePositionOfSun
 */
CApproximatePositionOfSun PASun::ApproximatePositionOfSun(
    double lctHours, double lctMinutes, double lctSeconds, double localDay,
    int localMonth, int localYear, bool isDaylightSaving, int zoneCorrection) {
  int daylightSaving = (isDaylightSaving == true) ? 1 : 0;

  double greenwichDateDay = LocalCivilTimeGreenwichDay(
      lctHours, lctMinutes, lctSeconds, daylightSaving, zoneCorrection,
      localDay, localMonth, localYear);
  int greenwichDateMonth = LocalCivilTimeGreenwichMonth(
      lctHours, lctMinutes, lctSeconds, daylightSaving, zoneCorrection,
      localDay, localMonth, localYear);
  int greenwichDateYear = LocalCivilTimeGreenwichYear(
      lctHours, lctMinutes, lctSeconds, daylightSaving, zoneCorrection,
      localDay, localMonth, localYear);
  double utHours = LocalCivilTimeToUniversalTime(
      lctHours, lctMinutes, lctSeconds, daylightSaving, zoneCorrection,
      localDay, localMonth, localYear);
  double utDays = utHours / 24;
  double jdDays = CivilDateToJulianDate(greenwichDateDay, greenwichDateMonth,
                                        greenwichDateYear) +
                  utDays;
  double dDays = jdDays - CivilDateToJulianDate(0, 1, 2010);
  double nDeg = 360 * dDays / 365.242191;
  double mDeg1 = nDeg + SunELong(0, 1, 2010) - SunPerigee(0, 1, 2010);
  double mDeg2 = mDeg1 - 360 * floor(mDeg1 / 360);
  double eCDeg =
      360 * SunEccentricity(0, 1, 2010) * sin(DegreesToRadians(mDeg2)) / M_PI;
  double lSDeg1 = nDeg + eCDeg + SunELong(0, 1, 2010);
  double lSDeg2 = lSDeg1 - 360 * floor(lSDeg1 / 360);
  double raDeg =
      pa_macros::EclipticRightAscension(lSDeg2, 0, 0, 0, 0, 0, greenwichDateDay,
                                        greenwichDateMonth, greenwichDateYear);
  double raHours = DecimalDegreesToDegreeHours(raDeg);
  double decDeg =
      pa_macros::EclipticDeclination(lSDeg2, 0, 0, 0, 0, 0, greenwichDateDay,
                                     greenwichDateMonth, greenwichDateYear);

  int sunRaHour = DecimalHoursHour(raHours);
  int sunRaMin = DecimalHoursMinute(raHours);
  double sunRaSec = DecimalHoursSecond(raHours);
  double sunDecDeg = DecimalDegreesDegrees(decDeg);
  double sunDecMin = DecimalDegreesMinutes(decDeg);
  double sunDecSec = DecimalDegreesSeconds(decDeg);

  return CApproximatePositionOfSun(sunRaHour, sunRaMin, sunRaSec, sunDecDeg,
                                   sunDecMin, sunDecSec);
}

/**
 * \brief Calculate precise position of the sun for a local date and time.
 */
CPrecisePositionOfSun PASun::PrecisePositionOfSun(
    double lctHours, double lctMinutes, double lctSeconds, double localDay,
    int localMonth, int localYear, bool isDaylightSaving, int zoneCorrection) {
  int daylightSaving = (isDaylightSaving == true) ? 1 : 0;

  double gDay = LocalCivilTimeGreenwichDay(lctHours, lctMinutes, lctSeconds,
                                           daylightSaving, zoneCorrection,
                                           localDay, localMonth, localYear);
  int gMonth = LocalCivilTimeGreenwichMonth(lctHours, lctMinutes, lctSeconds,
                                            daylightSaving, zoneCorrection,
                                            localDay, localMonth, localYear);
  int gYear = LocalCivilTimeGreenwichYear(lctHours, lctMinutes, lctSeconds,
                                          daylightSaving, zoneCorrection,
                                          localDay, localMonth, localYear);
  double sunEclipticLongitudeDeg =
      SunLong(lctHours, lctMinutes, lctSeconds, daylightSaving, zoneCorrection,
              localDay, localMonth, localYear);
  double raDeg = EclipticRightAscension(sunEclipticLongitudeDeg, 0, 0, 0, 0, 0,
                                        gDay, gMonth, gYear);
  double raHours = DecimalDegreesToDegreeHours(raDeg);
  double decDeg = EclipticDeclination(sunEclipticLongitudeDeg, 0, 0, 0, 0, 0,
                                      gDay, gMonth, gYear);

  int sunRaHour = DecimalHoursHour(raHours);
  int sunRaMin = DecimalHoursMinute(raHours);
  double sunRaSec = DecimalHoursSecond(raHours);
  double sunDecDeg = DecimalDegreesDegrees(decDeg);
  double sunDecMin = DecimalDegreesMinutes(decDeg);
  double sunDecSec = DecimalDegreesSeconds(decDeg);

  return CPrecisePositionOfSun(sunRaHour, sunRaMin, sunRaSec, sunDecDeg,
                               sunDecMin, sunDecSec);
}

/**
 * \brief Calculate distance to the Sun (in km), and angular size.
 *
 * @return CSunDistanceAngularSize
 */
CSunDistanceAngularSize PASun::SunDistanceAndAngularSize(
    double lctHours, double lctMinutes, double lctSeconds, double localDay,
    int localMonth, int localYear, bool isDaylightSaving, int zoneCorrection) {
  int daylightSaving = (isDaylightSaving) ? 1 : 0;

  double gDay = LocalCivilTimeGreenwichDay(lctHours, lctMinutes, lctSeconds,
                                           daylightSaving, zoneCorrection,
                                           localDay, localMonth, localYear);
  int gMonth = LocalCivilTimeGreenwichMonth(lctHours, lctMinutes, lctSeconds,
                                            daylightSaving, zoneCorrection,
                                            localDay, localMonth, localYear);
  int gYear = LocalCivilTimeGreenwichYear(lctHours, lctMinutes, lctSeconds,
                                          daylightSaving, zoneCorrection,
                                          localDay, localMonth, localYear);
  double trueAnomalyDeg =
      SunTrueAnomaly(lctHours, lctMinutes, lctSeconds, daylightSaving,
                     zoneCorrection, localDay, localMonth, localYear);
  double trueAnomalyRad = DegreesToRadians(trueAnomalyDeg);
  double eccentricity = SunEccentricity(gDay, gMonth, gYear);
  double f = (1 + eccentricity * cos(trueAnomalyRad)) /
             (1 - eccentricity * eccentricity);
  double rKm = 149598500 / f;
  double thetaDeg = f * 0.533128;

  double sunDistKm = Round(rKm, 0);
  double sunAngSizeDeg = DecimalDegreesDegrees(thetaDeg);
  double sunAngSizeMin = DecimalDegreesMinutes(thetaDeg);
  double sunAngSizeSec = DecimalDegreesSeconds(thetaDeg);

  return CSunDistanceAngularSize(sunDistKm, sunAngSizeDeg, sunAngSizeMin,
                                 sunAngSizeSec);
}

/**
 * \brief Calculate local sunrise and sunset.
 *
 * @return CSunriseAndSunset
 */
CSunriseAndSunset PASun::SunriseAndSunset(double localDay, int localMonth,
                                          int localYear, bool isDaylightSaving,
                                          int zoneCorrection,
                                          double geographicalLongDeg,
                                          double geographicalLatDeg) {
  int daylightSaving = (isDaylightSaving) ? 1 : 0;

  double localSunriseHours = SunriseLocalCivilTime(
      localDay, localMonth, localYear, daylightSaving, zoneCorrection,
      geographicalLongDeg, geographicalLatDeg);
  double localSunsetHours = SunsetLocalCivilTime(
      localDay, localMonth, localYear, daylightSaving, zoneCorrection,
      geographicalLongDeg, geographicalLatDeg);

  ERiseSetStatus sunRiseSetStatus = ESunRiseSetCalcStatus(
      localDay, localMonth, localYear, daylightSaving, zoneCorrection,
      geographicalLongDeg, geographicalLatDeg);

  double adjustedSunriseHours = localSunriseHours + 0.008333;
  double adjustedSunsetHours = localSunsetHours + 0.008333;

  double azimuthOfSunriseDeg1 =
      SunriseAzimuth(localDay, localMonth, localYear, daylightSaving,
                     zoneCorrection, geographicalLongDeg, geographicalLatDeg);
  double azimuthOfSunsetDeg1 =
      SunsetAzimuth(localDay, localMonth, localYear, daylightSaving,
                    zoneCorrection, geographicalLongDeg, geographicalLatDeg);

  int localSunriseHour = (sunRiseSetStatus == ERiseSetStatus::Ok)
                             ? DecimalHoursHour(adjustedSunriseHours)
                             : 0;
  int localSunriseMinute = (sunRiseSetStatus == ERiseSetStatus::Ok)
                               ? DecimalHoursMinute(adjustedSunriseHours)
                               : 0;

  int localSunsetHour = (sunRiseSetStatus == ERiseSetStatus::Ok)
                            ? DecimalHoursHour(adjustedSunsetHours)
                            : 0;
  int localSunsetMinute = (sunRiseSetStatus == ERiseSetStatus::Ok)
                              ? DecimalHoursMinute(adjustedSunsetHours)
                              : 0;

  double azimuthOfSunriseDeg = (sunRiseSetStatus == ERiseSetStatus::Ok)
                                   ? pa_util::Round(azimuthOfSunriseDeg1, 2)
                                   : 0;
  double azimuthOfSunsetDeg = (sunRiseSetStatus == ERiseSetStatus::Ok)
                                  ? pa_util::Round(azimuthOfSunsetDeg1, 2)
                                  : 0;

  ERiseSetStatus status = sunRiseSetStatus;

  return CSunriseAndSunset(localSunriseHour, localSunriseMinute,
                           localSunsetHour, localSunsetMinute,
                           azimuthOfSunriseDeg, azimuthOfSunsetDeg, status);
}

/**
 * \brief Calculate times of morning and evening twilight.
 *
 * @return CMorningAndEveningTwilight
 */
CMorningAndEveningTwilight PASun::MorningAndEveningTwilight(
    double localDay, int localMonth, int localYear, bool isDaylightSaving,
    int zoneCorrection, double geographicalLongDeg, double geographicalLatDeg,
    ETwilightType twilightType) {
  int daylightSaving = (isDaylightSaving) ? 1 : 0;

  double startOfAMTwilightHours = TwilightAMLocalCivilTime(
      localDay, localMonth, localYear, daylightSaving, zoneCorrection,
      geographicalLongDeg, geographicalLatDeg, twilightType);

  double endOfPMTwilightHours = TwilightPMLocalCivilTime(
      localDay, localMonth, localYear, daylightSaving, zoneCorrection,
      geographicalLongDeg, geographicalLatDeg, twilightType);

  ETwilightStatus twilightStatus =
      ETwilight(localDay, localMonth, localYear, daylightSaving, zoneCorrection,
                geographicalLongDeg, geographicalLatDeg, twilightType);

  double adjustedAMStartTime = startOfAMTwilightHours + 0.008333;
  double adjustedPMStartTime = endOfPMTwilightHours + 0.008333;

  double amTwilightBeginsHour = (twilightStatus == ETwilightStatus::Ok)
                                    ? DecimalHoursHour(adjustedAMStartTime)
                                    : -99;
  double amTwilightBeginsMin = (twilightStatus == ETwilightStatus::Ok)
                                   ? DecimalHoursMinute(adjustedAMStartTime)
                                   : -99;

  double pmTwilightEndsHour = (twilightStatus == ETwilightStatus::Ok)
                                  ? DecimalHoursHour(adjustedPMStartTime)
                                  : -99;
  double pmTwilightEndsMin = (twilightStatus == ETwilightStatus::Ok)
                                 ? DecimalHoursMinute(adjustedPMStartTime)
                                 : -99;

  ETwilightStatus status = twilightStatus;

  return CMorningAndEveningTwilight(amTwilightBeginsHour, amTwilightBeginsMin,
                                    pmTwilightEndsHour, pmTwilightEndsMin,
                                    status);
}

/**
 * \brief Calculate the equation of time.
 *
 * The equation of time is the  difference between the real Sun time and the
 * mean Sun time.
 *
 * @return CEquationOfTime
 */
CEquationOfTime PASun::EquationOfTime(double gwdateDay, int gwdateMonth,
                                      int gwdateYear) {
  double sunLongitudeDeg =
      SunLong(12, 0, 0, 0, 0, gwdateDay, gwdateMonth, gwdateYear);
  double sunRAHours = DecimalDegreesToDegreeHours(EclipticRightAscension(
      sunLongitudeDeg, 0, 0, 0, 0, 0, gwdateDay, gwdateMonth, gwdateYear));
  double equivalentUTHours = GreenwichSiderealTimeToUniversalTime(
      sunRAHours, 0, 0, gwdateDay, gwdateMonth, gwdateYear);
  double equationOfTimeHours = equivalentUTHours - 12;

  int equationOfTimeMin = DecimalHoursMinute(equationOfTimeHours);
  double equationOfTimeSec = DecimalHoursSecond(equationOfTimeHours);

  return CEquationOfTime(equationOfTimeMin, equationOfTimeSec);
}

/**
 * \brief Calculate solar elongation for a celestial body.
 *
 * Solar elongation is the angle between the lines of sight from the Earth to
 * the Sun and from the Earth to the celestial body.
 *
 * @return Solar elongation, in degrees.
 */
double PASun::SolarElongation(double raHour, double raMin, double raSec,
                              double decDeg, double decMin, double decSec,
                              double gwdateDay, int gwdateMonth,
                              int gwdateYear) {
  double sunLongitudeDeg =
      SunLong(0, 0, 0, 0, 0, gwdateDay, gwdateMonth, gwdateYear);
  double sunRAHours = DecimalDegreesToDegreeHours(EclipticRightAscension(
      sunLongitudeDeg, 0, 0, 0, 0, 0, gwdateDay, gwdateMonth, gwdateYear));
  double sunDecDeg = EclipticDeclination(sunLongitudeDeg, 0, 0, 0, 0, 0,
                                         gwdateDay, gwdateMonth, gwdateYear);
  double solarElongationDeg =
      pa_macros::Angle(sunRAHours, 0, 0, sunDecDeg, 0, 0, raHour, raMin, raSec,
                       decDeg, decMin, decSec, EAngleMeasure::Hours);

  return pa_util::Round(solarElongationDeg, 2);
}
