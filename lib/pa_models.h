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

class CCometLongLatDist {
public:
  CCometLongLatDist(double longDeg, double latDeg, double distAU) {
    this->longDeg = longDeg;
    this->latDeg = latDeg;
    this->distAU = distAU;
  }

  double longDeg;
  double latDeg;
  double distAU;
};

class CBinaryStarOrbitalData {
public:
  CBinaryStarOrbitalData(double positionAngleDeg, double separationArcsec) {
    this->positionAngleDeg = positionAngleDeg;
    this->separationArcsec = separationArcsec;
  }

  double positionAngleDeg;
  double separationArcsec;
};

class CMoonApproximatePosition {
public:
  CMoonApproximatePosition(double raHour, double raMin, double raSec,
                           double decDeg, double decMin, double decSec) {
    this->raHour = raHour;
    this->raMin = raMin;
    this->raSec = raSec;
    this->decDeg = decDeg;
    this->decMin = decMin;
    this->decSec = decSec;
  }

  double raHour;
  double raMin;
  double raSec;
  double decDeg;
  double decMin;
  double decSec;
};

class CMoonPrecisePosition {
public:
  CMoonPrecisePosition(double raHour, double raMin, double raSec, double decDeg,
                       double decMin, double decSec, double earthMoonDistKM,
                       double horParallaxDeg) {
    this->raHour = raHour;
    this->raMin = raMin;
    this->raSec = raSec;
    this->decDeg = decDeg;
    this->decMin = decMin;
    this->decSec = decSec;
    this->earthMoonDistKM = earthMoonDistKM;
    this->horParallaxDeg = horParallaxDeg;
  }

  double raHour;
  double raMin;
  double raSec;
  double decDeg;
  double decMin;
  double decSec;
  double earthMoonDistKM;
  double horParallaxDeg;
};

class CMoonLongLatHP {
public:
  CMoonLongLatHP(double longitudeDegrees, double latitudeDegrees,
                 double horizontalParallax) {
    this->longitudeDegrees = longitudeDegrees;
    this->latitudeDegrees = latitudeDegrees;
    this->horizontalParallax = horizontalParallax;
  }

  double longitudeDegrees;
  double latitudeDegrees;
  double horizontalParallax;
};

class CMoonPhase {
public:
  CMoonPhase(double phase, double brightLimbDeg) {
    this->phase = phase;
    this->brightLimbDeg = brightLimbDeg;
  }

  double phase;
  double brightLimbDeg;
};

class CMoonNewFull {
public:
  CMoonNewFull(double nmLocalTimeHour, double nmLocalTimeMin,
               double nmLocalDateDay, int nmLocalDateMonth, int nmLocalDateYear,
               double fmLocalTimeHour, double fmLocalTimeMin,
               double fmLocalDateDay, int fmLocalDateMonth,
               int fmLocalDateYear) {
    this->nmLocalTimeHour = nmLocalTimeHour;
    this->nmLocalTimeMin = nmLocalTimeMin;
    this->nmLocalDateDay = nmLocalDateDay;
    this->nmLocalDateMonth = nmLocalDateMonth;
    this->nmLocalDateYear = nmLocalDateYear;
    this->fmLocalTimeHour = fmLocalTimeHour;
    this->fmLocalTimeMin = fmLocalTimeMin;
    this->fmLocalDateDay = fmLocalDateDay;
    this->fmLocalDateMonth = fmLocalDateMonth;
    this->fmLocalDateYear = fmLocalDateYear;
  }

  double nmLocalTimeHour;
  double nmLocalTimeMin;
  double nmLocalDateDay;
  int nmLocalDateMonth;
  int nmLocalDateYear;
  double fmLocalTimeHour;
  double fmLocalTimeMin;
  double fmLocalDateDay;
  int fmLocalDateMonth;
  int fmLocalDateYear;
};

class CNewMoonFullMoonL6855 {
public:
  CNewMoonFullMoonL6855(double a, double b, double f) {
    this->a = a;
    this->b = b;
    this->f = f;
  }

  double a;
  double b;
  double f;
};

class CMoonDistDiameterHP {
public:
  CMoonDistDiameterHP(double earthMoonDist, double angDiameterDeg,
                      double angDiameterMin, double horParallaxDeg,
                      double horParallaxMin, double horParallaxSec) {
    this->earthMoonDist = earthMoonDist;
    this->angDiameterDeg = angDiameterDeg;
    this->angDiameterMin = angDiameterMin;
    this->horParallaxDeg = horParallaxDeg;
    this->horParallaxMin = horParallaxMin;
    this->horParallaxSec = horParallaxSec;
  }

