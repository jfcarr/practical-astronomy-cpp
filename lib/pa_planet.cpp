#include "pa_planet.h"
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
 * Calculate approximate position of a planet.
 *
 * @return CApproximatePositionOfPlanet
 */
CApproximatePositionOfPlanet PAPlanet::ApproximatePositionOfPlanet(
    double lctHour, double lctMin, double lctSec, bool isDaylightSaving,
    int zoneCorrectionHours, double localDateDay, int localDateMonth,
    int localDateYear, std::string planetName) {
  int daylightSaving = (isDaylightSaving) ? 1 : 0;

  pa_data::PlanetData planetInfo = pa_data::planetLookup(planetName);

  double gdateDay = pa_macros::LocalCivilTimeGreenwichDay(
      lctHour, lctMin, lctSec, daylightSaving, zoneCorrectionHours,
      localDateDay, localDateMonth, localDateYear);
  int gdateMonth = pa_macros::LocalCivilTimeGreenwichMonth(
      lctHour, lctMin, lctSec, daylightSaving, zoneCorrectionHours,
      localDateDay, localDateMonth, localDateYear);
  int gdateYear = pa_macros::LocalCivilTimeGreenwichYear(
      lctHour, lctMin, lctSec, daylightSaving, zoneCorrectionHours,
      localDateDay, localDateMonth, localDateYear);

  double utHours = pa_macros::LocalCivilTimeToUniversalTime(
      lctHour, lctMin, lctSec, daylightSaving, zoneCorrectionHours,
      localDateDay, localDateMonth, localDateYear);
  double dDays = pa_macros::CivilDateToJulianDate(gdateDay + (utHours / 24),
                                                  gdateMonth, gdateYear) -
                 pa_macros::CivilDateToJulianDate(0, 1, 2010);
  double npDeg1 = 360 * dDays / (365.242191 * planetInfo.tp_PeriodOrbit);
  double npDeg2 = npDeg1 - 360 * std::floor(npDeg1 / 360);
  double mpDeg = npDeg2 + planetInfo.long_LongitudeEpoch -
                 planetInfo.peri_LongitudePerihelion;
  double lpDeg1 = npDeg2 +
                  (360 * planetInfo.ecc_EccentricityOrbit *
                   sin(pa_util::DegreesToRadians(mpDeg)) / M_PI) +
                  planetInfo.long_LongitudeEpoch;
  double lpDeg2 = lpDeg1 - 360 * std::floor(lpDeg1 / 360);
  double planetTrueAnomalyDeg = lpDeg2 - planetInfo.peri_LongitudePerihelion;
  double rAU = planetInfo.axis_AxisOrbit *
               (1 - pow(planetInfo.ecc_EccentricityOrbit, 2)) /
               (1 + planetInfo.ecc_EccentricityOrbit *
                        cos(pa_util::DegreesToRadians(planetTrueAnomalyDeg)));

  pa_data::PlanetData earthInfo = pa_data::planetLookup("Earth");

  double neDeg1 = 360 * dDays / (365.242191 * earthInfo.tp_PeriodOrbit);
  double neDeg2 = neDeg1 - 360 * std::floor(neDeg1 / 360);
  double meDeg = neDeg2 + earthInfo.long_LongitudeEpoch -
                 earthInfo.peri_LongitudePerihelion;
  double leDeg1 = neDeg2 + earthInfo.long_LongitudeEpoch +
                  360 * earthInfo.ecc_EccentricityOrbit *
                      sin(pa_util::DegreesToRadians(meDeg)) / M_PI;
  double leDeg2 = leDeg1 - 360 * std::floor(leDeg1 / 360);
  double earthTrueAnomalyDeg = leDeg2 - earthInfo.peri_LongitudePerihelion;
  double rAU2 = earthInfo.axis_AxisOrbit *
                (1 - pow(earthInfo.ecc_EccentricityOrbit, 2)) /
                (1 + earthInfo.ecc_EccentricityOrbit *
                         cos(pa_util::DegreesToRadians(earthTrueAnomalyDeg)));
  double lpNodeRad = pa_util::DegreesToRadians(
      lpDeg2 - planetInfo.node_LongitudeAscendingNode);
  double psiRad =
      asin(sin(lpNodeRad) *
           sin(pa_util::DegreesToRadians(planetInfo.incl_OrbitalInclination)));
  double y = sin(lpNodeRad) *
             cos(pa_util::DegreesToRadians(planetInfo.incl_OrbitalInclination));
  double x = cos(lpNodeRad);
  double ldDeg = pa_macros::WToDegrees(atan2(y, x)) +
                 planetInfo.node_LongitudeAscendingNode;
  double rdAU = rAU * cos(psiRad);
  double leLdRad = pa_util::DegreesToRadians(leDeg2 - ldDeg);
  double atan2Type1 = atan2(rdAU * sin(leLdRad), rAU2 - rdAU * cos(leLdRad));

  double atan2Type2 = atan2(rAU2 * sin(-leLdRad), rdAU - rAU2 * cos(leLdRad));
  double aRad = (rdAU < 1) ? atan2Type1 : atan2Type2;
  double lamdaDeg1 = (rdAU < 1) ? 180 + leDeg2 + pa_macros::WToDegrees(aRad)
                                : pa_macros::WToDegrees(aRad) + ldDeg;
  double lamdaDeg2 = lamdaDeg1 - 360 * std::floor(lamdaDeg1 / 360);
  double betaDeg = pa_macros::WToDegrees(atan(
      rdAU * tan(psiRad) * sin(pa_util::DegreesToRadians(lamdaDeg2 - ldDeg)) /
      (rAU2 * sin(-leLdRad))));
  double raHours =
      pa_macros::DecimalDegreesToDegreeHours(pa_macros::EclipticRightAscension(
          lamdaDeg2, 0, 0, betaDeg, 0, 0, gdateDay, gdateMonth, gdateYear));
  double decDeg = pa_macros::EclipticDeclination(
      lamdaDeg2, 0, 0, betaDeg, 0, 0, gdateDay, gdateMonth, gdateYear);

  int planetRAHour = pa_macros::DecimalHoursHour(raHours);
  int planetRAMin = pa_macros::DecimalHoursMinute(raHours);
  double planetRASec = pa_macros::DecimalHoursSecond(raHours);
  double planetDecDeg = pa_macros::DecimalDegreesDegrees(decDeg);
  double planetDecMin = pa_macros::DecimalDegreesMinutes(decDeg);
  double planetDecSec = pa_macros::DecimalDegreesSeconds(decDeg);

  return CApproximatePositionOfPlanet(planetRAHour, planetRAMin, planetRASec,
                                      planetDecDeg, planetDecMin, planetDecSec);
}

