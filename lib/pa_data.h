#ifndef _pa_data
#define _pa_data

#include <string>

namespace pa_data {
class PlanetData {
public:
  /**
   * Name of planet.
   */
  std::string planetName;

  /**
   * Period of orbit.
   *
   * Original element name: tp
   */
  double tp_PeriodOrbit;

  /**
   * Longitude at the epoch.
   *
   * Original element name: long
   */
  double long_LongitudeEpoch;

  /**
   * Longitude of the perihelion.
   *
   * Original element name: peri
   */
  double peri_LongitudePerihelion;

  /**
   * Eccentricity of the orbit.
   *
   * Original element name: ecc
   */
  double ecc_EccentricityOrbit;

  /**
   * Semi-major axis of the orbit.
   *
   * Original element name: axis
   */
  double axis_AxisOrbit;

  /**
   * Orbital inclination.
   *
   * Original element name: incl
   */
  double incl_OrbitalInclination;

  /**
   * Longitude of the ascending node.
   *
   * Original element name: node
   */
  double node_LongitudeAscendingNode;

  /**
   * Angular diameter at 1 AU.
   *
   * Original element name: theta0
   */
  double theta0_AngularDiameter;

  /**
   * Visual magnitude at 1 AU.
   *
   * Original element name: v0
   */
  double v0_VisualMagnitude;

  PlanetData() {}

  PlanetData(std::string planetName, double tp_PeriodOrbit,
             double long_LongitudeEpoch, double peri_LongitudePerihelion,
             double ecc_EccentricityOrbit, double axis_AxisOrbit,
             double incl_OrbitalInclination, double node_LongitudeAscendingNode,
             double theta0_AngularDiameter, double v0_VisualMagnitude) {
    this->planetName = planetName;
    this->tp_PeriodOrbit = tp_PeriodOrbit;
    this->long_LongitudeEpoch = long_LongitudeEpoch;
    this->peri_LongitudePerihelion = peri_LongitudePerihelion;
    this->ecc_EccentricityOrbit = ecc_EccentricityOrbit;
    this->axis_AxisOrbit = axis_AxisOrbit;
    this->incl_OrbitalInclination = incl_OrbitalInclination;
    this->node_LongitudeAscendingNode = node_LongitudeAscendingNode;
    this->theta0_AngularDiameter = theta0_AngularDiameter;
    this->v0_VisualMagnitude = v0_VisualMagnitude;
  }
};

PlanetData planetLookup(std::string planetName);

} // namespace pa_data
#endif