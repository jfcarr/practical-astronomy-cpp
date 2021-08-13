#include "pa_coordinates.h"
#include "pa_macros.h"
#include "pa_types.h"
#include "pa_util.h"
#include <cmath>

using namespace pa_types;
using namespace pa_util;
using namespace pa_macros;

/**
 * \brief Convert Angle (degrees,minutes,seconds) to Decimal Degrees
 *
 * @param degrees
 * @param minutes
 * @param seconds
 *
 * @return Decimal Degrees
 */
double PACoordinates::AngleToDecimalDegrees(double degrees, double minutes,
                                            double seconds) {
  double a = std::abs(seconds) / 60;
  double b = (std::abs(minutes) + a) / 60;
  double c = std::abs(degrees) + b;
  double d = (degrees < 0 || minutes < 0 || seconds < 0) ? -c : c;

  return d;
}

/**
 * \brief Convert Decimal Degrees to an Angle (degrees, minutes, and seconds)
 *
 * @param decimalDegrees
 *
 * @return tuple <double degrees, double minutes, double seconds>
 */
std::tuple<double, double, double>
PACoordinates::DecimalDegreesToAngle(double decimalDegrees) {
  double unsignedDecimal = std::abs(decimalDegrees);
  double totalSeconds = unsignedDecimal * 3600;
  double seconds2dp = Round(std::fmod(totalSeconds, 60), 2);
  double correctedSeconds = (seconds2dp == 60) ? 0 : seconds2dp;
  double correctedRemainder =
      (seconds2dp == 60) ? totalSeconds + 60 : totalSeconds;
  double minutes = std::fmod(floor(correctedRemainder / 60), 60);
  double unsignedDegrees = floor(correctedRemainder / 3600);
  double signedDegrees =
      (decimalDegrees < 0) ? -1 * unsignedDegrees : unsignedDegrees;

  return std::tuple<double, double, double>{signedDegrees, minutes,
                                            floor(correctedSeconds)};
}

/**
 * \brief Convert Right Ascension to Hour Angle
 *
 * @return tuple <double hour_angle_hours, double hour_angle_minutes, double
 * hour_angle_seconds>
 */
std::tuple<double, double, double> PACoordinates::RightAscensionToHourAngle(
    double raHours, double raMinutes, double raSeconds, double lctHours,
    double lctMinutes, double lctSeconds, bool isDaylightSavings,
    int zoneCorrection, double localDay, int localMonth, int localYear,
    double geographicalLongitude) {
  int daylightSaving = (isDaylightSavings) ? 1 : 0;

  double hourAngle = pa_macros::RightAscensionToHourAngle(
      raHours, raMinutes, raSeconds, lctHours, lctMinutes, lctSeconds,
      daylightSaving, zoneCorrection, localDay, localMonth, localYear,
      geographicalLongitude);

  int hourAngleHours = DecimalHoursHour(hourAngle);
  int hourAngleMinutes = DecimalHoursMinute(hourAngle);
  double hourAngleSeconds = DecimalHoursSecond(hourAngle);

  return std::tuple<double, double, double>{hourAngleHours, hourAngleMinutes,
                                            hourAngleSeconds};
}

/**
 * \brief Convert Hour Angle to Right Ascension
 *
 * @return tuple <double right_ascension_hours, double right_ascension_minutes,
 * double right_ascension_seconds>
 */
std::tuple<double, double, double> PACoordinates::HourAngleToRightAscension(
    double hourAngleHours, double hourAngleMinutes, double hourAngleSeconds,
    double lctHours, double lctMinutes, double lctSeconds,
    bool isDaylightSavings, int zoneCorrection, double localDay, int localMonth,
    int localYear, double geographicalLongitude) {
  int daylightSaving = (isDaylightSavings) ? 1 : 0;

  double rightAscension = pa_macros::HourAngleToRightAscension(
      hourAngleHours, hourAngleMinutes, hourAngleSeconds, lctHours, lctMinutes,
      lctSeconds, daylightSaving, zoneCorrection, localDay, localMonth,
      localYear, geographicalLongitude);

  int rightAscensionHours = DecimalHoursHour(rightAscension);
  int rightAscensionMinutes = DecimalHoursMinute(rightAscension);
  int rightAscensionSeconds = DecimalHoursSecond(rightAscension);

  return std::tuple<double, double, double>{
      rightAscensionHours, rightAscensionMinutes, rightAscensionSeconds};
}

/**
 * \brief Convert Equatorial Coordinates to Horizon Coordinates
 *
 * @return tuple <double azimuthDegrees, double azimuthMinutes, double
 * azimuthSeconds, double altitudeDegrees, double altitudeMinutes, double
 * altitudeSeconds>
 */
std::tuple<double, double, double, double, double, double>
PACoordinates::EquatorialCoordinatesToHorizonCoordinates(
    double hourAngleHours, double hourAngleMinutes, double hourAngleSeconds,
    double declinationDegrees, double declinationMinutes,
    double declinationSeconds, double geographicalLatitude) {
  double azimuthInDecimalDegrees = EquatorialCoordinatesToAzimuth(
      hourAngleHours, hourAngleMinutes, hourAngleSeconds, declinationDegrees,
      declinationMinutes, declinationSeconds, geographicalLatitude);

  double altitudeInDecimalDegrees = EquatorialCoordinatesToAltitude(
      hourAngleHours, hourAngleMinutes, hourAngleSeconds, declinationDegrees,
      declinationMinutes, declinationSeconds, geographicalLatitude);

  double azimuthDegrees = DecimalDegreesDegrees(azimuthInDecimalDegrees);
  double azimuthMinutes = DecimalDegreesMinutes(azimuthInDecimalDegrees);
  double azimuthSeconds = DecimalDegreesSeconds(azimuthInDecimalDegrees);

  double altitudeDegrees = DecimalDegreesDegrees(altitudeInDecimalDegrees);
  double altitudeMinutes = DecimalDegreesMinutes(altitudeInDecimalDegrees);
  double altitudeSeconds = DecimalDegreesSeconds(altitudeInDecimalDegrees);

  return std::tuple<double, double, double, double, double, double>{
      azimuthDegrees,  azimuthMinutes,  azimuthSeconds,
      altitudeDegrees, altitudeMinutes, altitudeSeconds};
}

