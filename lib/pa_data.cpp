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

PlanetDataPrecise getPrecisePlanetData(
    std::string planet_name,
    std::vector<pa_data::PlanetDataPrecise> precise_planet_data) {
  for (int i = 0; i < precise_planet_data.size(); i++)
    if (precise_planet_data[i].name == planet_name)
      return precise_planet_data[i];

  return PlanetDataPrecise("NoMatch", 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
}

PlanetDataPrecise populatePrecisePlanetData(std::string name, double value1,
                                            double value2, double value3,
                                            double value4, double value5,
                                            double value6, double value7,
                                            double value8, double value9,
                                            double ap_value) {
  return PlanetDataPrecise(name, value1, value2, value3, value4, value5, value6,
                           value7, value8, value9, ap_value);
}

/**
 * Retrieve information about an elliptical comet.
 */
CometDataElliptical ellipticalCometLookup(std::string cometName) {
  std::vector<CometDataElliptical> cometData;

  cometData.push_back(CometDataElliptical("Encke", 1974.32, 160.1, 334.2, 3.3,
                                          2.21, 0.85, 12.0));
  cometData.push_back(CometDataElliptical("Temple 2", 1972.87, 310.2, 119.3,
                                          5.26, 3.02, 0.55, 12.5));
  cometData.push_back(CometDataElliptical("Haneda-Campos", 1978.77, 12.02,
                                          131.7, 5.37, 3.07, 0.64, 5.81));
  cometData.push_back(CometDataElliptical("Schwassmann-Wachmann 2", 1974.7,
                                          123.3, 126.0, 6.51, 3.49, 0.39, 3.7));
  cometData.push_back(CometDataElliptical("Borrelly", 1974.36, 67.8, 75.1, 6.76,
                                          3.58, 0.63, 30.2));
  cometData.push_back(CometDataElliptical("Whipple", 1970.77, 18.2, 188.4, 7.47,
                                          3.82, 0.35, 10.2));
  cometData.push_back(CometDataElliptical("Oterma", 1958.44, 150.0, 155.1, 7.88,
                                          3.96, 0.14, 4.0));
  cometData.push_back(CometDataElliptical("Schaumasse", 1960.29, 138.1, 86.2,
                                          8.18, 4.05, 0.71, 12.0));
  cometData.push_back(CometDataElliptical("Comas Sola", 1969.83, 102.9, 62.8,
                                          8.55, 4.18, 0.58, 13.4));
  cometData.push_back(CometDataElliptical(
      "Schwassmann-Wachmann 1", 1974.12, 334.1, 319.6, 15.03, 6.09, 0.11, 9.7));
  cometData.push_back(CometDataElliptical("Neujmin 1", 1966.94, 334.0, 347.2,
                                          17.93, 6.86, 0.78, 15.0));
  cometData.push_back(CometDataElliptical("Crommelin", 1956.82, 86.4, 250.4,
                                          27.89, 9.17, 0.92, 28.9));
  cometData.push_back(CometDataElliptical("Olbers", 1956.46, 150.0, 85.4, 69.47,
                                          16.84, 0.93, 44.6));
  cometData.push_back(CometDataElliptical("Pons-Brooks", 1954.39, 94.2, 255.2,
                                          70.98, 17.2, 0.96, 74.2));
  cometData.push_back(CometDataElliptical("Halley", 1986.112, 170.011, 58.154,
                                          76.0081, 17.9435, 0.9673, 162.2384));

  for (int i = 0; i < cometData.size(); i++)
    if (cometData[i].name == cometName)
      return cometData[i];

  return CometDataElliptical("NoMatch", 0, 0, 0, 0, 0, 0, 0);
}

/**
 * Retrieve information about a parabolic comet.
 */
CometDataParabolic parabolicCometLookup(std::string cometName) {
  std::vector<CometDataParabolic> cometData;

  cometData.push_back(CometDataParabolic("Kohler", 10.5659, 11, 1977, 163.4799,
                                         181.8175, 0.990662, 48.7196));

  for (int i = 0; i < cometData.size(); i++)
    if (cometData[i].name == cometName)
      return cometData[i];

  return CometDataParabolic("NoMatch", 0, 0, 0, 0, 0, 0, 0);
}

} // namespace pa_data