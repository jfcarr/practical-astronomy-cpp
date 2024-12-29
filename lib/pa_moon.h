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
  PrecisePositionOfMoon(double lctHour, double lctMin, double lctSec,
                        bool isDaylightSaving, int zoneCorrectionHours,
                        double localDateDay, int localDateMonth,
                        int localDateYear);

  CMoonPhase MoonPhase(double lctHour, double lctMin, double lctSec,
                       bool isDaylightSaving, int zoneCorrectionHours,
                       double localDateDay, int localDateMonth,
                       int localDateYear, EAccuracyLevel accuracyLevel);

  CMoonNewFull TimesOfNewMoonAndFullMoon(bool isDaylightSaving,
                                         int zoneCorrectionHours,
                                         double localDateDay,
                                         int localDateMonth, int localDateYear);

  CMoonDistDiameterHP
  MoonDistAngDiamHorParallax(double lctHour, double lctMin, double lctSec,
                             bool isDaylightSaving, int zoneCorrectionHours,
                             double localDateDay, int localDateMonth,
                             int localDateYear);

  CMoonRiseSet MoonriseAndMoonset(double localDateDay, int localDateMonth,
                                  int localDateYear, bool isDaylightSaving,
                                  int zoneCorrectionHours, double geogLongDeg,
                                  double geogLatDeg);
};

#endif