/**
 * \brief Convert Horizon Coordinates to Equatorial Coordinates
 *
 * @return tuple <double hour_angle_hours, double hour_angle_minutes, double
 * hour_angle-seconds, double declination_degrees, double declination_minutes,
 * double declination_seconds>
 */
std::tuple<double, double, double, double, double, double>
PACoordinates::HorizonCoordinatesToEquatorialCoordinates(
    double azimuthDegrees, double azimuthMinutes, double azimuthSeconds,
    double altitudeDegrees, double altitudeMinutes, double altitudeSeconds,
    double geographicalLatitude) {
  double hourAngleInDecimalDegrees = HorizonCoordinatesToHourAngle(
      azimuthDegrees, azimuthMinutes, azimuthSeconds, altitudeDegrees,
      altitudeMinutes, altitudeSeconds, geographicalLatitude);

  double declinationInDecimalDegrees = HorizonCoordinatesToDeclination(
      azimuthDegrees, azimuthMinutes, azimuthSeconds, altitudeDegrees,
      altitudeMinutes, altitudeSeconds, geographicalLatitude);

  int hourAngleHours = DecimalHoursHour(hourAngleInDecimalDegrees);
  int hourAngleMinutes = DecimalHoursMinute(hourAngleInDecimalDegrees);
  double hourAngleSeconds = DecimalHoursSecond(hourAngleInDecimalDegrees);

  double declinationDegrees =
      DecimalDegreesDegrees(declinationInDecimalDegrees);
  double declinationMinutes =
      DecimalDegreesMinutes(declinationInDecimalDegrees);
  double declinationSeconds =
      DecimalDegreesSeconds(declinationInDecimalDegrees);

  return std::tuple<double, double, double, double, double, double>{
      hourAngleHours,     hourAngleMinutes,   hourAngleSeconds,
      declinationDegrees, declinationMinutes, declinationSeconds};
}

/**
 * \brief Calculate Mean Obliquity of the Ecliptic for a Greenwich Date
 */
double PACoordinates::MeanObliquityOfTheEcliptic(double greenwichDay,
                                                 int greenwichMonth,
                                                 int greenwichYear) {
  double jd =
      CivilDateToJulianDate(greenwichDay, greenwichMonth, greenwichYear);
  double mjd = jd - 2451545;
  double t = mjd / 36525;
  double de1 = t * (46.815 + t * (0.0006 - (t * 0.00181)));
  double de2 = de1 / 3600;

  return 23.439292 - de2;
}

/**
 * \brief Convert Ecliptic Coordinates to Equatorial Coordinates
 *
 * @return tuple <double outRAHours, double outRAMinutes, double outRASeconds,
 * double outDecDegrees, double outDecMinutes, double outDecSeconds>
 */
std::tuple<double, double, double, double, double, double>
PACoordinates::EclipticCoordinateToEquatorialCoordinate(
    double eclipticLongitudeDegrees, double eclipticLongitudeMinutes,
    double eclipticLongitudeSeconds, double eclipticLatitudeDegrees,
    double eclipticLatitudeMinutes, double eclipticLatitudeSeconds,
    double greenwichDay, int greenwichMonth, int greenwichYear) {
  double ecLonDeg = DegreesMinutesSecondsToDecimalDegrees(
      eclipticLongitudeDegrees, eclipticLongitudeMinutes,
      eclipticLongitudeSeconds);
  double ecLatDeg = DegreesMinutesSecondsToDecimalDegrees(
      eclipticLatitudeDegrees, eclipticLatitudeMinutes,
      eclipticLatitudeSeconds);
  double ecLonRad = DegreesToRadians(ecLonDeg);
  double ecLatRad = DegreesToRadians(ecLatDeg);
  double obliqDeg = Obliq(greenwichDay, greenwichMonth, greenwichYear);
  double obliqRad = DegreesToRadians(obliqDeg);
  double sinDec = sin(ecLatRad) * cos(obliqRad) +
                  cos(ecLatRad) * sin(obliqRad) * sin(ecLonRad);
  double decRad = asin(sinDec);
  double decDeg = WToDegrees(decRad);
  double y = sin(ecLonRad) * cos(obliqRad) - tan(ecLatRad) * sin(obliqRad);
  double x = cos(ecLonRad);
  double raRad = atan2(y, x);
  double raDeg1 = WToDegrees(raRad);
  double raDeg2 = raDeg1 - 360 * floor(raDeg1 / 360);
  double raHours = DecimalDegreesToDegreeHours(raDeg2);

  int outRaHours = DecimalHoursHour(raHours);
  int outRaMinutes = DecimalHoursMinute(raHours);
  double outRaSeconds = DecimalHoursSecond(raHours);
  double outDecDegrees = DecimalDegreesDegrees(decDeg);
  double outDecMinutes = DecimalDegreesMinutes(decDeg);
  double outDecSeconds = DecimalDegreesSeconds(decDeg);

  return std::tuple<double, double, double, double, double, double>{
      outRaHours,    outRaMinutes,  outRaSeconds,
      outDecDegrees, outDecMinutes, outDecSeconds};
}

/**
 * \brief Convert Equatorial Coordinates to Ecliptic Coordinates
 *
 * @return tuple <double outEclLongDeg, double outEclLongMin, double
 * outEclLongSec, double outEclLatDeg, double outEclLatMin, double outEclLatSec>
 */
