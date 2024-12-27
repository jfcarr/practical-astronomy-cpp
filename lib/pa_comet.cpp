#include "pa_comet.h"
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
 * Calculate position of an elliptical comet.
 */
CCometPosition PAComet::PositionOfEllipticalComet(
    double lctHour, double lctMin, double lctSec, bool isDaylightSaving,
    int zoneCorrectionHours, double localDateDay, int localDateMonth,
    int localDateYear, std::string cometName) {
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

  pa_data::CometDataElliptical cometInfo =
      pa_data::ellipticalCometLookup(cometName);

  double timeSinceEpochYears =
      (CivilDateToJulianDate(greenwichDateDay, greenwichDateMonth,
                             greenwichDateYear) -
       CivilDateToJulianDate(0.0, 1, greenwichDateYear)) /
          365.242191 +
      greenwichDateYear - cometInfo.epoch_EpochOfPerihelion;
  double mcDeg = 360 * timeSinceEpochYears / cometInfo.period_PeriodOfOrbit;
  double mcRad = DegreesToRadians(mcDeg - 360 * floor(mcDeg / 360));
  double eccentricity = cometInfo.ecc_EccentricityOfOrbit;
  double trueAnomalyDeg = WToDegrees(TrueAnomaly(mcRad, eccentricity));
  double lcDeg = trueAnomalyDeg + cometInfo.peri_LongitudeOfPerihelion;
  double rAU = cometInfo.axis_SemiMajorAxisOfOrbit *
               (1 - eccentricity * eccentricity) /
               (1 + eccentricity * cos(DegreesToRadians(trueAnomalyDeg)));
  double lcNodeRad =
      DegreesToRadians(lcDeg - cometInfo.node_LongitudeOfAscendingNode);
  double psiRad =
      asin(sin(lcNodeRad) *
           sin(DegreesToRadians(cometInfo.incl_InclinationOfOrbit)));

  double y =
      sin(lcNodeRad) * cos(DegreesToRadians(cometInfo.incl_InclinationOfOrbit));
  double x = cos(lcNodeRad);

  double ldDeg =
      WToDegrees(atan2(y, x)) + cometInfo.node_LongitudeOfAscendingNode;
  double rdAU = rAU * cos(psiRad);

  double earthLongitudeLeDeg =
      SunLong(lctHour, lctMin, lctSec, daylightSaving, zoneCorrectionHours,
              localDateDay, localDateMonth, localDateYear) +
      180.0;
  double earthRadiusVectorAU =
      SunDist(lctHour, lctMin, lctSec, daylightSaving, zoneCorrectionHours,
              localDateDay, localDateMonth, localDateYear);

  double leLdRad = DegreesToRadians(earthLongitudeLeDeg - ldDeg);
  double aRad = (rdAU < earthRadiusVectorAU)
                    ? atan2((rdAU * sin(leLdRad)),
                            (earthRadiusVectorAU - rdAU * cos(leLdRad)))
                    : atan2((earthRadiusVectorAU * sin(-leLdRad)),
                            (rdAU - earthRadiusVectorAU * cos(leLdRad)));

  double cometLongDeg1 = (rdAU < earthRadiusVectorAU)
                             ? 180.0 + earthLongitudeLeDeg + WToDegrees(aRad)
                             : WToDegrees(aRad) + ldDeg;
  double cometLongDeg = cometLongDeg1 - 360 * floor(cometLongDeg1 / 360);
  double cometLatDeg = WToDegrees(
      atan(rdAU * tan(psiRad) * sin(DegreesToRadians((cometLongDeg1 - ldDeg))) /
           (earthRadiusVectorAU * sin(-leLdRad))));
  double cometRAHours1 = DecimalDegreesToDegreeHours(EclipticRightAscension(
      cometLongDeg, 0, 0, cometLatDeg, 0, 0, greenwichDateDay,
      greenwichDateMonth, greenwichDateYear));
  double cometDecDeg1 = EclipticDeclination(
      cometLongDeg, 0, 0, cometLatDeg, 0, 0, greenwichDateDay,
      greenwichDateMonth, greenwichDateYear);
  double cometDistanceAU = sqrt(
      pow(earthRadiusVectorAU, 2) + pow(rAU, 2) -
      2.0 * earthRadiusVectorAU * rAU *
          cos(DegreesToRadians((lcDeg - earthLongitudeLeDeg))) * cos(psiRad));

  int cometRAHour = DecimalHoursHour(cometRAHours1 + 0.008333);
  int cometRAMin = DecimalHoursMinute(cometRAHours1 + 0.008333);
  double cometDecDeg = DecimalDegreesDegrees(cometDecDeg1 + 0.008333);
  double cometDecMin = DecimalDegreesMinutes(cometDecDeg1 + 0.008333);
  double cometDistEarth = Round(cometDistanceAU, 2);

  return CCometPosition(cometRAHour, cometRAMin, 0, cometDecDeg, cometDecMin, 0,
                        cometDistEarth);
}

/**
 * Calculate position of a parabolic comet.
 */
CCometPosition PAComet::PositionOfParabolicComet(
    double lctHour, double lctMin, double lctSec, bool isDaylightSaving,
    int zoneCorrectionHours, double localDateDay, int localDateMonth,
    int localDateYear, std::string cometName) {
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

  pa_data::CometDataParabolic cometInfo =
      pa_data::parabolicCometLookup(cometName);

  double perihelionEpochDay = cometInfo.epoch_peri_day;
  int perihelionEpochMonth = cometInfo.epoch_peri_month;
  int perihelionEpochYear = cometInfo.epoch_peri_year;
  double qAU = cometInfo.peri_dist;
  double inclinationDeg = cometInfo.incl;
  double perihelionDeg = cometInfo.arg_peri;
  double nodeDeg = cometInfo.node;

  CCometLongLatDist cometLongLatDist = PCometLongLatDist(
      lctHour, lctMin, lctSec, daylightSaving, zoneCorrectionHours,
      localDateDay, localDateMonth, localDateYear, perihelionEpochDay,
      perihelionEpochMonth, perihelionEpochYear, qAU, inclinationDeg,
      perihelionDeg, nodeDeg);

  double cometRAHours = DecimalDegreesToDegreeHours(EclipticRightAscension(
      cometLongLatDist.longDeg, 0, 0, cometLongLatDist.latDeg, 0, 0,
      greenwichDateDay, greenwichDateMonth, greenwichDateYear));
  double cometDecDeg1 = EclipticDeclination(
      cometLongLatDist.longDeg, 0, 0, cometLongLatDist.latDeg, 0, 0,
      greenwichDateDay, greenwichDateMonth, greenwichDateYear);

  int cometRAHour = DecimalHoursHour(cometRAHours);
  int cometRAMin = DecimalHoursMinute(cometRAHours);
  double cometRASec = DecimalHoursSecond(cometRAHours);
  double cometDecDeg = DecimalDegreesDegrees(cometDecDeg1);
  double cometDecMin = DecimalDegreesMinutes(cometDecDeg1);
  double cometDecSec = DecimalDegreesSeconds(cometDecDeg1);
  double cometDistEarth = Round(cometLongLatDist.distAU, 2);

  return CCometPosition(cometRAHour, cometRAMin, cometRASec, cometDecDeg,
                        cometDecMin, cometDecSec, cometDistEarth);
}