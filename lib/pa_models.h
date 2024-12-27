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
                 EWarningFlags warningFlag) {
    this->hours = hours;
    this->minutes = minutes;
    this->seconds = seconds;
    this->warningFlag = warningFlag;
  }

  int hours;
  int minutes;
  double seconds;
  EWarningFlags warningFlag;
};

class CAngle {
public:
  CAngle(double degrees, double minutes, double seconds) {
    this->degrees = degrees;
    this->minutes = minutes;
    this->seconds = seconds;
  }

  double degrees;
  double minutes;
  double seconds;
};

class CHourAngle {
public:
  CHourAngle(double hours, double minutes, double seconds) {
    this->hours = hours;
    this->minutes = minutes;
    this->seconds = seconds;
  }

  double hours;
  double minutes;
  double seconds;
};

class CRightAscension {
public:
  CRightAscension(double hours, double minutes, double seconds) {
    this->hours = hours;
    this->minutes = minutes;
    this->seconds = seconds;
  }

  double hours;
  double minutes;
  double seconds;
};

class CHorizonCoordinates {
public:
  CHorizonCoordinates(double azimuthDegrees, double azimuthMinutes,
                      double azimuthSeconds, double altitudeDegrees,
                      double altitudeMinutes, double altitudeSeconds) {
    this->azimuthDegrees = azimuthDegrees;
    this->azimuthMinutes = azimuthMinutes;
    this->azimuthSeconds = azimuthSeconds;
    this->altitudeDegrees = altitudeDegrees;
    this->altitudeMinutes = altitudeMinutes;
    this->altitudeSeconds = altitudeSeconds;
  }

  double azimuthDegrees;
  double azimuthMinutes;
  double azimuthSeconds;
  double altitudeDegrees;
  double altitudeMinutes;
  double altitudeSeconds;
};

class CEquatorialCoordinatesHA {
public:
  CEquatorialCoordinatesHA(double hourAngleHours, double hourAngleMinutes,
                           double hourAngleSeconds, double declinationDegrees,
                           double declinationMinutes,
                           double declinationSeconds) {
    this->hourAngleHours = hourAngleHours;
    this->hourAngleMinutes = hourAngleMinutes;
    this->hourAngleSeconds = hourAngleSeconds;
    this->declinationDegrees = declinationDegrees;
    this->declinationMinutes = declinationMinutes;
    this->declinationSeconds = declinationSeconds;
  }

  double hourAngleHours;
  double hourAngleMinutes;
  double hourAngleSeconds;
  double declinationDegrees;
  double declinationMinutes;
  double declinationSeconds;
};

class CEquatorialCoordinatesRA {
public:
  CEquatorialCoordinatesRA(double rightAscensionHours,
                           double rightAscensionMinutes,
                           double rightAscensionSeconds,
                           double declinationDegrees, double declinationMinutes,
                           double declinationSeconds) {
    this->rightAscensionHours = rightAscensionHours;
    this->rightAscensionMinutes = rightAscensionMinutes;
    this->rightAscensionSeconds = rightAscensionSeconds;
    this->declinationDegrees = declinationDegrees;
    this->declinationMinutes = declinationMinutes;
    this->declinationSeconds = declinationSeconds;
  }

  double rightAscensionHours;
  double rightAscensionMinutes;
  double rightAscensionSeconds;
  double declinationDegrees;
  double declinationMinutes;
  double declinationSeconds;
};

class CEqlipticCoordinates {
public:
  CEqlipticCoordinates(double longitudeDegrees, double longitudeMinutes,
                       double longitudeSeconds, double latitudeDegrees,
                       double latitudeMinutes, double latitudeSeconds) {
    this->longitudeDegrees = longitudeDegrees;
    this->longitudeMinutes = longitudeMinutes;
    this->longitudeSeconds = longitudeSeconds;
    this->latitudeDegrees = latitudeDegrees;
    this->latitudeMinutes = latitudeMinutes;
    this->latitudeSeconds = latitudeSeconds;
  }

  double longitudeDegrees;
  double longitudeMinutes;
  double longitudeSeconds;
  double latitudeDegrees;
  double latitudeMinutes;
  double latitudeSeconds;
};

class CGalacticCoordinates {
public:
  CGalacticCoordinates(double longitudeDegrees, double longitudeMinutes,
                       double longitudeSeconds, double latitudeDegrees,
                       double latitudeMinutes, double latitudeSeconds) {
    this->longitudeDegrees = longitudeDegrees;
    this->longitudeMinutes = longitudeMinutes;
    this->longitudeSeconds = longitudeSeconds;
    this->latitudeDegrees = latitudeDegrees;
    this->latitudeMinutes = latitudeMinutes;
    this->latitudeSeconds = latitudeSeconds;
  }