std::tuple<double, double, double, double, double, double>
PACoordinates::EquatorialCoordinateToEclipticCoordinate(
    double raHours, double raMinutes, double raSeconds, double decDegrees,
    double decMinutes, double decSeconds, double gwDay, int gwMonth,
    int gwYear) {
  double raDeg =
      DegreeHoursToDecimalDegrees(HmsToDh(raHours, raMinutes, raSeconds));
  double decDeg =
      DegreesMinutesSecondsToDecimalDegrees(decDegrees, decMinutes, decSeconds);
  double raRad = DegreesToRadians(raDeg);
  double decRad = DegreesToRadians(decDeg);
  double obliqDeg = Obliq(gwDay, gwMonth, gwYear);
  double obliqRad = DegreesToRadians(obliqDeg);
  double sinEclRad =
      sin(decRad) * cos(obliqRad) - cos(decRad) * sin(obliqRad) * sin(raRad);
  double eclLatRad = asin(sinEclRad);
  double eclLatDeg = WToDegrees(eclLatRad);
  double y = sin(raRad) * cos(obliqRad) + tan(decRad) * sin(obliqRad);
  double x = cos(raRad);
  double eclLongRad = atan2(y, x);
  double eclLongDeg1 = WToDegrees(eclLongRad);
  double eclLongDeg2 = eclLongDeg1 - 360 * floor(eclLongDeg1 / 360);

  double outEclLongDeg = DecimalDegreesDegrees(eclLongDeg2);
  double outEclLongMin = DecimalDegreesMinutes(eclLongDeg2);
  double outEclLongSec = DecimalDegreesSeconds(eclLongDeg2);
  double outEclLatDeg = DecimalDegreesDegrees(eclLatDeg);
  double outEclLatMin = DecimalDegreesMinutes(eclLatDeg);
  double outEclLatSec = DecimalDegreesSeconds(eclLatDeg);

  return std::tuple<double, double, double, double, double, double>{
      outEclLongDeg, outEclLongMin, outEclLongSec,
      outEclLatDeg,  outEclLatMin,  outEclLatSec};
}

/**
 * \brief Convert Equatorial Coordinates to Galactic Coordinates
 *
 * @return tuple <double galLongDeg, double galLongMin, double galLongSec,
 * double galLatDeg, double galLatMin, double galLatSec>
 */
std::tuple<double, double, double, double, double, double>
PACoordinates::EquatorialCoordinateToGalacticCoordinate(
    double raHours, double raMinutes, double raSeconds, double decDegrees,
    double decMinutes, double decSeconds) {
  double raDeg =
      DegreeHoursToDecimalDegrees(HmsToDh(raHours, raMinutes, raSeconds));
  double decDeg =
      DegreesMinutesSecondsToDecimalDegrees(decDegrees, decMinutes, decSeconds);
  double raRad = DegreesToRadians(raDeg);
  double decRad = DegreesToRadians(decDeg);
  double sinB = cos(decRad) * cos(DegreesToRadians(27.4)) *
                    cos(raRad - DegreesToRadians(192.25)) +
                sin(decRad) * sin(DegreesToRadians(27.4));
  double bRadians = asin(sinB);
  double bDeg = WToDegrees(bRadians);
  double y = sin(decRad) - sinB * sin(DegreesToRadians(27.4));
  double x = cos(decRad) * sin(raRad - DegreesToRadians(192.25)) *
             cos(DegreesToRadians(27.4));
  double longDeg1 = WToDegrees(atan2(y, x)) + 33;
  double longDeg2 = longDeg1 - 360 * floor(longDeg1 / 360);

  double galLongDeg = DecimalDegreesDegrees(longDeg2);
  double galLongMin = DecimalDegreesMinutes(longDeg2);
  double galLongSec = DecimalDegreesSeconds(longDeg2);
  double galLatDeg = DecimalDegreesDegrees(bDeg);
  double galLatMin = DecimalDegreesMinutes(bDeg);
  double galLatSec = DecimalDegreesSeconds(bDeg);

  return std::tuple<double, double, double, double, double, double>{
      galLongDeg, galLongMin, galLongSec, galLatDeg, galLatMin, galLatSec};
}

/**
 * \brief Convert Galactic Coordinates to Equatorial Coordinates
 *
 * @return tuple <double raHours, double raMinutes, double raSeconds, double
 * decDegrees, double decMinutes, double decSeconds>
 */
std::tuple<double, double, double, double, double, double>
PACoordinates::GalacticCoordinateToEquatorialCoordinate(
    double galLongDeg, double galLongMin, double galLongSec, double galLatDeg,
    double galLatMin, double galLatSec) {
  double gLongDeg =
      DegreesMinutesSecondsToDecimalDegrees(galLongDeg, galLongMin, galLongSec);
  double gLatDeg =
      DegreesMinutesSecondsToDecimalDegrees(galLatDeg, galLatMin, galLatSec);
  double gLongRad = DegreesToRadians(gLongDeg);
  double gLatRad = DegreesToRadians(gLatDeg);
  double sinDec = cos(gLatRad) * cos(DegreesToRadians(27.4)) *
                      sin(gLongRad - DegreesToRadians(33.0)) +
                  sin(gLatRad) * sin(DegreesToRadians(27.4));
  double decRadians = asin(sinDec);
  double decDeg = WToDegrees(decRadians);
  double y = cos(gLatRad) * cos(gLongRad - DegreesToRadians(33.0));
  double x = sin(gLatRad) * cos(DegreesToRadians(27.4)) -
             cos(gLatRad) * sin(DegreesToRadians(27.4)) *
                 sin(gLongRad - DegreesToRadians(33.0));

  double raDeg1 = WToDegrees(atan2(y, x)) + 192.25;
  double raDeg2 = raDeg1 - 360 * floor(raDeg1 / 360);
  double raHours1 = DecimalDegreesToDegreeHours(raDeg2);

  double raHours = DecimalHoursHour(raHours1);
  double raMinutes = DecimalHoursMinute(raHours1);
  double raSeconds = DecimalHoursSecond(raHours1);
  double decDegrees = DecimalDegreesDegrees(decDeg);
  double decMinutes = DecimalDegreesMinutes(decDeg);
  double decSeconds = DecimalDegreesSeconds(decDeg);

  return std::tuple<double, double, double, double, double, double>{
      raHours, raMinutes, raSeconds, decDegrees, decMinutes, decSeconds};
}