/**
 * Calculate precise position of a planet.
 *
 * @return CPrecisePositionOfPlanet
 */
CPrecisePositionOfPlanet PAPlanet::PrecisePositionOfPlanet(
    double lctHour, double lctMin, double lctSec, bool isDaylightSaving,
    int zoneCorrectionHours, double localDateDay, int localDateMonth,
    int localDateYear, std::string planetName) {
  int daylightSaving = (isDaylightSaving) ? 1 : 0;

  pa_models::CPlanetCoordinates coordinateResults =
      pa_macros::PlanetCoordinates(lctHour, lctMin, lctSec, daylightSaving,
                                   zoneCorrectionHours, localDateDay,
                                   localDateMonth, localDateYear, planetName);

  double planetRAHours =
      pa_macros::DecimalDegreesToDegreeHours(pa_macros::EclipticRightAscension(
          coordinateResults.planetLongitude, 0, 0,
          coordinateResults.planetLatitude, 0, 0, localDateDay, localDateMonth,
          localDateYear));
  double planetDecDeg1 = pa_macros::EclipticDeclination(
      coordinateResults.planetLongitude, 0, 0, coordinateResults.planetLatitude,
      0, 0, localDateDay, localDateMonth, localDateYear);

  int planetRAHour = pa_macros::DecimalHoursHour(planetRAHours);
  int planetRAMin = pa_macros::DecimalHoursMinute(planetRAHours);
  double planetRASec = pa_macros::DecimalHoursSecond(planetRAHours);
  double planetDecDeg = pa_macros::DecimalDegreesDegrees(planetDecDeg1);
  double planetDecMin = pa_macros::DecimalDegreesMinutes(planetDecDeg1);
  double planetDecSec = pa_macros::DecimalDegreesSeconds(planetDecDeg1);

  return CPrecisePositionOfPlanet(planetRAHour, planetRAMin, planetRASec,
                                  planetDecDeg, planetDecMin, planetDecSec);
}

