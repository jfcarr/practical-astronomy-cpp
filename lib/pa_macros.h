#include "pa_types.h"
#include <tuple>

#ifndef _pa_macros
#define _pa_macros
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
double Refract(double y2, pa_types::CoordinateType sw, double pr, double tr);
double RefractL3035(double pr, double tr, double y, double d);
double ParallaxHa(double hh, double hm, double hs, double dd, double dm,
                  double ds, pa_types::CoordinateType sw, double gp, double ht,
                  double hp);
std::tuple<double, double> ParallaxHaL2870(double x, double y, double rc,
                                           double rp, double rs, double tp);
double ParallaxDec(double hh, double hm, double hs, double dd, double dm,
                   double ds, pa_types::CoordinateType sw, double gp, double ht,
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
double MoonHorizontalParallax(double lh, double lm, double ls, int ds, int zc,
                              double dy, int mn, int yr);
double Unwind(double w);
double SunELong(double gd, int gm, int gy);
double SunPerigee(double gd, int gm, int gy);
double SunEccentricity(double gd, int gm, int gy);
double EclipticDeclination(double eld, double elm, double els, double bd,
                           double bm, double bs, double gd, int gm, int gy);
double EclipticRightAscension(double eld, double elm, double els, double bd,
                              double bm, double bs, double gd, int gm, int gy);
double SunTrueAnomaly(double lch, double lcm, double lcs, int ds, int zc,
                      double ld, int lm, int ly);
double SunriseLocalCivilTime(double ld, int lm, int ly, int ds, int zc,
                             double gl, double gp);
double SunsetLocalCivilTime(double ld, int lm, int ly, int ds, int zc,
                            double gl, double gp);
std::tuple<double, double, double, double, pa_types::RiseSetStatus>
SunriseLocalCivilTimeL3710(double gd, int gm, int gy, double sr, double di,
                           double gp);
std::tuple<double, double, double, double, pa_types::RiseSetStatus>
SunsetLocalCivilTimeL3710(double gd, int gm, int gy, double sr, double di,
                          double gp);
double RiseSetLocalSiderealTimeRise(double rah, double ram, double ras,
                                    double dd, double dm, double ds, double vd,
                                    double g);
double RiseSetLocalSiderealTimeSet(double rah, double ram, double ras,
                                   double dd, double dm, double ds, double vd,
                                   double g);
pa_types::RiseSetStatus ERiseSet(double rah, double ram, double ras, double dd,
                                 double dm, double ds, double vd, double g);
pa_types::WarningFlags EGstUt(double gsh, double gsm, double gss, double gd,
                              int gm, int gy);
double UniversalTimeToLocalCivilTime(double u_hours, double u_minutes,
                                     double u_seconds, int daylight_saving,
                                     int zone_correction, double greenwich_day,
                                     int greenwich_month, int greenwich_year);
pa_types::RiseSetStatus ESunRiseSetCalcStatus(double ld, int lm, int ly, int ds,
                                              int zc, double gl, double gp);
std::tuple<double, double, double, double, pa_types::RiseSetStatus>
ESunRiseSetCalcStatusL3710(double gd, int gm, int gy, double sr, double di,
                           double gp);
double SunriseAzimuth(double ld, int lm, int ly, int ds, int zc, double gl,
                      double gp);
std::tuple<double, double, double, double, pa_types::RiseSetStatus>
SunriseAzimuthL3710(double gd, int gm, int gy, double sr, double di, double gp);
double SunsetAzimuth(double ld, int lm, int ly, int ds, int zc, double gl,
                     double gp);
std::tuple<double, double, double, double, pa_types::RiseSetStatus>
SunsetAzimuthL3710(double gd, int gm, int gy, double sr, double di, double gp);
double RiseSetAzimuthRise(double rah, double ram, double ras, double dd,
                          double dm, double ds, double vd, double g);
double RiseSetAzimuthSet(double rah, double ram, double ras, double dd,
                         double dm, double ds, double vd, double g);
double TwilightAMLocalCivilTime(double ld, int lm, int ly, int ds, int zc,
                                double gl, double gp,
                                pa_types::TwilightType tt);
std::tuple<double, double, double, double, pa_types::RiseSetStatus>
TwilightAMLocalCivilTime_L3710(double gd, int gm, int gy, double sr, double di,
                               double gp);
double TwilightPMLocalCivilTime(double ld, int lm, int ly, int ds, int zc,
                                double gl, double gp,
                                pa_types::TwilightType tt);
std::tuple<double, double, double, double, pa_types::RiseSetStatus>
TwilightPMLocalCivilTime_L3710(double gd, int gm, int gy, double sr, double di,
                               double gp);
pa_types::TwilightStatus ETwilight(double ld, int lm, int ly, int ds, int zc,
                                   double gl, double gp,
                                   pa_types::TwilightType tt);
std::tuple<double, double, double, double, pa_types::TwilightStatus>
ETwilight_L3710(double gd, int gm, int gy, double sr, double di, double gp);
} // namespace pa_macros
#endif