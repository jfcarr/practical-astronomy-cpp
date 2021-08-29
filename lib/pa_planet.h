#ifndef _pa_planet
#define _pa_planet

#include <string>
#include <tuple>

class PAPlanet {
public:
  std::tuple<double, double, double, double, double, double>
  ApproximatePositionOfPlanet(double lctHour, double lctMin, double lctSec,
                              bool isDaylightSaving, int zoneCorrectionHours,
                              double localDateDay, int localDateMonth,
                              int localDateYear, std::string planetName);
};
#endif