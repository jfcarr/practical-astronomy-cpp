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
};

#endif