  double earthMoonDist;
  double angDiameterDeg;
  double angDiameterMin;
  double horParallaxDeg;
  double horParallaxMin;
  double horParallaxSec;
};

class CMoonRiseSet {
public:
  CMoonRiseSet(double mrLocalTimeHour, double mrLocalTimeMin,
               double mrLocalDateDay, int mrLocalDateMonth, int mrLocalDateYear,
               double mrAzimuthDeg, double msLocalTimeHour,
               double msLocalTimeMin, double msLocalDateDay,
               int msLocalDateMonth, int msLocalDateYear, double msAzimuthDeg) {
    this->mrLocalTimeHour = mrLocalTimeHour;
    this->mrLocalTimeMin = mrLocalTimeMin;
    this->mrLocalDateDay = mrLocalDateDay;
    this->mrLocalDateMonth = mrLocalDateMonth;
    this->mrLocalDateYear = mrLocalDateYear;
    this->mrAzimuthDeg = mrAzimuthDeg;
    this->msLocalTimeHour = msLocalTimeHour;
    this->msLocalTimeMin = msLocalTimeMin;
    this->msLocalDateDay = msLocalDateDay;
    this->msLocalDateMonth = msLocalDateMonth;
    this->msLocalDateYear = msLocalDateYear;
    this->msAzimuthDeg = msAzimuthDeg;
  }

  double mrLocalTimeHour;
  double mrLocalTimeMin;
  double mrLocalDateDay;
  int mrLocalDateMonth;
  int mrLocalDateYear;
  double mrAzimuthDeg;
  double msLocalTimeHour;
  double msLocalTimeMin;
  double msLocalDateDay;
  int msLocalDateMonth;
  int msLocalDateYear;
  double msAzimuthDeg;
};

class CMoonRiseLCTL6680 {
public:
  CMoonRiseLCTL6680(double ut, double lct, double dy1, int mn1, int yr1,
                    double gdy, int gmn, int gyr) {
    this->ut = ut;
    this->lct = lct;
    this->dy1 = dy1;
    this->mn1 = mn1;
    this->yr1 = yr1;
    this->gdy = gdy;
    this->gmn = gmn;
    this->gyr = gyr;
  }

  double ut;
  double lct;
  double dy1;
  int mn1;
  int yr1;
  double gdy;
  int gmn;
  int gyr;
};

class CMoonSetLCTL6680 {
public:
  CMoonSetLCTL6680(double ut, double lct, double dy1, int mn1, int yr1,
                   double gdy, int gmn, int gyr) {
    this->ut = ut;
    this->lct = lct;
    this->dy1 = dy1;
    this->mn1 = mn1;
    this->yr1 = yr1;
    this->gdy = gdy;
    this->gmn = gmn;
    this->gyr = gyr;
  }

  double ut;
  double lct;
  double dy1;
  int mn1;
  int yr1;
  double gdy;
  int gmn;
  int gyr;
};

class CMoonRiseLCTL6700 {
public:
  CMoonRiseLCTL6700(double mm, double bm, double pm, double dp, double th,
                    double di, double p, double q, double lu, double lct) {
    this->mm = mm;
    this->bm = bm;
    this->pm = pm;
    this->dp = dp;
    this->th = th;
    this->di = di;
    this->p = p;
    this->q = q;
    this->lu = lu;
    this->lct = lct;
  }

  double mm;
  double bm;
  double pm;
  double dp;
  double th;
  double di;
  double p;
  double q;
  double lu;
  double lct;
};

class CMoonSetLCTL6700 {
public:
  CMoonSetLCTL6700(double mm, double bm, double pm, double dp, double th,
                   double di, double p, double q, double lu, double lct) {
    this->mm = mm;
    this->bm = bm;
    this->pm = pm;
    this->dp = dp;
    this->th = th;
    this->di = di;
    this->p = p;
    this->q = q;
    this->lu = lu;
    this->lct = lct;
  }

  double mm;
  double bm;
  double pm;
  double dp;
  double th;
  double di;
  double p;
  double q;
  double lu;
  double lct;
};

