#include "pa_data.h"
#include "pa_models.h"
#include "pa_types.h"
#include <string>
#include <tuple>
#include <vector>

#ifndef _pa_macros
#define _pa_macros

using namespace pa_models;
using namespace pa_types;

namespace pa_macros {

double HmsToDh(double hours, double minutes, double seconds);

int DecimalHoursHour(double decimalHours);

int DecimalHoursMinute(double decimal_hours);

double DecimalHoursSecond(double decimal_hours);

double CivilDateToJulianDate(double day, double month, double year);

double JulianDateDay(double julian_date);

int JulianDateMonth(double julian_date);

int JulianDateYear(double julian_date);

double RightAscensionToHourAngle(double ra_hours, double ra_minutes,
                                 double ra_seconds, double lct_hours,
                                 double lct_minutes, double lct_seconds,
                                 int daylight_saving, int zone_correction,
                                 double local_day, int local_month,
                                 int local_year, double geographical_longitude);

double LocalCivilTimeToUniversalTime(double lct_hours, double lct_minutes,
                                     double lct_seconds, int daylight_saving,
                                     int zone_correction, double local_day,
                                     int local_month, int local_year);

double LocalCivilTimeGreenwichDay(double lct_hours, double lct_minutes,
                                  double lct_seconds, int daylight_saving,
                                  int zone_correction, double local_day,
                                  int local_month, int local_year);

double LocalCivilTimeGreenwichMonth(double lct_hours, double lct_minutes,
                                    double lct_seconds, int daylight_saving,
                                    int zone_correction, double local_day,
                                    int local_month, int local_year);

double LocalCivilTimeGreenwichYear(double lct_hours, double lct_minutes,
                                   double lct_seconds, int daylight_saving,
                                   int zone_correction, double local_day,
                                   int local_month, int local_year);

double UniversalTimeToGreenwichSiderealTime(double u_hours, double u_minutes,
                                            double u_seconds,
                                            double greenwich_day,
                                            int greenwich_month,
                                            int greenwich_year);

double GreenwichSiderealTimeToLocalSiderealTime(double greenwich_hours,
                                                double greenwich_minutes,
                                                double greenwich_seconds,
                                                double geographical_longitude);

double HourAngleToRightAscension(double hour_angle_hours,
                                 double hour_angle_minutes,
                                 double hour_angle_seconds, double lct_hours,
                                 double lct_minutes, double lct_seconds,
                                 int daylight_saving, int zone_correction,
                                 double local_day, int local_month,
                                 int local_year, double geographical_longitude);

double EquatorialCoordinatesToAzimuth(double hour_angle_hours,
                                      double hour_angle_minutes,
                                      double hour_angle_seconds,
                                      double declination_degrees,
                                      double declination_minutes,
                                      double declination_seconds,
                                      double geographical_latitude);

double DegreesMinutesSecondsToDecimalDegrees(double degrees, double minutes,
                                             double seconds);

double WToDegrees(double w);

double EquatorialCoordinatesToAltitude(double hour_angle_hours,
                                       double hour_angle_minutes,
                                       double hour_angle_seconds,
                                       double declination_degrees,
                                       double declination_minutes,
                                       double declination_seconds,
                                       double geographical_latitude);

double DecimalDegreesDegrees(double decimal_degrees);

double DecimalDegreesMinutes(double decimal_degrees);

double DecimalDegreesSeconds(double decimal_degrees);

double HorizonCoordinatesToDeclination(
    double azimuth_degrees, double azimuth_minutes, double azimuth_seconds,
    double altitude_degrees, double altitude_minutes, double altitude_seconds,
    double geographical_latitude);

double
HorizonCoordinatesToHourAngle(double azimuth_degrees, double azimuth_minutes,
                              double azimuth_seconds, double altitude_degrees,
                              double altitude_minutes, double altitude_seconds,
                              double geographical_latitude);

double DecimalDegreesToDegreeHours(double decimal_degrees);

double DegreeHoursToDecimalDegrees(double degree_hours);

double Obliq(double greenwich_day, int greenwich_month, int greenwich_year);

double NutatLong(double gd, int gm, int gy);

double NutatObl(double greenwich_day, int greenwich_month, int greenwich_year);

double LocalSiderealTimeToGreenwichSiderealTime(double local_hours,
                                                double local_minutes,
                                                double local_seconds,
                                                double longitude);

double GreenwichSiderealTimeToUniversalTime(double greenwich_sidereal_hours,
                                            double greenwich_sidereal_minutes,
                                            double greenwich_sidereal_seconds,
                                            double greenwich_day,
                                            int greenwich_month,
                                            int greenwich_year);

double SunLong(double lch, double lcm, double lcs, int ds, int zc, double ld,
               int lm, int ly);

double TrueAnomaly(double am, double ec);

double EccentricAnomaly(double am, double ec);

double Refract(double y2, ECoordinateType sw, double pr, double tr);

double RefractL3035(double pr, double tr, double y, double d);

double ParallaxHa(double hh, double hm, double hs, double dd, double dm,
                  double ds, ECoordinateType sw, double gp, double ht,
                  double hp);

std::tuple<double, double> ParallaxHaL2870(double x, double y, double rc,
                                           double rp, double rs, double tp);

double ParallaxDec(double hh, double hm, double hs, double dd, double dm,
                   double ds, ECoordinateType sw, double gp, double ht,
                   double hp);

std::tuple<double, double> ParallaxDecL2870(double x, double y, double rc,
                                            double rp, double rs, double tp);

double SunDia(double lch, double lcm, double lcs, int ds, int zc, double ld,
              int lm, int ly);

double SunDist(double lch, double lcm, double lcs, int ds, int zc, double ld,
               int lm, int ly);

double MoonLongitude(double lh, double lm, double ls, int ds, int zc, double dy,
                     int mn, int yr);

double MoonLatitude(double lh, double lm, double ls, int ds, int zc, double dy,
                    int mn, int yr);

double MoonDist(double lh, double lm, double ls, int ds, int zc, double dy,
                int mn, int yr);

double MoonSize(double lh, double lm, double ls, int ds, int zc, double dy,
                int mn, int yr);

double MoonHorizontalParallax(double lh, double lm, double ls, int ds, int zc,
                              double dy, int mn, int yr);

double Unwind(double w);

double UnwindDeg(double w);

double SunELong(double gd, int gm, int gy);

double SunPerigee(double gd, int gm, int gy);

double SunEccentricity(double gd, int gm, int gy);

double EclipticDeclination(double eld, double elm, double els, double bd,
                           double bm, double bs, double gd, int gm, int gy);

double EclipticRightAscension(double eld, double elm, double els, double bd,
                              double bm, double bs, double gd, int gm, int gy);

double SunTrueAnomaly(double lch, double lcm, double lcs, int ds, int zc,
                      double ld, int lm, int ly);

double SunMeanAnomaly(double lch, double lcm, double lcs, int ds, int zc,
                      double ld, int lm, int ly);

double SunriseLocalCivilTime(double ld, int lm, int ly, int ds, int zc,
                             double gl, double gp);

double SunsetLocalCivilTime(double ld, int lm, int ly, int ds, int zc,
                            double gl, double gp);

std::tuple<double, double, double, double, ERiseSetStatus>
SunriseLocalCivilTimeL3710(double gd, int gm, int gy, double sr, double di,
                           double gp);

std::tuple<double, double, double, double, ERiseSetStatus>
SunsetLocalCivilTimeL3710(double gd, int gm, int gy, double sr, double di,
                          double gp);

double RiseSetLocalSiderealTimeRise(double rah, double ram, double ras,
                                    double dd, double dm, double ds, double vd,
                                    double g);

double RiseSetLocalSiderealTimeSet(double rah, double ram, double ras,
                                   double dd, double dm, double ds, double vd,
                                   double g);

ERiseSetStatus ERiseSet(double rah, double ram, double ras, double dd,
                        double dm, double ds, double vd, double g);

EWarningFlags EGstUt(double gsh, double gsm, double gss, double gd, int gm,
                     int gy);

double UniversalTimeToLocalCivilTime(double u_hours, double u_minutes,
                                     double u_seconds, int daylight_saving,
                                     int zone_correction, double greenwich_day,
                                     int greenwich_month, int greenwich_year);

double UniversalTimeLocalCivilDay(double u_hours, double u_minutes,
                                  double u_seconds, int daylight_saving,
                                  int zone_correction, double greenwich_day,
                                  int greenwich_month, int greenwich_year);

int UniversalTimeLocalCivilMonth(double u_hours, double u_minutes,
                                 double u_seconds, int daylight_saving,
                                 int zone_correction, double greenwich_day,
                                 int greenwich_month, int greenwich_year);

int UniversalTimeLocalCivilYear(double u_hours, double u_minutes,
                                double u_seconds, int daylight_saving,
                                int zone_correction, double greenwich_day,
                                int greenwich_month, int greenwich_year);

ERiseSetStatus ESunRiseSetCalcStatus(double ld, int lm, int ly, int ds, int zc,
                                     double gl, double gp);

std::tuple<double, double, double, double, ERiseSetStatus>
ESunRiseSetCalcStatusL3710(double gd, int gm, int gy, double sr, double di,
                           double gp);

double SunriseAzimuth(double ld, int lm, int ly, int ds, int zc, double gl,
                      double gp);

std::tuple<double, double, double, double, ERiseSetStatus>
SunriseAzimuthL3710(double gd, int gm, int gy, double sr, double di, double gp);

double SunsetAzimuth(double ld, int lm, int ly, int ds, int zc, double gl,
                     double gp);

std::tuple<double, double, double, double, ERiseSetStatus>
SunsetAzimuthL3710(double gd, int gm, int gy, double sr, double di, double gp);

double RiseSetAzimuthRise(double rah, double ram, double ras, double dd,
                          double dm, double ds, double vd, double g);

double RiseSetAzimuthSet(double rah, double ram, double ras, double dd,
                         double dm, double ds, double vd, double g);

double TwilightAMLocalCivilTime(double ld, int lm, int ly, int ds, int zc,
                                double gl, double gp, ETwilightType tt);

std::tuple<double, double, double, double, ERiseSetStatus>
TwilightAMLocalCivilTime_L3710(double gd, int gm, int gy, double sr, double di,
                               double gp);

double TwilightPMLocalCivilTime(double ld, int lm, int ly, int ds, int zc,
                                double gl, double gp, ETwilightType tt);

std::tuple<double, double, double, double, ERiseSetStatus>
TwilightPMLocalCivilTime_L3710(double gd, int gm, int gy, double sr, double di,
                               double gp);

ETwilightStatus ETwilight(double ld, int lm, int ly, int ds, int zc, double gl,
                          double gp, ETwilightType tt);

std::tuple<double, double, double, double, ETwilightStatus>
ETwilight_L3710(double gd, int gm, int gy, double sr, double di, double gp);

double Angle(double xx1, double xm1, double xs1, double dd1, double dm1,
             double ds1, double xx2, double xm2, double xs2, double dd2,
             double dm2, double ds2, EAngleMeasure s);

CPlanetCoordinates PlanetCoordinates(double lh, double lm, double ls, int ds,
                                     int zc, double dy, int mn, int yr,
                                     std::string s);

CPlanetLongLatL4685 PlanetLongL4685(std::vector<pa_data::PlanetDataPrecise> pl);

CPlanetLongLatL4735 PlanetLongL4735(std::vector<pa_data::PlanetDataPrecise> pl,
                                    double ms, double t);

CPlanetLongLatL4810 PlanetLongL4810(std::vector<pa_data::PlanetDataPrecise> pl,
                                    double ms);

CPlanetLongLatL4945 PlanetLongL4945(double t,
                                    pa_data::PlanetDataPrecise planet);

CCometLongLatDist PCometLongLatDist(double lh, double lm, double ls, int ds,
                                    int zc, double dy, int mn, int yr,
                                    double td, int tm, int ty, double q,
                                    double i, double p, double n);

double SolveCubic(double w);

CMoonLongLatHP MoonLongLatHP(double lh, double lm, double ls, int ds, int zc,
                             double dy, int mn, int yr);

double MoonPhase(double lh, double lm, double ls, int ds, int zc, double dy,
                 int mn, int yr);

double MoonMeanAnomaly(double lh, double lm, double ls, int ds, int zc,
                       double dy, int mn, int yr);

double NewMoon(int ds, int zc, double dy, int mn, int yr);

double FullMoon(int ds, int zc, double dy, int mn, int yr);

CNewMoonFullMoonL6855 NewMoonFullMoonL6855(double k, double t);

double Fract(double w);

double Lint(double w);

double IInt(double w);

double Sign(double number_to_check);

double UTDayAdjust(double ut, double g1);

double FPart(double w);

double EQELat(double rah, double ram, double ras, double dd, double dm,
              double ds, double gd, int gm, int gy);

double EQELong(double rah, double ram, double ras, double dd, double dm,
               double ds, double gd, int gm, int gy);

double MoonRiseLCT(double dy, int mn, int yr, int ds, int zc, double gLong,
                   double gLat);

CMoonRiseLCTL6680 MoonRiseLCTL6680(double x, int ds, int zc, double gdy,
                                   int gmn, int gyr, double g1, double ut);

CMoonRiseLCTL6700 MoonRiseLCTL6700(double lct, int ds, int zc, double dy1,
                                   int mn1, int yr1, double gdy, int gmn,
                                   int gyr, double gLat);

CFullDatePrecise MoonRiseLCDMY(double dy, int mn, int yr, int ds, int zc,
                               double gLong, double gLat);

CMoonRiseLcDMYL6680 MoonRiseLCDMYL6680(double x, int ds, int zc, double gdy,
                                       int gmn, int gyr, double g1, double ut);

CMoonRiseLcDMYL6700 MoonRiseLCDMYL6700(double lct, int ds, int zc, double dy1,
                                       int mn1, int yr1, double gdy, int gmn,
                                       int gyr, double gLat);

double MoonRiseAz(double dy, int mn, int yr, int ds, int zc, double gLong,
                  double gLat);

CMoonRiseAzL6680 MoonRiseAzL6680(double x, int ds, int zc, double gdy, int gmn,
                                 int gyr, double g1, double ut);

CMoonRiseAzL6700 MoonRiseAzL6700(double lct, int ds, int zc, double dy1,
                                 int mn1, int yr1, double gdy, int gmn, int gyr,
                                 double gLat);

double MoonSetLCT(double dy, int mn, int yr, int ds, int zc, double gLong,
                  double gLat);

CMoonSetLCTL6680 MoonSetLCTL6680(double x, int ds, int zc, double gdy, int gmn,
                                 int gyr, double g1, double ut);

CMoonSetLCTL6700 MoonSetLCTL6700(double lct, int ds, int zc, double dy1,
                                 int mn1, int yr1, double gdy, int gmn, int gyr,
                                 double gLat);

CFullDatePrecise MoonSetLCDMY(double dy, int mn, int yr, int ds, int zc,
                              double gLong, double gLat);

CMoonSetLcDMYL6680 MoonSetLCDMYL6680(double x, int ds, int zc, double gdy,
                                     int gmn, int gyr, double g1, double ut);

CMoonSetLcDMYL6700 MoonSetLCDMYL6700(double lct, int ds, int zc, double dy1,
                                     int mn1, int yr1, double gdy, int gmn,
                                     int gyr, double gLat);

double MoonSetAz(double dy, int mn, int yr, int ds, int zc, double gLong,
                 double gLat);

CMoonSetAzL6680 MoonSetAzL6680(double x, int ds, int zc, double gdy, int gmn,
                               int gyr, double g1, double ut);

CMoonSetAzL6700 MoonSetAzL6700(double lct, int ds, int zc, double dy1, int mn1,
                               int yr1, double gdy, int gmn, int gyr,
                               double gLat);

ELunarEclipseStatus LunarEclipseOccurrence(int ds, int zc, double dy, int mn,
                                           int yr);

CLunarEclipseOccurrenceL6855 LunarEclipseOccurrenceL6855(double t, double k);

double UTMaxLunarEclipse(double dy, int mn, int yr, int ds, int zc);

double UTFirstContactLunarEclipse(double dy, int mn, int yr, int ds, int zc);

double UTLastContactLunarEclipse(double dy, int mn, int yr, int ds, int zc);

double UTStartUmbraLunarEclipse(double dy, int mn, int yr, int ds, int zc);

double UTEndUmbraLunarEclipse(double dy, int mn, int yr, int ds, int zc);

double UTStartTotalLunarEclipse(double dy, int mn, int yr, int ds, int zc);

double UTEndTotalLunarEclipse(double dy, int mn, int yr, int ds, int zc);

double MagLunarEclipse(double dy, int mn, int yr, int ds, int zc);

ESolarEclipseStatus SolarEclipseOccurrence(int ds, int zc, double dy, int mn,
                                           int yr);

CSolarEclipseOccurrenceL6855 SolarEclipseOccurrenceL6855(double t, double k);

double UTMaxSolarEclipse(double dy, int mn, int yr, int ds, int zc,
                         double glong, double glat);

CUTMaxSolarEclipseL7390 UTMaxSolarEclipseL7390(double x, double y, double igday,
                                               int gmonth, int gyear, double tm,
                                               double glong, double glat,
                                               double hp);

double UTFirstContactSolarEclipse(double dy, int mn, int yr, int ds, int zc,
                                  double glong, double glat);

CUTFirstContactSolarEclipseL7390
UTFirstContactSolarEclipseL7390(double x, double y, double igday, int gmonth,
                                int gyear, double tm, double glong, double glat,
                                double hp);

double UTLastContactSolarEclipse(double dy, int mn, int yr, int ds, int zc,
                                 double glong, double glat);

CUTLastContactSolarEclipseL7390
UTLastContactSolarEclipseL7390(double x, double y, double igday, int gmonth,
                               int gyear, double tm, double glong, double glat,
                               double hp);

double MagSolarEclipse(double dy, int mn, int yr, int ds, int zc, double glong,
                       double glat);

CMagSolarEclipseL7390 MagSolarEclipseL7390(double x, double y, double igday,
                                           int gmonth, int gyear, double tm,
                                           double glong, double glat,
                                           double hp);

} // namespace pa_macros
#endif