/**
 * \brief Calculate the angle between two celestial objects
 *
 * @return tuple <double angleDeg, double angleMin, double angleSec>
 */
std::tuple<double, double, double> PACoordinates::AngleBetweenTwoObjects(
    double raLong1HourDeg, double raLong1Min, double raLong1Sec,
    double decLat1Deg, double decLat1Min, double decLat1Sec,
    double raLong2HourDeg, double raLong2Min, double raLong2Sec,
    double decLat2Deg, double decLat2Min, double decLat2Sec,
    pa_types::AngleMeasurementUnits hourOrDegree) {
  double raLong1Decimal =
      (hourOrDegree == pa_types::AngleMeasurementUnits::Hours)
          ? HmsToDh(raLong1HourDeg, raLong1Min, raLong1Sec)
          : DegreesMinutesSecondsToDecimalDegrees(raLong1HourDeg, raLong1Min,
                                                  raLong1Sec);
  double raLong1Deg = (hourOrDegree == pa_types::AngleMeasurementUnits::Hours)
                          ? DegreeHoursToDecimalDegrees(raLong1Decimal)
                          : raLong1Decimal;

  double raLong1Rad = DegreesToRadians(raLong1Deg);
  double decLat1Deg1 =
      DegreesMinutesSecondsToDecimalDegrees(decLat1Deg, decLat1Min, decLat1Sec);
  double decLat1Rad = DegreesToRadians(decLat1Deg1);

  double raLong2Decimal =
      (hourOrDegree == pa_types::AngleMeasurementUnits::Hours)
          ? HmsToDh(raLong2HourDeg, raLong2Min, raLong2Sec)
          : DegreesMinutesSecondsToDecimalDegrees(raLong2HourDeg, raLong2Min,
                                                  raLong2Sec);
  double raLong2Deg = (hourOrDegree == pa_types::AngleMeasurementUnits::Hours)
                          ? DegreeHoursToDecimalDegrees(raLong2Decimal)
                          : raLong2Decimal;
  double raLong2Rad = DegreesToRadians(raLong2Deg);
  double decLat2Deg1 =
      DegreesMinutesSecondsToDecimalDegrees(decLat2Deg, decLat2Min, decLat2Sec);
  double decLat2Rad = DegreesToRadians(decLat2Deg1);

  double cosD =
      sin(decLat1Rad) * sin(decLat2Rad) +
      cos(decLat1Rad) * cos(decLat2Rad) * cos(raLong1Rad - raLong2Rad);
  double dRad = acos(cosD);
  double dDeg = WToDegrees(dRad);

  double angleDeg = DecimalDegreesDegrees(dDeg);
  double angleMin = DecimalDegreesMinutes(dDeg);
  double angleSec = DecimalDegreesSeconds(dDeg);

  return std::tuple<double, double, double>{angleDeg, angleMin, angleSec};
}

/**
 * \brief Calculate rising and setting times for an object.
 *
 * @return tuple <rise_set_status riseSetStatus, double utRiseHour, double
 * utRiseMin, double utSetHour, double utSetMin, double azRise, double azSet>
 */
std::tuple<pa_types::RiseSetStatus, double, double, double, double, double,
           double>
PACoordinates::RisingAndSetting(double raHours, double raMinutes,
                                double raSeconds, double decDeg, double decMin,
                                double decSec, double gwDateDay,
                                int gwDateMonth, int gwDateYear,
                                double geogLongDeg, double geogLatDeg,
                                double vertShiftDeg) {
  double raHours1 = HmsToDh(raHours, raMinutes, raSeconds);
  double decRad = DegreesToRadians(
      DegreesMinutesSecondsToDecimalDegrees(decDeg, decMin, decSec));
  double verticalDisplRadians = DegreesToRadians(vertShiftDeg);
  double geoLatRadians = DegreesToRadians(geogLatDeg);
  double cosH =
      -(sin(verticalDisplRadians) + sin(geoLatRadians) * sin(decRad)) /
      (cos(geoLatRadians) * cos(decRad));
  double hHours = DecimalDegreesToDegreeHours(WToDegrees(acos(cosH)));
  double lstRiseHours =
      (raHours1 - hHours) - 24 * floor((raHours1 - hHours) / 24);
  double lstSetHours =
      (raHours1 + hHours) - 24 * floor((raHours1 + hHours) / 24);
  double aDeg = WToDegrees(
      acos((sin(decRad) + sin(verticalDisplRadians) * sin(geoLatRadians)) /
           (cos(verticalDisplRadians) * cos(geoLatRadians))));
  double azRiseDeg = aDeg - 360 * floor(aDeg / 360);
  double azSetDeg = (360 - aDeg) - 360 * floor((360 - aDeg) / 360);
  double utRiseHours1 = pa_macros::GreenwichSiderealTimeToUniversalTime(
      pa_macros::LocalSiderealTimeToGreenwichSiderealTime(lstRiseHours, 0, 0,
                                                          geogLongDeg),
      0, 0, gwDateDay, gwDateMonth, gwDateYear);
  double utSetHours1 = pa_macros::GreenwichSiderealTimeToUniversalTime(
      pa_macros::LocalSiderealTimeToGreenwichSiderealTime(lstSetHours, 0, 0,
                                                          geogLongDeg),
      0, 0, gwDateDay, gwDateMonth, gwDateYear);
  double utRiseAdjustedHours = utRiseHours1 + 0.008333;
  double utSetAdjustedHours = utSetHours1 + 0.008333;

  pa_types::RiseSetStatus rsStatus = pa_types::RiseSetStatus::Ok;
  if (cosH > 1)
    rsStatus = pa_types::RiseSetStatus::NeverRises;
  if (cosH < -1)
    rsStatus = pa_types::RiseSetStatus::Circumpolar;

  int utRiseHour = (rsStatus == pa_types::RiseSetStatus::Ok)
                       ? DecimalHoursHour(utRiseAdjustedHours)
                       : 0;
  int utRiseMin = (rsStatus == pa_types::RiseSetStatus::Ok)
                      ? DecimalHoursMinute(utRiseAdjustedHours)
                      : 0;
  int utSetHour = (rsStatus == pa_types::RiseSetStatus::Ok)
                      ? DecimalHoursHour(utSetAdjustedHours)
                      : 0;
  int utSetMin = (rsStatus == pa_types::RiseSetStatus::Ok)
                     ? DecimalHoursMinute(utSetAdjustedHours)
                     : 0;
  double azRise = (rsStatus == pa_types::RiseSetStatus::Ok)
                      ? pa_util::Round(azRiseDeg, 2)
                      : 0;
  double azSet = (rsStatus == pa_types::RiseSetStatus::Ok)
                     ? pa_util::Round(azSetDeg, 2)
                     : 0;

  return std::tuple<pa_types::RiseSetStatus, double, double, double, double,
                    double, double>{rsStatus, utRiseHour, utRiseMin, utSetHour,
                                    utSetMin, azRise,     azSet};
}