class CMoonRiseLcDMYL6680 {
public:
  CMoonRiseLcDMYL6680(double ut, double lct, double dy1, int mn1, int yr1,
                      double gdy, int gmn, int gyr) {
    this->ut = ut;
    this->lct = lct;
    this->dy1 = dy1;
    this->mn1 = mn1;
    this->yr1 = yr1;
    this->gdy = gdy;
    this->gmn = gmn;
    this->gyr = gyr;
  }

  double ut;
  double lct;
  double dy1;
  int mn1;
  int yr1;
  double gdy;
  int gmn;
  int gyr;
};

class CMoonSetLcDMYL6680 {
public:
  CMoonSetLcDMYL6680(double ut, double lct, double dy1, int mn1, int yr1,
                     double gdy, int gmn, int gyr) {
    this->ut = ut;
    this->lct = lct;
    this->dy1 = dy1;
    this->mn1 = mn1;
    this->yr1 = yr1;
    this->gdy = gdy;
    this->gmn = gmn;
    this->gyr = gyr;
  }

  double ut;
  double lct;
  double dy1;
  int mn1;
  int yr1;
  double gdy;
  int gmn;
  int gyr;
};

class CMoonRiseLcDMYL6700 {
public:
  CMoonRiseLcDMYL6700(double mm, double bm, double pm, double dp, double th,
                      double di, double p, double q, double lu, double lct) {
    this->mm = mm;
    this->bm = bm;
    this->pm = pm;
    this->dp = dp;
    this->th = th;
    this->di = di;
    this->p = p;
    this->q = q;
    this->lu = lu;
    this->lct = lct;
  }

  double mm;
  double bm;
  double pm;
  double dp;
  double th;
  double di;
  double p;
  double q;
  double lu;
  double lct;
};

class CMoonSetLcDMYL6700 {
public:
  CMoonSetLcDMYL6700(double mm, double bm, double pm, double dp, double th,
                     double di, double p, double q, double lu, double lct) {
    this->mm = mm;
    this->bm = bm;
    this->pm = pm;
    this->dp = dp;
    this->th = th;
    this->di = di;
    this->p = p;
    this->q = q;
    this->lu = lu;
    this->lct = lct;
  }

  double mm;
  double bm;
  double pm;
  double dp;
  double th;
  double di;
  double p;
  double q;
  double lu;
  double lct;
};

class CMoonRiseAzL6680 {
public:
  CMoonRiseAzL6680(double ut, double lct, double dy1, int mn1, int yr1,
                   double gdy, int gmn, int gyr) {
    this->ut = ut;
    this->lct = lct;
    this->dy1 = dy1;
    this->mn1 = mn1;
    this->yr1 = yr1;
    this->gdy = gdy;
    this->gmn = gmn;
    this->gyr = gyr;
  }

  double ut;
  double lct;
  double dy1;
  int mn1;
  int yr1;
  double gdy;
  int gmn;
  int gyr;
};

class CMoonSetAzL6680 {
public:
  CMoonSetAzL6680(double ut, double lct, double dy1, int mn1, int yr1,
                  double gdy, int gmn, int gyr) {
    this->ut = ut;
    this->lct = lct;
    this->dy1 = dy1;
    this->mn1 = mn1;
    this->yr1 = yr1;
    this->gdy = gdy;
    this->gmn = gmn;
    this->gyr = gyr;
  }

  double ut;
  double lct;
  double dy1;
  int mn1;
  int yr1;
  double gdy;
  int gmn;
  int gyr;
};

class CMoonRiseAzL6700 {
public:
  CMoonRiseAzL6700(double mm, double bm, double pm, double dp, double th,
                   double di, double p, double q, double lu, double lct,
                   double au) {
    this->mm = mm;
    this->bm = bm;
    this->pm = pm;
    this->dp = dp;
    this->th = th;
    this->di = di;
    this->p = p;
    this->q = q;
    this->lu = lu;
    this->lct = lct;
    this->au = au;
  }

  double mm;
  double bm;
  double pm;
  double dp;
  double th;
  double di;
  double p;
  double q;
  double lu;
  double lct;
  double au;
};

class CMoonSetAzL6700 {
public:
  CMoonSetAzL6700(double mm, double bm, double pm, double dp, double th,
                  double di, double p, double q, double lu, double lct,
                  double au) {
    this->mm = mm;
    this->bm = bm;
    this->pm = pm;
    this->dp = dp;
    this->th = th;
    this->di = di;
    this->p = p;
    this->q = q;
    this->lu = lu;
    this->lct = lct;
    this->au = au;
  }