  double longitudeDegrees;
  double longitudeMinutes;
  double longitudeSeconds;
  double latitudeDegrees;
  double latitudeMinutes;
  double latitudeSeconds;
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

class CRiseSet {
public:
  CRiseSet(ERiseSetStatus rsStatus, double utRiseHour, double utRiseMin,
           double utSetHour, double utSetMin, double azRise, double azSet) {
    this->rsStatus = rsStatus;
    this->utRiseHour = utRiseHour;
    this->utRiseMin = utRiseMin;
    this->utSetHour = utSetHour;
    this->utSetMin = utSetMin;
    this->azRise = azRise;
    this->azSet = azSet;
  }

  ERiseSetStatus rsStatus;
  double utRiseHour;
  double utRiseMin;
  double utSetHour;
  double utSetMin;
  double azRise;
  double azSet;
};

class CPrecession {
public:
  CPrecession(double correctedRaHour, double correctedRaMinutes,
              double correctedRaSeconds, double correctedDecDeg,
              double correctedDecMinutes, double correctedDecSeconds) {
    this->correctedRaHour = correctedRaHour;
    this->correctedRaMinutes = correctedRaMinutes;
    this->correctedRaSeconds = correctedRaSeconds;
    this->correctedDecDeg = correctedDecDeg;
    this->correctedDecMinutes = correctedDecMinutes;
    this->correctedDecSeconds = correctedDecSeconds;
  }

  double correctedRaHour;
  double correctedRaMinutes;
  double correctedRaSeconds;
  double correctedDecDeg;
  double correctedDecMinutes;
  double correctedDecSeconds;
};

class CNutation {
public:
  CNutation(double nutInLongDeg, double nutInOblDeg) {
    this->nutInLongDeg = nutInLongDeg;
    this->nutInOblDeg = nutInOblDeg;
  }

  double nutInLongDeg;
  double nutInOblDeg;
};

class CAberration {
public:
  CAberration(double apparentEclLongDeg, double apparentEclLongMin,
              double apparentEclLongSec, double apparentEclLatDeg,
              double apparentEclLatMin, double apparentEclLatSec) {
    this->apparentEclLongDeg = apparentEclLongDeg;
    this->apparentEclLongMin = apparentEclLongMin;
    this->apparentEclLongSec = apparentEclLongSec;
    this->apparentEclLatDeg = apparentEclLatDeg;
    this->apparentEclLatMin = apparentEclLatMin;
    this->apparentEclLatSec = apparentEclLatSec;
  }

  double apparentEclLongDeg;
  double apparentEclLongMin;
  double apparentEclLongSec;
  double apparentEclLatDeg;
  double apparentEclLatMin;
  double apparentEclLatSec;
};

class CAtmosphericRefraction {
public:
  CAtmosphericRefraction(double correctedRaHour, double correctedRaMin,
                         double correctedRaSec, double correctedDecDeg,
                         double correctedDecMin, double correctedDecSec) {
    this->correctedRaHour = correctedRaHour;
    this->correctedRaMin = correctedRaMin;
    this->correctedRaSec = correctedRaSec;
    this->correctedDecDeg = correctedDecDeg;
    this->correctedDecMin = correctedDecMin;
    this->correctedDecSec = correctedDecSec;
  }

  double correctedRaHour;
  double correctedRaMin;
  double correctedRaSec;
  double correctedDecDeg;
  double correctedDecMin;
  double correctedDecSec;
};

class CGeocentricParallax {
public:
  CGeocentricParallax(double correctedRaHour, double correctedRaMin,
                      double correctedRaSec, double correctedDecDeg,
                      double correctedDecMin, double correctedDecSec) {
    this->correctedRaHour = correctedRaHour;
    this->correctedRaMin = correctedRaMin;
    this->correctedRaSec = correctedRaSec;
    this->correctedDecDeg = correctedDecDeg;
    this->correctedDecMin = correctedDecMin;
    this->correctedDecSec = correctedDecSec;
  }

  double correctedRaHour;
  double correctedRaMin;
  double correctedRaSec;
  double correctedDecDeg;
  double correctedDecMin;
  double correctedDecSec;
};

class CHeliographicCoordinates {
public:
  CHeliographicCoordinates(double longitudeDegrees, double latitudeDegrees) {
    this->longitudeDegrees = longitudeDegrees;
    this->latitudeDegrees = latitudeDegrees;
  }

  double longitudeDegrees;
  double latitudeDegrees;
};

class CSelenographicCoordinates1 {
public:
  CSelenographicCoordinates1(double subEarthLongitude, double subEarthLatitude,
                             double positionAngleOfPole) {
    this->subEarthLongitude = subEarthLongitude;
    this->subEarthLatitude = subEarthLatitude;
    this->positionAngleOfPole = positionAngleOfPole;
  }