/**
 * \brief Calculate precession (corrected coordinates between two epochs)
 *
 * @return tuple<double corrected_ra_hour, double corrected_ra_minutes, double
 * corrected_ra_seconds, double corrected_dec_deg, double corrected_dec_minutes,
 * double corrected_dec_seconds>
 */
std::tuple<double, double, double, double, double, double>
PACoordinates::CorrectForPrecession(double raHour, double raMinutes,
                                    double raSeconds, double decDeg,
                                    double decMinutes, double decSeconds,
                                    double epoch1Day, int epoch1Month,
                                    int epoch1Year, double epoch2Day,
                                    int epoch2Month, int epoch2Year) {
  double ra1Rad = DegreesToRadians(
      DegreeHoursToDecimalDegrees(HmsToDh(raHour, raMinutes, raSeconds)));
  double dec1Rad = DegreesToRadians(
      DegreesMinutesSecondsToDecimalDegrees(decDeg, decMinutes, decSeconds));
  double tCenturies =
      (CivilDateToJulianDate(epoch1Day, epoch1Month, epoch1Year) - 2415020) /
      36525;
  double mSec = 3.07234 + (0.00186 * tCenturies);
  double nArcsec = 20.0468 - (0.0085 * tCenturies);
  double nYears = (CivilDateToJulianDate(epoch2Day, epoch2Month, epoch2Year) -
                   CivilDateToJulianDate(epoch1Day, epoch1Month, epoch1Year)) /
                  365.25;
  double s1Hours =
      ((mSec + (nArcsec * sin(ra1Rad) * tan(dec1Rad) / 15)) * nYears) / 3600;
  double ra2Hours = HmsToDh(raHour, raMinutes, raSeconds) + s1Hours;
  double s2Deg = (nArcsec * cos(ra1Rad) * nYears) / 3600;
  double dec2Deg =
      DegreesMinutesSecondsToDecimalDegrees(decDeg, decMinutes, decSeconds) +
      s2Deg;

  int correctedRaHour = DecimalHoursHour(ra2Hours);
  int correctedRaMinutes = DecimalHoursMinute(ra2Hours);
  double correctedRaSeconds = DecimalHoursSecond(ra2Hours);
  double correctedDecDeg = DecimalDegreesDegrees(dec2Deg);
  double correctedDecMinutes = DecimalDegreesMinutes(dec2Deg);
  double correctedDecSeconds = DecimalDegreesSeconds(dec2Deg);

  return std::tuple<double, double, double, double, double, double>{
      correctedRaHour, correctedRaMinutes,  correctedRaSeconds,
      correctedDecDeg, correctedDecMinutes, correctedDecSeconds};
}

/**
 * \brief Calculate nutation for two values: ecliptic longitude and obliquity,
 * for a Greenwich date.
 *
 * @return tuple<nutation in ecliptic longitude (degrees), nutation in obliquity
 * (degrees)>
 */
std::tuple<double, double>
PACoordinates::NutationInEclipticLongitudeAndObliquity(double greenwichDay,
                                                       int greenwichMonth,
                                                       int greenwichYear) {
  double jdDays =
      CivilDateToJulianDate(greenwichDay, greenwichMonth, greenwichYear);
  double tCenturies = (jdDays - 2415020) / 36525;
  double aDeg = 100.0021358 * tCenturies;
  double l1Deg = 279.6967 + (0.000303 * tCenturies * tCenturies);
  double lDeg1 = l1Deg + 360 * (aDeg - floor(aDeg));
  double lDeg2 = lDeg1 - 360 * floor(lDeg1 / 360);
  double lRad = DegreesToRadians(lDeg2);
  double bDeg = 5.372617 * tCenturies;
  double nDeg1 = 259.1833 - 360 * (bDeg - floor(bDeg));
  double nDeg2 = nDeg1 - 360 * (floor(nDeg1 / 360));
  double nRad = DegreesToRadians(nDeg2);
  double nutInLongArcsec = -17.2 * sin(nRad) - 1.3 * sin(2 * lRad);
  double nutInOblArcsec = 9.2 * cos(nRad) + 0.5 * cos(2 * lRad);

  double nutInLongDeg = nutInLongArcsec / 3600;
  double nutInOblDeg = nutInOblArcsec / 3600;

  return std::tuple<double, double>{nutInLongDeg, nutInOblDeg};
}

/**
 * \brief Correct ecliptic coordinates for the effects of aberration.
 *
 * @return tuple<apparent ecliptic longitude (degrees, minutes, seconds),
 * apparent ecliptic latitude (degrees, minutes, seconds)>
 */
