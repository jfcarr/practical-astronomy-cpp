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

  CCometPosition PositionOfParabolicComet(double lctHour, double lctMin,
                                          double lctSec, bool isDaylightSaving,
                                          int zoneCorrectionHours,
                                          double localDateDay,
                                          int localDateMonth, int localDateYear,
                                          std::string cometName);
};

#endif
