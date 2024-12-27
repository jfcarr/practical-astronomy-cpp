#ifndef _pa_data
#define _pa_data

#include <string>
#include <vector>

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

class PlanetDataPrecise {
public:
  std::string name; /** Name of planet */
  double value1;    /** Working value 1 */
  double value2;    /** Working value 2 */
  double value3;    /** Working value 3 */
  double value4;    /** Working value 4 */
  double value5;    /** Working value 5 */
  double value6;    /** Working value 6 */
  double value7;    /** Working value 7 */
  double value8;    /** Working value 8 */
  double value9;    /** Working value 9 */
  double ap_value;  /** Working AP value */

  PlanetDataPrecise() {}

  PlanetDataPrecise(std::string name, double value1, double value2,
                    double value3, double value4, double value5, double value6,
                    double value7, double value8, double value9,
                    double ap_value) {
    this->name = name;
    this->value1 = value1;
    this->value2 = value2;
    this->value3 = value3;
    this->value4 = value4;
    this->value5 = value5;
    this->value6 = value6;
    this->value7 = value7;
    this->value8 = value8;
    this->value9 = value9;
    this->ap_value = ap_value;
  }
};

PlanetData planetLookup(std::string planetName);

PlanetDataPrecise getPrecisePlanetData(
    std::string planet_name,
    std::vector<pa_data::PlanetDataPrecise> precise_planet_data);

PlanetDataPrecise populatePrecisePlanetData(std::string name, double value1,
                                            double value2, double value3,
                                            double value4, double value5,
                                            double value6, double value7,
                                            double value8, double value9,
                                            double ap_value);

class CometDataElliptical {
public:
  /** Name of comet */
  std::string name;

  /** Epoch of the perihelion */
  double epoch_EpochOfPerihelion;

  /** Longitude of the perihelion */
  double peri_LongitudeOfPerihelion;

  /** Longitude of the ascending node */
  double node_LongitudeOfAscendingNode;

  /** Period of the orbit */
  double period_PeriodOfOrbit;

  /** Semi-major axis of the orbit */
  double axis_SemiMajorAxisOfOrbit;

  /** Eccentricity of the orbit */
  double ecc_EccentricityOfOrbit;

  /** Inclination of the orbit */
  double incl_InclinationOfOrbit;

  CometDataElliptical() {}

  CometDataElliptical(std::string name, double epoch_EpochOfPerihelion,
                      double peri_LongitudeOfPerihelion,
                      double node_LongitudeOfAscendingNode,
                      double period_PeriodOfOrbit,
                      double axis_SemiMajorAxisOfOrbit,
                      double ecc_EccentricityOfOrbit,
                      double incl_InclinationOfOrbit) {
    this->name = name;
    this->epoch_EpochOfPerihelion = epoch_EpochOfPerihelion;
    this->peri_LongitudeOfPerihelion = peri_LongitudeOfPerihelion;
    this->node_LongitudeOfAscendingNode = node_LongitudeOfAscendingNode;
    this->period_PeriodOfOrbit = period_PeriodOfOrbit;
    this->axis_SemiMajorAxisOfOrbit = axis_SemiMajorAxisOfOrbit;
    this->ecc_EccentricityOfOrbit = ecc_EccentricityOfOrbit;
    this->incl_InclinationOfOrbit = incl_InclinationOfOrbit;
  }
};

CometDataElliptical ellipticalCometLookup(std::string cometName);

class CometDataParabolic {
public:
  /** Name of the comet  */
  std::string name;

  /** Epoch perihelion day */
  double epoch_peri_day;

  /** Epoch perihelion month */
  int epoch_peri_month;

  /** Epoch perihelion year */
  int epoch_peri_year;

  /** Arg perihelion */
  double arg_peri;

  /** Comet's node */
  double node;

  /** Distance at the perihelion */
  double peri_dist;

  /** Inclination */
  double incl;

  CometDataParabolic() {}

  CometDataParabolic(std::string name, double epoch_peri_day,
                     int epoch_peri_month, int epoch_peri_year, double arg_peri,
                     double node, double peri_dist, double incl) {
    this->name = name;
    this->epoch_peri_day = epoch_peri_day;
    this->epoch_peri_month = epoch_peri_month;
    this->epoch_peri_year = epoch_peri_year;
    this->arg_peri = arg_peri;
    this->node = node;
    this->peri_dist = peri_dist;
    this->incl = incl;
  }
};

CometDataParabolic parabolicCometLookup(std::string cometName);

class BinaryStarData {
public:
  std::string name;  /** Name of binary system.  */
  double period;     /** Period of the orbit. */
  double epoch_peri; /** Epoch of the perihelion. */
  double long_peri;  /** Longitude of the perihelion. */
  double ecc;        /** Eccentricity of the orbit. */
  double axis;       /** Semi-major axis of the orbit. */
  double incl;       /** Orbital inclination. */
  double pa_node;    /** Position angle of the ascending node. */

  BinaryStarData() {}

  BinaryStarData(std::string name, double period, double epoch_peri,
                 double long_peri, double ecc, double axis, double incl,
                 double pa_node) {
    this->name = name;
    this->period = period;
    this->epoch_peri = epoch_peri;
    this->long_peri = long_peri;
    this->ecc = ecc;
    this->axis = axis;
    this->incl = incl;
    this->pa_node = pa_node;
  }
};

BinaryStarData getBinaryStarData(std::string starName);

} // namespace pa_data
#endif