std::tuple<double, double, double, double, double, double>
PACoordinates::CorrectForAberration(double utHour, double utMinutes,
                                    double utSeconds, double gwDay, int gwMonth,
                                    int gw_year, double trueEclLongDeg,
                                    double trueEclLongMin,
                                    double trueEclLongSec, double trueEclLatDeg,
                                    double trueEclLatMin,
                                    double trueEclLatSec) {
  double trueLongDeg = DegreesMinutesSecondsToDecimalDegrees(
      trueEclLongDeg, trueEclLongMin, trueEclLongSec);
  double trueLatDeg = DegreesMinutesSecondsToDecimalDegrees(
      trueEclLatDeg, trueEclLatMin, trueEclLatSec);
  double sunTrueLongDeg =
      SunLong(utHour, utMinutes, utSeconds, 0, 0, gwDay, gwMonth, gw_year);
  double dLongArcsec = -20.5 *
                       cos(DegreesToRadians(sunTrueLongDeg - trueLongDeg)) /
                       cos(DegreesToRadians(trueLatDeg));
  double dLatArcsec = -20.5 *
                      sin(DegreesToRadians(sunTrueLongDeg - trueLongDeg)) *
                      sin(DegreesToRadians(trueLatDeg));
  double apparentLongDeg = trueLongDeg + (dLongArcsec / 3600);
  double apparentLatDeg = trueLatDeg + (dLatArcsec / 3600);

  double apparentEclLongDeg = DecimalDegreesDegrees(apparentLongDeg);
  double apparentEclLongMin = DecimalDegreesMinutes(apparentLongDeg);
  double apparentEclLongSec = DecimalDegreesSeconds(apparentLongDeg);
  double apparentEclLatDeg = DecimalDegreesDegrees(apparentLatDeg);
  double apparentEclLatMin = DecimalDegreesMinutes(apparentLatDeg);
  double apparentEclLatSec = DecimalDegreesSeconds(apparentLatDeg);

  return std::tuple<double, double, double, double, double, double>{
      apparentEclLongDeg, apparentEclLongMin, apparentEclLongSec,
      apparentEclLatDeg,  apparentEclLatMin,  apparentEclLatSec};
}

/**
 * \brief Calculate corrected RA/Dec, accounting for atmospheric refraction.
 *
 * NOTE: Valid values for coordinate_type are "TRUE" and "APPARENT".
 *
 * @return tuple <corrected RA hours,minutes,seconds and corrected Declination
 * degrees,minutes,seconds>
 */
std::tuple<double, double, double, double, double, double>
PACoordinates::AtmosphericRefraction(
    double trueRaHour, double trueRaMin, double trueRaSec, double trueDecDeg,
    double trueDecMin, double trueDecSec,
    pa_types::CoordinateType coordinateType1, double geogLongDeg,
    double geogLatDeg, int daylightSavingHours, int timezoneHours,
    double lcdDay, int lcdMonth, int lcdYear, double lctHour, double lctMin,
    double lctSec, double atmosphericPressureMbar,
    double atmosphericTemperatureCelsius) {
  double haHour = pa_macros::RightAscensionToHourAngle(
      trueRaHour, trueRaMin, trueRaSec, lctHour, lctMin, lctSec,
      daylightSavingHours, timezoneHours, lcdDay, lcdMonth, lcdYear,
      geogLongDeg);
  double azimuthDeg = pa_macros::EquatorialCoordinatesToAzimuth(
      haHour, 0, 0, trueDecDeg, trueDecMin, trueDecSec, geogLatDeg);
  double altitudeDeg = pa_macros::EquatorialCoordinatesToAltitude(
      haHour, 0, 0, trueDecDeg, trueDecMin, trueDecSec, geogLatDeg);
  double correctedAltitudeDeg =
      pa_macros::Refract(altitudeDeg, coordinateType1, atmosphericPressureMbar,
                         atmosphericTemperatureCelsius);

  double correctedHaHour = pa_macros::HorizonCoordinatesToHourAngle(
      azimuthDeg, 0, 0, correctedAltitudeDeg, 0, 0, geogLatDeg);
  double correctedRaHour1 = pa_macros::HourAngleToRightAscension(
      correctedHaHour, 0, 0, lctHour, lctMin, lctSec, daylightSavingHours,
      timezoneHours, lcdDay, lcdMonth, lcdYear, geogLongDeg);
  double correctedDecDeg1 = pa_macros::HorizonCoordinatesToDeclination(
      azimuthDeg, 0, 0, correctedAltitudeDeg, 0, 0, geogLatDeg);

  int correctedRaHour = pa_macros::DecimalHoursHour(correctedRaHour1);
  int correctedRaMin = pa_macros::DecimalHoursMinute(correctedRaHour1);
  double correctedRaSec = pa_macros::DecimalHoursSecond(correctedRaHour1);
  double correctedDecDeg = pa_macros::DecimalDegreesDegrees(correctedDecDeg1);
  double correctedDecMin = pa_macros::DecimalDegreesMinutes(correctedDecDeg1);
  double correctedDecSec = pa_macros::DecimalDegreesSeconds(correctedDecDeg1);

  return std::tuple<double, double, double, double, double, double>{
      correctedRaHour, correctedRaMin,  correctedRaSec,
      correctedDecDeg, correctedDecMin, correctedDecSec};
}

/**
 * \brief Calculate corrected RA/Dec, accounting for geocentric parallax.
 *
 * @return tuple <corrected RA hours,minutes,seconds and corrected Declination
 * degrees,minutes,seconds>
 */
