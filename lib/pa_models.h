
#ifndef _pa_models
#define _pa_models
namespace pa_models {
class CPrecisePositionOfPlanet {
public:
  CPrecisePositionOfPlanet(int planetRAHour, int planetRAMin,
                           double planetRASec, double planetDecDeg,
                           double planetDecMin, double planetDecSec) {
    PlanetRAHour = planetRAHour;
    PlanetRAMin = planetRAMin;
    PlanetRASec = planetRASec;
    PlanetDecDeg = planetDecDeg;
    PlanetDecMin = planetDecMin;
    PlanetDecSec = planetDecSec;
  }

  int PlanetRAHour;
  int PlanetRAMin;
  double PlanetRASec;
  double PlanetDecDeg;
  double PlanetDecMin;
  double PlanetDecSec;
};

class CPlanetCoordinates {
public:
  CPlanetCoordinates(double planetLongitude, double planetLatitude,
                     double planetDistanceAU, double planetHLong1,
                     double planetHLong2, double planetHLat,
                     double planetRVect) {
    this->planetLongitude = planetLongitude;
    this->planetLatitude = planetLatitude;
    this->planetDistanceAU = planetDistanceAU;
    this->planetHLong1 = planetHLong1;
    this->planetHLong2 = planetHLong2;
    this->planetHLat = planetHLat;
    this->planetRVect = planetRVect;
  }

  double planetLongitude;
  double planetLatitude;
  double planetDistanceAU;
  double planetHLong1;
  double planetHLong2;
  double planetHLat;
  double planetRVect;
};

class CPlanetLongLatL4685 {
public:
  CPlanetLongLatL4685(double qa, double qb) {
    this->qa = qa;
    this->qb = qb;
  }

  double qa;
  double qb;
};

class CPlanetLongLatL4735 {
public:
  CPlanetLongLatL4735(double qa, double qb, double qc, double qe) {
    this->qa = qa;
    this->qb = qb;
    this->qc = qc;
    this->qe = qe;
  }

  double qa;
  double qb;
  double qc;
  double qe;
};

class CPlanetLongLatL4810 {
public:
  CPlanetLongLatL4810(double a, double sa, double ca, double qc, double qe,
                      double qa, double qb) {
    this->a = a;
    this->sa = sa;
    this->ca = ca;
    this->qc = qc;
    this->qe = qe;
    this->qa = qa;
    this->qb = qb;
  }

  double a;
  double sa;
  double ca;
  double qc;
  double qe;
  double qa;
  double qb;
};

class CPlanetLongLatL4945 {
public:
  CPlanetLongLatL4945(double qa, double qb, double qc, double qd, double qe,
                      double qf, double qg) {
    this->qa = qa;
    this->qb = qb;
    this->qc = qc;
    this->qd = qd;
    this->qe = qe;
    this->qf = qf;
    this->qg = qg;
  }

  double qa;
  double qb;
  double qc;
  double qd;
  double qe;
  double qf;
  double qg;
};

} // namespace pa_models
#endif
