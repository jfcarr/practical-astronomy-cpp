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
    double lct_hour, double lct_min, double lct_sec, bool is_daylight_saving,
    int zone_correction_hours, double local_date_day, int local_date_month,
    int local_date_year, std::string comet_name) {
  int daylight_saving = is_daylight_saving ? 1 : 0;

  double greenwich_date_day = LocalCivilTimeGreenwichDay(
      lct_hour, lct_min, lct_sec, daylight_saving, zone_correction_hours,
      local_date_day, local_date_month, local_date_year);
  int greenwich_date_month = LocalCivilTimeGreenwichMonth(
      lct_hour, lct_min, lct_sec, daylight_saving, zone_correction_hours,
      local_date_day, local_date_month, local_date_year);
  int greenwich_date_year = LocalCivilTimeGreenwichYear(
      lct_hour, lct_min, lct_sec, daylight_saving, zone_correction_hours,
      local_date_day, local_date_month, local_date_year);

  pa_data::CometDataParabolic comet_info =
      pa_data::parabolicCometLookup(comet_name);

  double perihelion_epoch_day = comet_info.epoch_peri_day;
  int perihelion_epoch_month = comet_info.epoch_peri_month;
  int perihelion_epoch_year = comet_info.epoch_peri_year;
  double q_au = comet_info.peri_dist;
  double inclination_deg = comet_info.incl;
  double perihelion_deg = comet_info.arg_peri;
  double node_deg = comet_info.node;

  CCometLongLatDist comet_long_lat_dist = PCometLongLatDist(
      lct_hour, lct_min, lct_sec, daylight_saving, zone_correction_hours,
      local_date_day, local_date_month, local_date_year, perihelion_epoch_day,
      perihelion_epoch_month, perihelion_epoch_year, q_au, inclination_deg,
      perihelion_deg, node_deg);

  double comet_ra_hours = DecimalDegreesToDegreeHours(EclipticRightAscension(
      comet_long_lat_dist.longDeg, 0, 0, comet_long_lat_dist.latDeg, 0, 0,
      greenwich_date_day, greenwich_date_month, greenwich_date_year));
  double comet_dec_deg1 = EclipticDeclination(
      comet_long_lat_dist.longDeg, 0, 0, comet_long_lat_dist.latDeg, 0, 0,
      greenwich_date_day, greenwich_date_month, greenwich_date_year);

  int comet_ra_hour = DecimalHoursHour(comet_ra_hours);
  int comet_ra_min = DecimalHoursMinute(comet_ra_hours);
  double comet_ra_sec = DecimalHoursSecond(comet_ra_hours);
  double comet_dec_deg = DecimalDegreesDegrees(comet_dec_deg1);
  double comet_dec_min = DecimalDegreesMinutes(comet_dec_deg1);
  double comet_dec_sec = DecimalDegreesSeconds(comet_dec_deg1);
  double comet_dist_earth = Round(comet_long_lat_dist.distAU, 2);

  return CCometPosition(comet_ra_hour, comet_ra_min, comet_ra_sec,
                        comet_dec_deg, comet_dec_min, comet_dec_sec,
                        comet_dist_earth);
}