  double mm;
  double bm;
  double pm;
  double dp;
  double th;
  double di;
  double p;
  double q;
  double lu;
  double lct;
  double au;
};

class CFullDatePrecise {
public:
  CFullDatePrecise(int month, double day, int year) {
    this->month = month;
    this->day = day;
    this->year = year;
  }
  int month;
  double day;
  int year;
};

class CLunarEclipseOccurrence {
public:
  CLunarEclipseOccurrence(enum ELunarEclipseStatus status, double eventDateDay,
                          int eventDateMonth, int eventDateYear) {
    this->status = status;
    this->eventDateDay = eventDateDay;
    this->eventDateMonth = eventDateMonth;
    this->eventDateYear = eventDateYear;
  }

  enum ELunarEclipseStatus status;
  double eventDateDay;
  int eventDateMonth;
  int eventDateYear;
};

class CLunarEclipseOccurrenceL6855 {
public:
  CLunarEclipseOccurrenceL6855(double f, double dd, double e1, double b1,
                               double a, double b) {
    this->f = f;
    this->dd = dd;
    this->e1 = e1;
    this->b1 = b1;
    this->a = a;
    this->b = b;
  }

  double f;
  double dd;
  double e1;
  double b1;
  double a;
  double b;
};

class CLunarEclipseCircumstances {
public:
  CLunarEclipseCircumstances(
      double certainDateDay, double certainDateMonth, double certainDateYear,
      double utStartPenPhaseHour, double utStartPenPhaseMinutes,
      double utStartUmbralPhaseHour, double utStartUmbralPhaseMinutes,
      double utStartTotalPhaseHour, double utStartTotalPhaseMinutes,
      double utMidEclipseHour, double utMidEclipseMinutes,
      double utEndTotalPhaseHour, double utEndTotalPhaseMinutes,
      double utEndUmbralPhaseHour, double utEndUmbralPhaseMinutes,
      double utEndPenPhaseHour, double utEndPenPhaseMinutes,
      double eclipseMagnitude) {
    this->certainDateDay = certainDateDay;
    this->certainDateMonth = certainDateMonth;
    this->certainDateYear = certainDateYear;
    this->utStartPenPhaseHour = utStartPenPhaseHour;
    this->utStartPenPhaseMinutes = utStartPenPhaseMinutes;
    this->utStartUmbralPhaseHour = utStartUmbralPhaseHour;
    this->utStartUmbralPhaseMinutes = utStartUmbralPhaseMinutes;
    this->utStartTotalPhaseHour = utStartTotalPhaseHour;
    this->utStartTotalPhaseMinutes = utStartTotalPhaseMinutes;
    this->utMidEclipseHour = utMidEclipseHour;
    this->utMidEclipseMinutes = utMidEclipseMinutes;
    this->utEndTotalPhaseHour = utEndTotalPhaseHour;
    this->utEndTotalPhaseMinutes = utEndTotalPhaseMinutes;
    this->utEndUmbralPhaseHour = utEndUmbralPhaseHour;
    this->utEndUmbralPhaseMinutes = utEndUmbralPhaseMinutes;
    this->utEndPenPhaseHour = utEndPenPhaseHour;
    this->utEndPenPhaseMinutes = utEndPenPhaseMinutes;
    this->eclipseMagnitude = eclipseMagnitude;
  }

  double certainDateDay;
  double certainDateMonth;
  double certainDateYear;
  double utStartPenPhaseHour;
  double utStartPenPhaseMinutes;
  double utStartUmbralPhaseHour;
  double utStartUmbralPhaseMinutes;
  double utStartTotalPhaseHour;
  double utStartTotalPhaseMinutes;
  double utMidEclipseHour;
  double utMidEclipseMinutes;
  double utEndTotalPhaseHour;
  double utEndTotalPhaseMinutes;
  double utEndUmbralPhaseHour;
  double utEndUmbralPhaseMinutes;
  double utEndPenPhaseHour;
  double utEndPenPhaseMinutes;
  double eclipseMagnitude;
};