std::tuple<double, double, double, double, double, double>
PACoordinates::CorrectionsForGeocentricParallax(
    double raHour, double raMin, double raSec, double decDeg, double decMin,
    double decSec, pa_types::CoordinateType coordinateType,
    double equatorialHorParallaxDeg, double geogLongDeg, double geogLatDeg,
    double heightM, int daylightSaving, int timezoneHours, double lcdDay,
    int lcdMonth, int lcdYear, double lctHour, double lctMin, double lctSec) {
  double haHours = pa_macros::RightAscensionToHourAngle(
      raHour, raMin, raSec, lctHour, lctMin, lctSec, daylightSaving,
      timezoneHours, lcdDay, lcdMonth, lcdYear, geogLongDeg);

  double correctedHaHours = pa_macros::ParallaxHa(
      haHours, 0, 0, decDeg, decMin, decSec, coordinateType, geogLatDeg,
      heightM, equatorialHorParallaxDeg);

  double correctedRaHours = pa_macros::HourAngleToRightAscension(
      correctedHaHours, 0, 0, lctHour, lctMin, lctSec, daylightSaving,
      timezoneHours, lcdDay, lcdMonth, lcdYear, geogLongDeg);

  double correctedDecDeg1 = pa_macros::ParallaxDec(
      haHours, 0, 0, decDeg, decMin, decSec, coordinateType, geogLatDeg,
      heightM, equatorialHorParallaxDeg);

  int correctedRaHour = pa_macros::DecimalHoursHour(correctedRaHours);
  int correctedRaMin = pa_macros::DecimalHoursMinute(correctedRaHours);
  double correctedRaSec = pa_macros::DecimalHoursSecond(correctedRaHours);
  double correctedDecDeg = pa_macros::DecimalDegreesDegrees(correctedDecDeg1);
  double correctedDecMin = pa_macros::DecimalDegreesMinutes(correctedDecDeg1);
  double correctedDecSec = pa_macros::DecimalDegreesSeconds(correctedDecDeg1);

  return std::tuple<double, double, double, double, double, double>{
      correctedRaHour, correctedRaMin,  correctedRaSec,
      correctedDecDeg, correctedDecMin, correctedDecSec};
}

/**
 * \brief Calculate heliographic coordinates for a given Greenwich date, with a
 * given heliographic position angle and heliographic displacement in arc
 * minutes.
 *
 * @return tuple <heliographic longitude and heliographic latitude, in degrees>
 */
std::tuple<double, double> PACoordinates::HeliographicCoordinates(
    double helioPositionAngleDeg, double helioDisplacementArcmin,
    double gwdateDay, int gwdateMonth, int gwdate_year) {
  double julianDateDays =
      CivilDateToJulianDate(gwdateDay, gwdateMonth, gwdate_year);
  double tCenturies = (julianDateDays - 2415020) / 36525;
  double longAscNodeDeg =
      DegreesMinutesSecondsToDecimalDegrees(74, 22, 0) + (84 * tCenturies / 60);
  double sunLongDeg =
      SunLong(0, 0, 0, 0, 0, gwdateDay, gwdateMonth, gwdate_year);
  double y =
      sin(DegreesToRadians(longAscNodeDeg - sunLongDeg)) *
      cos(DegreesToRadians(DegreesMinutesSecondsToDecimalDegrees(7, 15, 0)));
  double x = -cos(DegreesToRadians(longAscNodeDeg - sunLongDeg));
  double aDeg = WToDegrees(atan2(y, x));
  double mDeg1 = 360 - (360 * (julianDateDays - 2398220) / 25.38);
  double mDeg2 = mDeg1 - 360 * floor(mDeg1 / 360);
  double l0Deg1 = mDeg2 + aDeg;
  double b0Rad = asin(
      sin(DegreesToRadians(sunLongDeg - longAscNodeDeg)) *
      sin(DegreesToRadians(DegreesMinutesSecondsToDecimalDegrees(7, 15, 0))));
  double theta1Rad = atan(-cos(DegreesToRadians(sunLongDeg)) *
                          tan(DegreesToRadians(pa_macros::Obliq(
                              gwdateDay, gwdateMonth, gwdate_year))));
  double theta2Rad = atan(
      -cos(DegreesToRadians(longAscNodeDeg - sunLongDeg)) *
      tan(DegreesToRadians(DegreesMinutesSecondsToDecimalDegrees(7, 15, 0))));
  double pDeg = WToDegrees(theta1Rad + theta2Rad);
  double rho1Deg = helioDisplacementArcmin / 60;
  double rhoRad =
      asin(2 * rho1Deg /
           SunDia(0, 0, 0, 0, 0, gwdateDay, gwdateMonth, gwdate_year)) -
      DegreesToRadians(rho1Deg);
  double bRad = asin(sin(b0Rad) * cos(rhoRad) +
                     cos(b0Rad) * sin(rhoRad) *
                         cos(DegreesToRadians(pDeg - helioPositionAngleDeg)));
  double bDeg = WToDegrees(bRad);
  double lDeg1 =
      WToDegrees(asin(sin(rhoRad) *
                      sin(DegreesToRadians(pDeg - helioPositionAngleDeg)) /
                      cos(bRad))) +
      l0Deg1;
  double lDeg2 = lDeg1 - 360 * floor(lDeg1 / 360);

  double helioLongDeg = Round(lDeg2, 2);
  double helioLatDeg = Round(bDeg, 2);

  return std::tuple<double, double>{helioLongDeg, helioLatDeg};
}

/**
 * \brief Calculate carrington rotation number for a Greenwich date
 *
 * @return carrington rotation number
 */
int PACoordinates::CarringtonRotationNumber(double gwdateDay, int gwdateMonth,
                                            int gwdateYear) {
  double julianDateDays =
      CivilDateToJulianDate(gwdateDay, gwdateMonth, gwdateYear);

  int crn = 1690 + (int)Round((julianDateDays - 2444235.34) / 27.2753, 0);

  return crn;
}

/**
 * \brief Calculate selenographic (lunar) coordinates (sub-Earth)
 *
 * @return tuple<sub-earth longitude, sub-earth latitude, and position angle of
 * pole>
 */