/**
 * Calculate several visual aspects of a planet.
 *
 * @return CPlanetVisualAspects
 */
CPlanetVisualAspects
PAPlanet::VisualAspectsOfAPlanet(double lctHour, double lctMin, double lctSec,
                                 bool isDaylightSaving, int zoneCorrectionHours,
                                 double localDateDay, int localDateMonth,
                                 int localDateYear, std::string planetName) {
  int daylightSaving = isDaylightSaving ? 1 : 0;

  double greenwichDateDay = LocalCivilTimeGreenwichDay(
      lctHour, lctMin, lctSec, daylightSaving, zoneCorrectionHours,
      localDateDay, localDateMonth, localDateYear);
  int greenwichDateMonth = LocalCivilTimeGreenwichMonth(
      lctHour, lctMin, lctSec, daylightSaving, zoneCorrectionHours,
      localDateDay, localDateMonth, localDateYear);
  int greenwichDateYear = LocalCivilTimeGreenwichYear(
      lctHour, lctMin, lctSec, daylightSaving, zoneCorrectionHours,
      localDateDay, localDateMonth, localDateYear);

  CPlanetCoordinates planetCoordInfo = PlanetCoordinates(
      lctHour, lctMin, lctSec, daylightSaving, zoneCorrectionHours,
      localDateDay, localDateMonth, localDateYear, planetName);

  double planetRARad = DegreesToRadians(EclipticRightAscension(
      planetCoordInfo.planetLongitude, 0, 0, planetCoordInfo.planetLatitude, 0,
      0, localDateDay, localDateMonth, localDateYear));
  double planetDecRad = DegreesToRadians(EclipticDeclination(
      planetCoordInfo.planetLongitude, 0, 0, planetCoordInfo.planetLatitude, 0,
      0, localDateDay, localDateMonth, localDateYear));

  double lightTravelTimeHours = planetCoordInfo.planetDistanceAU * 0.1386;

  pa_data::PlanetData planetInfo = pa_data::planetLookup(planetName);
  double angularDiameterArcsec =
      planetInfo.theta0_AngularDiameter / planetCoordInfo.planetDistanceAU;
  double phase1 =
      0.5 * (1.0 + cos(DegreesToRadians(planetCoordInfo.planetLongitude -
                                        planetCoordInfo.planetHLong1)));

  double sunEclLongDeg =
      SunLong(lctHour, lctMin, lctSec, daylightSaving, zoneCorrectionHours,
              localDateDay, localDateMonth, localDateYear);
  double sunRARad = DegreesToRadians(
      EclipticRightAscension(sunEclLongDeg, 0, 0, 0, 0, 0, greenwichDateDay,
                             greenwichDateMonth, greenwichDateYear));
  double sunDecRad = DegreesToRadians(
      EclipticDeclination(sunEclLongDeg, 0, 0, 0, 0, 0, greenwichDateDay,
                          greenwichDateMonth, greenwichDateYear));

  double y = cos(sunDecRad) * sin(sunRARad - planetRARad);
  double x = cos(planetDecRad) * sin(sunDecRad) -
             sin(planetDecRad) * cos(sunDecRad) * cos(sunRARad - planetRARad);

  double chiDeg = WToDegrees(atan2(y, x));
  double radiusVectorAU = planetCoordInfo.planetRVect;
  double approximateMagnitude1 =
      5.0 * log10(radiusVectorAU * planetCoordInfo.planetDistanceAU /
                  sqrt(phase1)) +
      planetInfo.v0_VisualMagnitude;

  double distanceAU = Round(planetCoordInfo.planetDistanceAU, 5);
  double angDiaArcsec = Round(angularDiameterArcsec, 1);
  double phase = Round(phase1, 2);
  int lightTimeHour = DecimalHoursHour(lightTravelTimeHours);
  int lightTimeMinutes = DecimalHoursMinute(lightTravelTimeHours);
  double lightTimeSeconds = DecimalHoursSecond(lightTravelTimeHours);
  double posAngleBrightLimbDeg = Round(chiDeg, 1);
  double approximateMagnitude = Round(approximateMagnitude1, 1);

  return CPlanetVisualAspects(distanceAU, angDiaArcsec, phase, lightTimeHour,
                              lightTimeMinutes, lightTimeSeconds,
                              posAngleBrightLimbDeg, approximateMagnitude);
}
