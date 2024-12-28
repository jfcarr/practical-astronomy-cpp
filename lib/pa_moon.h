#ifndef _pa_moon
#define _pa_moon

#include "pa_models.h"
#include <string>
#include <tuple>

using namespace pa_models;

class PAMoon {
public:
  CMoonApproximatePosition
  ApproximatePositionOfMoon(double lctHour, double lctMin, double lctSec,
                            bool isDaylightSaving, int zoneCorrectionHours,
                            double localDateDay, int localDateMonth,
                            int localDateYear);

  CMoonPrecisePosition
  PrecisePositionOfMoon(double lct_hour, double lct_min, double lct_sec,
                        bool is_daylight_saving, int zone_correction_hours,
                        double local_date_day, int local_date_month,
                        int local_date_year);
};

#endif