  double subEarthLongitude;
  double subEarthLatitude;
  double positionAngleOfPole;
};

class CSelenographicCoordinates2 {
public:
  CSelenographicCoordinates2(double subSolarLongitude,
                             double subSolarColongitude,
                             double subSolarLatitude) {
    this->subSolarLongitude = subSolarLongitude;
    this->subSolarColongitude = subSolarColongitude;
    this->subSolarLatitude = subSolarLatitude;
  }

  double subSolarLongitude;
  double subSolarColongitude;
  double subSolarLatitude;
};

class CApproximatePositionOfSun {
public:
  CApproximatePositionOfSun(double rightAscensionHours,
                            double rightAscensionMinutes,
                            double rightAscensionSeconds,
                            double declinationDegrees,
                            double declinationMinutes,
                            double declinationSeconds) {
    this->rightAscensionHours = rightAscensionHours;
    this->rightAscensionMinutes = rightAscensionMinutes;
    this->rightAscensionSeconds = rightAscensionSeconds;
    this->declinationDegrees = declinationDegrees;
    this->declinationMinutes = declinationMinutes;
    this->declinationSeconds = declinationSeconds;
  }

  double rightAscensionHours;
  double rightAscensionMinutes;
  double rightAscensionSeconds;
  double declinationDegrees;
  double declinationMinutes;
  double declinationSeconds;
};

class CPrecisePositionOfSun {
public:
  CPrecisePositionOfSun(double rightAscensionHours,
                        double rightAscensionMinutes,
                        double rightAscensionSeconds, double declinationDegrees,
                        double declinationMinutes, double declinationSeconds) {
    this->rightAscensionHours = rightAscensionHours;
    this->rightAscensionMinutes = rightAscensionMinutes;
    this->rightAscensionSeconds = rightAscensionSeconds;
    this->declinationDegrees = declinationDegrees;
    this->declinationMinutes = declinationMinutes;
    this->declinationSeconds = declinationSeconds;
  }

  double rightAscensionHours;
  double rightAscensionMinutes;
  double rightAscensionSeconds;
  double declinationDegrees;
  double declinationMinutes;
  double declinationSeconds;
};

class CSunDistanceAngularSize {
public:
  CSunDistanceAngularSize(double distKm, double angSizeDeg, double angSizeMin,
                          double angSizeSec) {
    this->distKm = distKm;
    this->angSizeDeg = angSizeDeg;
    this->angSizeMin = angSizeMin;
    this->angSizeSec = angSizeSec;
  };

  double distKm;
  double angSizeDeg;
  double angSizeMin;
  double angSizeSec;
};

class CSunriseAndSunset {
public:
  CSunriseAndSunset(double localSunriseHour, double localSunriseMinute,
                    double localSunsetHour, double localSunsetMinute,
                    double azimuthOfSunriseDeg, double azimuthOfSunsetDeg,
                    ERiseSetStatus status) {
    this->localSunriseHour = localSunsetHour;
    this->localSunriseMinute = localSunsetMinute;
    this->localSunsetHour = localSunsetHour;
    this->localSunsetMinute = localSunsetMinute;
    this->azimuthOfSunriseDeg = azimuthOfSunriseDeg;
    this->azimuthOfSunsetDeg = azimuthOfSunsetDeg;
    this->status = status;
  }

  double localSunriseHour;
  double localSunriseMinute;
  double localSunsetHour;
  double localSunsetMinute;
  double azimuthOfSunriseDeg;
  double azimuthOfSunsetDeg;
  ERiseSetStatus status;
};

class CMorningAndEveningTwilight {
public:
  CMorningAndEveningTwilight(double amTwilightBeginsHour,
                             double amTwilightBeginsMin,
                             double pmTwilightEndsHour,
                             double pmTwilightEndsMin, ETwilightStatus status) {
    this->amTwilightBeginsHour = amTwilightBeginsHour;
    this->amTwilightBeginsMin = amTwilightBeginsMin;
    this->pmTwilightEndsHour = pmTwilightEndsHour;
    this->pmTwilightEndsMin = pmTwilightEndsMin;
    this->status = status;
  }

  double amTwilightBeginsHour;
  double amTwilightBeginsMin;
  double pmTwilightEndsHour;
  double pmTwilightEndsMin;
  ETwilightStatus status;
};

class CEquationOfTime {
public:
  CEquationOfTime(double minutes, double seconds) {
    this->minutes = minutes;
    this->seconds = seconds;
  }

  double minutes;
  double seconds;
};

class CCometPosition {
public:
  CCometPosition(double raHour, double raMin, double raSec, double decDeg,
                 double decMin, double decSec, double distEarth) {
    this->raHour = raHour;
    this->raMin = raMin;
    this->raSec = raSec;
    this->decDeg = decDeg;
    this->decMin = decMin;
    this->decSec = decSec;
    this->distEarth = distEarth;
  }

  double raHour;
  double raMin;
  double raSec;
  double decDeg;
  double decMin;
  double decSec;
  double distEarth;
};

} // namespace pa_models
#endif