std::tuple<double, double, double>
PACoordinates::SelenographicCoordinates1(double gwdateDay, int gwdateMonth,
                                         int gwdateYear) {
  double julianDateDays =
      CivilDateToJulianDate(gwdateDay, gwdateMonth, gwdateYear);
  double tCenturies = (julianDateDays - 2451545) / 36525;
  double longAscNodeDeg = 125.044522 - 1934.136261 * tCenturies;
  double f1 = 93.27191 + 483202.0175 * tCenturies;
  double f2 = f1 - 360 * floor(f1 / 360);
  double geocentricMoonLongDeg = pa_macros::MoonLongitude(
      0, 0, 0, 0, 0, gwdateDay, gwdateMonth, gwdateYear);
  double geocentricMoonLatRad = DegreesToRadians(pa_macros::MoonLatitude(
      0, 0, 0, 0, 0, gwdateDay, gwdateMonth, gwdateYear));
  double inclinationRad =
      DegreesToRadians(DegreesMinutesSecondsToDecimalDegrees(1, 32, 32.7));
  double nodeLongRad = DegreesToRadians(longAscNodeDeg - geocentricMoonLongDeg);
  double sinBe =
      -cos(inclinationRad) * sin(geocentricMoonLatRad) +
      sin(inclinationRad) * cos(geocentricMoonLatRad) * sin(nodeLongRad);
  double subEarthLatDeg = WToDegrees(asin(sinBe));
  double aRad = atan2(-sin(geocentricMoonLatRad) * sin(inclinationRad) -
                          cos(geocentricMoonLatRad) * cos(inclinationRad) *
                              sin(nodeLongRad),
                      cos(geocentricMoonLatRad) * cos(nodeLongRad));
  double aDeg = WToDegrees(aRad);
  double subEarthLongDeg1 = aDeg - f2;
  double subEarthLongDeg2 =
      subEarthLongDeg1 - 360 * floor(subEarthLongDeg1 / 360);
  double subEarthLongDeg3 =
      (subEarthLongDeg2 > 180) ? (subEarthLongDeg2 - 360) : subEarthLongDeg2;
  double c1Rad = atan(
      cos(nodeLongRad) * sin(inclinationRad) /
      (cos(geocentricMoonLatRad) * cos(inclinationRad) +
       sin(geocentricMoonLatRad) * sin(inclinationRad) * sin(nodeLongRad)));
  double obliquityRad =
      DegreesToRadians(Obliq(gwdateDay, gwdateMonth, gwdateYear));
  double c2Rad =
      atan(sin(obliquityRad) * cos(DegreesToRadians(geocentricMoonLongDeg)) /
           (sin(obliquityRad) * sin(geocentricMoonLatRad) *
                sin(DegreesToRadians(geocentricMoonLongDeg)) -
            cos(obliquityRad) * cos(geocentricMoonLatRad)));
  double cDeg = WToDegrees(c1Rad + c2Rad);

  double subEarthLongitude = Round(subEarthLongDeg3, 2);
  double subEarthLatitude = Round(subEarthLatDeg, 2);
  double positionAngleOfPole = Round(cDeg, 2);

  return std::tuple<double, double, double>{subEarthLongitude, subEarthLatitude,
                                            positionAngleOfPole};
}

/**
 * \brief Calculate selenographic (lunar) coordinates (sub-Solar)
 *
 * @return tuple<sub-solar longitude, sub-solar colongitude, and sub-solar
 * latitude>
 */
std::tuple<double, double, double>
PACoordinates::SelenographicCoordinates2(double gwdateDay, int gwdateMonth,
                                         int gwdateYear) {
  double julianDateDays =
      CivilDateToJulianDate(gwdateDay, gwdateMonth, gwdateYear);
  double tCenturies = (julianDateDays - 2451545) / 36525;
  double longAscNodeDeg = 125.044522 - 1934.136261 * tCenturies;
  double f1 = 93.27191 + 483202.0175 * tCenturies;
  double f2 = f1 - 360 * floor(f1 / 360);
  double sunGeocentricLongDeg =
      SunLong(0, 0, 0, 0, 0, gwdateDay, gwdateMonth, gwdateYear);
  double moonEquHorParallaxArcMin =
      pa_macros::MoonHorizontalParallax(0, 0, 0, 0, 0, gwdateDay, gwdateMonth,
                                        gwdateYear) *
      60;
  double sunEarthDistAu =
      SunDist(0, 0, 0, 0, 0, gwdateDay, gwdateMonth, gwdateYear);
  double geocentricMoonLatRad = DegreesToRadians(
      MoonLatitude(0, 0, 0, 0, 0, gwdateDay, gwdateMonth, gwdateYear));
  double geocentricMoonLongDeg =
      MoonLongitude(0, 0, 0, 0, 0, gwdateDay, gwdateMonth, gwdateYear);
  double adjustedMoonLongDeg =
      sunGeocentricLongDeg + 180 +
      (26.4 * cos(geocentricMoonLatRad) *
       sin(DegreesToRadians(sunGeocentricLongDeg - geocentricMoonLongDeg)) /
       (moonEquHorParallaxArcMin * sunEarthDistAu));
  double adjustedMoonLatRad = 0.14666 * geocentricMoonLatRad /
                              (moonEquHorParallaxArcMin * sunEarthDistAu);
  double inclinationRad =
      DegreesToRadians(DegreesMinutesSecondsToDecimalDegrees(1, 32, 32.7));
  double nodeLongRad = DegreesToRadians(longAscNodeDeg - adjustedMoonLongDeg);
  double sinBs =
      -cos(inclinationRad) * sin(adjustedMoonLatRad) +
      sin(inclinationRad) * cos(adjustedMoonLatRad) * sin(nodeLongRad);
  double subSolarLatDeg = WToDegrees(asin(sinBs));
  double aRad = atan2(-sin(adjustedMoonLatRad) * sin(inclinationRad) -
                          cos(adjustedMoonLatRad) * cos(inclinationRad) *
                              sin(nodeLongRad),
                      cos(adjustedMoonLatRad) * cos(nodeLongRad));
  double aDeg = WToDegrees(aRad);
  double subSolarLongDeg1 = aDeg - f2;
  double sub_solar_long_deg2 =
      subSolarLongDeg1 - 360 * floor(subSolarLongDeg1 / 360);
  double subSolarLongDeg3 = (sub_solar_long_deg2 > 180)
                                ? sub_solar_long_deg2 - 360
                                : sub_solar_long_deg2;
  double subSolarColongDeg = 90 - subSolarLongDeg3;

  double subSolarLongitude = Round(subSolarLongDeg3, 2);
  double subSolarColongitude = Round(subSolarColongDeg, 2);
  double subSolarLatitude = Round(subSolarLatDeg, 2);

  return std::tuple<double, double, double>{
      subSolarLongitude, subSolarColongitude, subSolarLatitude};
}
