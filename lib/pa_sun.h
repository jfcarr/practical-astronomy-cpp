#ifndef _pa_sun
#define _pa_sun

#include "pa_types.h"
#include <tuple>

using namespace pa_types;

class PASun {
public:
  std::tuple<double, double, double, double, double, double>
  ApproximatePositionOfSun(double lct_hours, double lct_minutes,
                           double lct_seconds, double local_day,
                           int local_month, int local_year,
                           bool is_daylight_saving, int zone_correction);

  std::tuple<double, double, double, double, double, double>
  PrecisePositionOfSun(double lct_hours, double lct_minutes, double lct_seconds,
                       double local_day, int local_month, int local_year,
                       bool is_daylight_saving, int zone_correction);

  std::tuple<double, double, double, double>
  SunDistanceAndAngularSize(double lct_hours, double lct_minutes,
                            double lct_seconds, double local_day,
                            int local_month, int local_year,
                            bool is_daylight_saving, int zone_correction);

  std::tuple<double, double, double, double, double, double, ERiseSetStatus>
  SunriseAndSunset(double local_day, int local_month, int local_year,
                   bool is_daylight_saving, int zone_correction,
                   double geographical_long_deg, double geographical_lat_deg);

  std::tuple<double, double, double, double, ETwilightStatus>
  MorningAndEveningTwilight(double localDay, int localMonth, int localYear,
                            bool isDaylightSaving, int zoneCorrection,
                            double geographicalLongDeg,
                            double geographicalLatDeg,
                            ETwilightType twilightType);

  std::tuple<double, double> EquationOfTime(double gwdateDay, int gwdateMonth,
                                            int gwdateYear);

  double SolarElongation(double raHour, double raMin, double raSec,
                         double decDeg, double decMin, double decSec,
                         double gwdateDay, int gwdateMonth, int gwdateYear);
};
#endif