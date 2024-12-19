#ifndef _pa_sun
#define _pa_sun

#include "pa_models.h"
#include "pa_types.h"
#include <tuple>

using namespace pa_models;
using namespace pa_types;

class PASun {
public:
  CApproximatePositionOfSun
  ApproximatePositionOfSun(double lct_hours, double lct_minutes,
                           double lct_seconds, double local_day,
                           int local_month, int local_year,
                           bool is_daylight_saving, int zone_correction);

  CPrecisePositionOfSun
  PrecisePositionOfSun(double lct_hours, double lct_minutes, double lct_seconds,
                       double local_day, int local_month, int local_year,
                       bool is_daylight_saving, int zone_correction);

  CSunDistanceAngularSize
  SunDistanceAndAngularSize(double lct_hours, double lct_minutes,
                            double lct_seconds, double local_day,
                            int local_month, int local_year,
                            bool is_daylight_saving, int zone_correction);

  CSunriseAndSunset SunriseAndSunset(double local_day, int local_month,
                                     int local_year, bool is_daylight_saving,
                                     int zone_correction,
                                     double geographical_long_deg,
                                     double geographical_lat_deg);

  CMorningAndEveningTwilight MorningAndEveningTwilight(
      double localDay, int localMonth, int localYear, bool isDaylightSaving,
      int zoneCorrection, double geographicalLongDeg, double geographicalLatDeg,
      ETwilightType twilightType);

  CEquationOfTime EquationOfTime(double gwdateDay, int gwdateMonth,
                                 int gwdateYear);

  double SolarElongation(double raHour, double raMin, double raSec,
                         double decDeg, double decMin, double decSec,
                         double gwdateDay, int gwdateMonth, int gwdateYear);
};
#endif