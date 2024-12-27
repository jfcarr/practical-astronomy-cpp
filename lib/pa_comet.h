#ifndef _pa_comet
#define _pa_comet

#include "pa_models.h"
#include <string>
#include <tuple>

using namespace pa_models;

class PAComet {
public:
  CCometPosition
  PositionOfEllipticalComet(double lctHour, double lctMin, double lctSec,
                            bool isDaylightSaving, int zoneCorrectionHours,
                            double localDateDay, int localDateMonth,
                            int localDateYear, std::string cometName);

  CCometPosition
  PositionOfParabolicComet(double lct_hour, double lct_min, double lct_sec,
                           bool is_daylight_saving, int zone_correction_hours,
                           double local_date_day, int local_date_month,
                           int local_date_year, std::string comet_name);
};

#endif