class CSolarEclipseOccurrence {
public:
  CSolarEclipseOccurrence(enum ESolarEclipseStatus status, double eventDateDay,
                          int eventDateMonth, int eventDateYear) {
    this->status = status;
    this->eventDateDay = eventDateDay;
    this->eventDateMonth = eventDateMonth;
    this->eventDateYear = eventDateYear;
  }

  enum ESolarEclipseStatus status;
  double eventDateDay;
  int eventDateMonth;
  int eventDateYear;
};

class CSolarEclipseOccurrenceL6855 {
public:
  CSolarEclipseOccurrenceL6855(double f, double dd, double e1, double b1,
                               double a, double b) {
    this->f = f;
    this->dd = dd;
    this->e1 = e1;
    this->b1 = b1;
    this->a = a;
    this->b = b;
  }

  double f;
  double dd;
  double e1;
  double b1;
  double a;
  double b;
};

class CSolarEclipseCircumstances {
public:
  CSolarEclipseCircumstances(double certainDateDay, int certainDateMonth,
                             int certainDateYear, double utFirstContactHour,
                             double utFirstContactMinutes,
                             double utMidEclipseHour,
                             double utMidEclipseMinutes,
                             double utLastContactHour,
                             double utLastContactMinutes,
                             double eclipseMagnitude) {
    this->certainDateDay = certainDateDay;
    this->certainDateMonth = certainDateMonth;
    this->certainDateYear = certainDateYear;
    this->utFirstContactHour = utFirstContactHour;
    this->utFirstContactMinutes = utFirstContactMinutes;
    this->utMidEclipseHour = utMidEclipseHour;
    this->utMidEclipseMinutes = utMidEclipseMinutes;
    this->utLastContactHour = utLastContactHour;
    this->utLastContactMinutes = utLastContactMinutes;
    this->eclipseMagnitude = eclipseMagnitude;
  }

  double certainDateDay;
  int certainDateMonth;
  int certainDateYear;
  double utFirstContactHour;
  double utFirstContactMinutes;
  double utMidEclipseHour;
  double utMidEclipseMinutes;
  double utLastContactHour;
  double utLastContactMinutes;
  double eclipseMagnitude;
};

class CUTMaxSolarEclipseL7390 {
public:
  CUTMaxSolarEclipseL7390(double paa, double qaa, double xaa, double pbb,
                          double qbb, double xbb, double p, double q) {
    this->paa = paa;
    this->qaa = qaa;
    this->xaa = xaa;
    this->pbb = pbb;
    this->qbb = qbb;
    this->xbb = xbb;
    this->p = p;
    this->q = q;
  }

  double paa;
  double qaa;
  double xaa;
  double pbb;
  double qbb;
  double xbb;
  double p;
  double q;
};

class CUTFirstContactSolarEclipseL7390 {
public:
  CUTFirstContactSolarEclipseL7390(double paa, double qaa, double xaa,
                                   double pbb, double qbb, double xbb, double p,
                                   double q) {
    this->paa = paa;
    this->qaa = qaa;
    this->xaa = xaa;
    this->pbb = pbb;
    this->qbb = qbb;
    this->xbb = xbb;
    this->p = p;
    this->q = q;
  }

  double paa;
  double qaa;
  double xaa;
  double pbb;
  double qbb;
  double xbb;
  double p;
  double q;
};

class CUTLastContactSolarEclipseL7390 {
public:
  CUTLastContactSolarEclipseL7390(double paa, double qaa, double xaa,
                                  double pbb, double qbb, double xbb, double p,
                                  double q) {
    this->paa = paa;
    this->qaa = qaa;
    this->xaa = xaa;
    this->pbb = pbb;
    this->qbb = qbb;
    this->xbb = xbb;
    this->p = p;
    this->q = q;
  }

  double paa;
  double qaa;
  double xaa;
  double pbb;
  double qbb;
  double xbb;
  double p;
  double q;
};

class CMagSolarEclipseL7390 {
public:
  CMagSolarEclipseL7390(double paa, double qaa, double xaa, double pbb,
                        double qbb, double xbb, double p, double q) {
    this->paa = paa;
    this->qaa = qaa;
    this->xaa = xaa;
    this->pbb = pbb;
    this->qbb = qbb;
    this->xbb = xbb;
    this->p = p;
    this->q = q;
  }

  double paa;
  double qaa;
  double xaa;
  double pbb;
  double qbb;
  double xbb;
  double p;
  double q;
};

} // namespace pa_models
#endif
