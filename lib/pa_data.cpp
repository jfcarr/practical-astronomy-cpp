#include "pa_data.h"
#include <vector>

namespace pa_data {

/**
 * Retrieve information about a planet.
 */
PlanetData planetLookup(std::string planetName) {
  std::vector<PlanetData> planetData;

  planetData.push_back(PlanetData("Mercury", 0.24085, 75.5671, 77.612, 0.205627,
                                  0.387098, 7.0051, 48.449, 6.74, -0.42));
  planetData.push_back(PlanetData("Venus", 0.615207, 272.30044, 131.54,
                                  0.006812, 0.723329, 3.3947, 76.769, 16.92,
                                  -4.4));
  planetData.push_back(PlanetData("Earth", 0.999996, 99.556772, 103.2055,
                                  0.016671, 0.999985, -99.0, -99.0, -99.0,
                                  -99.0));
  planetData.push_back(PlanetData("Mars", 1.880765, 109.09646, 336.217,
                                  0.093348, 1.523689, 1.8497, 49.632, 9.36,
                                  -1.52));
  planetData.push_back(PlanetData("Jupiter", 11.857911, 337.917132, 14.6633,
                                  0.048907, 5.20278, 1.3035, 100.595, 196.74,
                                  -9.4));
  planetData.push_back(PlanetData("Saturn", 29.310579, 172.398316, 89.567,
                                  0.053853, 9.51134, 2.4873, 113.752, 165.6,
                                  -8.88));
  planetData.push_back(PlanetData("Uranus", 84.039492, 356.135400, 172.884833,
                                  0.046321, 19.21814, 0.773059, 73.926961, 65.8,
                                  -7.19));
  planetData.push_back(PlanetData("Neptune", 165.845392, 326.895127, 23.07,
                                  0.010483, 30.1985, 1.7673, 131.879, 62.2,
                                  -6.87));

  for (int i = 0; i < planetData.size(); i++)
    if (planetData[i].planetName == planetName)
      return planetData[i];

  return PlanetData("NoMatch", 0, 0, 0, 0, 0, 0, 0, 0, 0);
}
} // namespace pa_data