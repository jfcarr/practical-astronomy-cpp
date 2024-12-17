#ifndef _pa_models
#define _pa_models

#include "pa_types.h"

using namespace pa_types;

namespace pa_models {

class CMonthDayYear {
public:
  CMonthDayYear(int month, int day, int year) {
    this->month = month;
    this->day = day;
    this->year = year;
  }

  int month;
  int day;
  int year;
};

class CCivilTime {
public:
  CCivilTime(double hours, double minutes, double seconds) {
    this->hours = hours;
    this->minutes = minutes;
    this->seconds = seconds;
  }

  double hours;
  double minutes;
  double seconds;
};

class CUniversalDateTime {
public:
  CUniversalDateTime(int hours, int minutes, int seconds, int day, int month,
                     int year) {
    this->hours = hours;
    this->minutes = minutes;
    this->seconds = seconds;
    this->day = day;
    this->month = month;
    this->year = year;
  }

  int hours;
  int minutes;
  int seconds;
  int day;
  int month;
  int year;
};

class CCivilDateTime : public CUniversalDateTime {
public:
  CCivilDateTime(int hours, int minutes, int seconds, int day, int month,
                 int year)
      : CUniversalDateTime(hours, minutes, seconds, day, month, year) {}
};

class CGreenwichSiderealTime {
public:
  CGreenwichSiderealTime(int hours, int minutes, double seconds) {
    this->hours = hours;
    this->minutes = minutes;
    this->seconds = seconds;
  }

  int hours;
  int minutes;
  double seconds;
};

class CLocalSiderealTime : public CGreenwichSiderealTime {
public:
  CLocalSiderealTime(int hours, int minutes, double seconds)
      : CGreenwichSiderealTime(hours, minutes, seconds) {}
};

class CUniversalTime {
public:
  CUniversalTime(int hours, int minutes, double seconds,
                 WarningFlags warningFlag) {
    this->hours = hours;
    this->minutes = minutes;
    this->seconds = seconds;
    this->warningFlag = warningFlag;
  }

  int hours;
  int minutes;
  double seconds;
  WarningFlags warningFlag;
};

class CApproximatePositionOfPlanet {
public:
  CApproximatePositionOfPlanet(double planetRAHour, double planetRAMin,
                               double planetRASec, double planetDecDeg,
                               double planetDecMin, double planetDecSec) {
    this->planetRAHour = planetRAHour;
    this->planetRAMin = planetRAMin;
    this->planetRASec = planetRASec;
    this->planetDecDeg = planetDecDeg;
    this->planetDecMin = planetDecMin;
    this->planetDecSec = planetDecSec;
  }

  double planetRAHour;
  double planetRAMin;
  double planetRASec;
  double planetDecDeg;
  double planetDecMin;
  double planetDecSec;
};

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

class CPlanetVisualAspects {
public:
  CPlanetVisualAspects(double distanceAU, double angDiaArcsec, double phase,
                       double lightTimeHour, double lightTimeMinutes,
                       double lightTimeSeconds, double posAngleBrightLimbDeg,
                       double approximateMagnitude) {
    this->distanceAU = distanceAU;
    this->angDiaArcsec = angDiaArcsec;
    this->phase = phase;
    this->lightTimeHour = lightTimeHour;
    this->lightTimeMinutes = lightTimeMinutes;
    this->lightTimeSeconds = lightTimeSeconds;
    this->posAngleBrightLimbDeg = posAngleBrightLimbDeg;
    this->approximateMagnitude = approximateMagnitude;
  }

  double distanceAU;
  double angDiaArcsec;
  double phase;
  double lightTimeHour;
  double lightTimeMinutes;
  double lightTimeSeconds;
  double posAngleBrightLimbDeg;
  double approximateMagnitude;
};

} // namespace pa_models
#endif
