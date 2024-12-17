#ifndef _pa_planet
#define _pa_planet

#include "pa_models.h"
#include <string>
#include <tuple>

using namespace pa_models;

class PAPlanet {
public:
  CApproximatePositionOfPlanet
  ApproximatePositionOfPlanet(double lctHour, double lctMin, double lctSec,
                              bool isDaylightSaving, int zoneCorrectionHours,
                              double localDateDay, int localDateMonth,
                              int localDateYear, std::string planetName);

  CPrecisePositionOfPlanet
  PrecisePositionOfPlanet(double lctHour, double lctMin, double lctSec,
                          bool isDaylightSaving, int zoneCorrectionHours,
                          double localDateDay, int localDateMonth,
                          int localDateYear, std::string planetName);

  CPlanetVisualAspects
  VisualAspectsOfAPlanet(double lctHour, double lctMin, double lctSec,
                         bool isDaylightSaving, int zoneCorrectionHours,
                         double localDateDay, int localDateMonth,
                         int localDateYear, std::string planetName);
};
#endif
