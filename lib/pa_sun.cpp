#include "pa_sun.h"
#include "pa_macros.h"
#include "pa_types.h"
#include "pa_util.h"
#include <cmath>

using namespace pa_types;
using namespace pa_util;
using namespace pa_macros;

/**
 * \brief Calculate approximate position of the sun for a local date and time.
 *
 * @return tuple <double sun_ra_hour, double sun_ra_main, double sun_ra_sec,
 * double sun_dec_deg, double sun_dec_min, double sun_dec_sec>
 */
std::tuple<double, double, double, double, double, double>
PASun::ApproximatePositionOfSun(double lctHours, double lctMinutes,
                                double lctSeconds, double localDay,
                                int localMonth, int localYear,
                                bool isDaylightSaving, int zoneCorrection) {
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

  return std::tuple<double, double, double, double, double, double>{
      sunRaHour, sunRaMin, sunRaSec, sunDecDeg, sunDecMin, sunDecSec};
}

/**
 * \brief Calculate precise position of the sun for a local date and time.
 */
std::tuple<double, double, double, double, double, double>
PASun::PrecisePositionOfSun(double lctHours, double lctMinutes,
                            double lctSeconds, double localDay, int localMonth,
                            int localYear, bool isDaylightSaving,
                            int zoneCorrection) {
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

  return std::tuple<double, double, double, double, double, double>{
      sunRaHour, sunRaMin, sunRaSec, sunDecDeg, sunDecMin, sunDecSec};
}

/**
 * \brief Calculate distance to the Sun (in km), and angular size.
 *
 * @return tuple<double sun_dist_km, double sun_ang_size_deg, double
 * sun_ang_size_min, double sun_ang_size_sec>
 */
std::tuple<double, double, double, double> PASun::SunDistanceAndAngularSize(
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

  return std::tuple<double, double, double, double>{
      sunDistKm, sunAngSizeDeg, sunAngSizeMin, sunAngSizeSec};
}

/**
 * \brief Calculate local sunrise and sunset.
 *
 * tuple <double local_sunrise_hour, double local_sunrise_minute, double
 * local_sunset_hour, double local_sunset_minute, double azimuth_of_sunrise_deg,
 * double azimuth_of_sunset_deg, pa_types::sun_rise_set_status>
 */
std::tuple<double, double, double, double, double, double,
           pa_types::RiseSetStatus>
PASun::SunriseAndSunset(double localDay, int localMonth, int localYear,
                        bool isDaylightSaving, int zoneCorrection,
                        double geographicalLongDeg, double geographicalLatDeg) {
  int daylightSaving = (isDaylightSaving) ? 1 : 0;

  double localSunriseHours = SunriseLocalCivilTime(
      localDay, localMonth, localYear, daylightSaving, zoneCorrection,
      geographicalLongDeg, geographicalLatDeg);
  double localSunsetHours = SunsetLocalCivilTime(
      localDay, localMonth, localYear, daylightSaving, zoneCorrection,
      geographicalLongDeg, geographicalLatDeg);

  pa_types::RiseSetStatus sunRiseSetStatus = ESunRiseSetCalcStatus(
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

  int localSunriseHour = (sunRiseSetStatus == pa_types::RiseSetStatus::Ok)
                             ? DecimalHoursHour(adjustedSunriseHours)
                             : 0;
  int localSunriseMinute = (sunRiseSetStatus == pa_types::RiseSetStatus::Ok)
                               ? DecimalHoursMinute(adjustedSunriseHours)
                               : 0;

  int localSunsetHour = (sunRiseSetStatus == pa_types::RiseSetStatus::Ok)
                            ? DecimalHoursHour(adjustedSunsetHours)
                            : 0;
  int localSunsetMinute = (sunRiseSetStatus == pa_types::RiseSetStatus::Ok)
                              ? DecimalHoursMinute(adjustedSunsetHours)
                              : 0;

  double azimuthOfSunriseDeg = (sunRiseSetStatus == pa_types::RiseSetStatus::Ok)
                                   ? pa_util::Round(azimuthOfSunriseDeg1, 2)
                                   : 0;
  double azimuthOfSunsetDeg = (sunRiseSetStatus == pa_types::RiseSetStatus::Ok)
                                  ? pa_util::Round(azimuthOfSunsetDeg1, 2)
                                  : 0;

  pa_types::RiseSetStatus status = sunRiseSetStatus;

  return std::tuple<double, double, double, double, double, double,
                    pa_types::RiseSetStatus>{localSunriseHour,
                                             localSunriseMinute,
                                             localSunsetHour,
                                             localSunsetMinute,
                                             azimuthOfSunriseDeg,
                                             azimuthOfSunsetDeg,
                                             status};
}