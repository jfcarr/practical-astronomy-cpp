#ifndef _pa_coordinates
#define _pa_coordinates

#include "pa_models.h"
#include "pa_types.h"
#include <tuple>

using namespace pa_models;

class PACoordinates {
public:
  double AngleToDecimalDegrees(double degrees, double minutes, double seconds);

  CAngle DecimalDegreesToAngle(double decimalDegrees);

  CHourAngle RightAscensionToHourAngle(double ra_hours, double ra_minutes,
                                       double ra_seconds, double lct_hours,
                                       double lct_minutes, double lct_seconds,
                                       bool is_daylight_savings,
                                       int zone_correction, double local_day,
                                       int local_month, int local_year,
                                       double geographical_longitude);

  CRightAscension
  HourAngleToRightAscension(double hour_angle_hours, double hour_angle_minutes,
                            double hour_angle_seconds, double lct_hours,
                            double lct_minutes, double lct_seconds,
                            bool is_daylight_savings, int zone_correction,
                            double local_day, int local_month, int local_year,
                            double geographical_longitude);

  CHorizonCoordinates EquatorialCoordinatesToHorizonCoordinates(
      double hour_angle_hours, double hour_angle_minutes,
      double hour_angle_seconds, double declination_degrees,
      double declination_minutes, double declination_seconds,
      double geographical_latitude);

  CEquatorialCoordinatesHA HorizonCoordinatesToEquatorialCoordinates(
      double azimuth_degrees, double azimuth_minutes, double azimuth_seconds,
      double altitude_degrees, double altitude_minutes, double altitude_seconds,
      double geographical_latitude);

  double MeanObliquityOfTheEcliptic(double greenwich_day, int greenwich_month,
                                    int greenwich_year);

  CEquatorialCoordinatesRA EclipticCoordinateToEquatorialCoordinate(
      double ecliptic_longitude_degrees, double ecliptic_longitude_minutes,
      double ecliptic_longitude_seconds, double ecliptic_latitude_degrees,
      double ecliptic_latitude_minutes, double ecliptic_latitude_seconds,
      double greenwich_day, int greenwich_month, int greenwich_year);

  CEqlipticCoordinates EquatorialCoordinateToEclipticCoordinate(
      double ra_hours, double ra_minutes, double ra_seconds, double dec_degrees,
      double dec_minutes, double dec_seconds, double gw_day, int gw_month,
      int gw_year);

  CGalacticCoordinates EquatorialCoordinateToGalacticCoordinate(
      double ra_hours, double ra_minutes, double ra_seconds, double dec_degrees,
      double dec_minutes, double dec_seconds);

  CEquatorialCoordinatesRA GalacticCoordinateToEquatorialCoordinate(
      double gal_long_deg, double gal_long_min, double gal_long_sec,
      double gal_lat_deg, double gal_lat_min, double gal_lat_sec);

  CAngle AngleBetweenTwoObjects(double ra_long_1_hour_deg, double ra_long_1_min,
                                double ra_long_1_sec, double dec_lat_1_deg,
                                double dec_lat_1_min, double dec_lat_1_sec,
                                double ra_long_2_hour_deg, double ra_long_2_min,
                                double ra_long_2_sec, double dec_lat_2_deg,
                                double dec_lat_2_min, double dec_lat_2_sec,
                                pa_types::AngleMeasurementUnits hour_or_degree);

  CRiseSet RisingAndSetting(double ra_hours, double ra_minutes,
                            double ra_seconds, double dec_deg, double dec_min,
                            double dec_sec, double gw_date_day,
                            int gw_date_month, int gw_date_year,
                            double geog_long_deg, double geog_lat_deg,
                            double vert_shift_deg);

  CPrecession CorrectForPrecession(double ra_hour, double ra_minutes,
                                   double ra_seconds, double dec_deg,
                                   double dec_minutes, double dec_seconds,
                                   double epoch_1_day, int epoch_1_month,
                                   int epoch_1_year, double epoch_2_day,
                                   int epoch_2_month, int epoch_2_year);

  CNutation NutationInEclipticLongitudeAndObliquity(double greenwich_day,
                                                    int greenwich_month,
                                                    int greenwich_year);

  CAberration
  CorrectForAberration(double ut_hour, double ut_minutes, double ut_seconds,
                       double gw_day, int gw_month, int gw_year,
                       double true_ecl_long_deg, double true_ecl_long_min,
                       double true_ecl_long_sec, double true_ecl_lat_deg,
                       double true_ecl_lat_min, double true_ecl_lat_sec);

  CAtmosphericRefraction AtmosphericRefraction(
      double true_ra_hour, double true_ra_min, double true_ra_sec,
      double true_dec_deg, double true_dec_min, double true_dec_sec,
      pa_types::CoordinateType coordinate_type1, double geog_long_deg,
      double geog_lat_deg, int daylight_saving_hours, int timezone_hours,
      double lcd_day, int lcd_month, int lcd_year, double lct_hour,
      double lct_min, double lct_sec, double atmospheric_pressure_mbar,
      double atmospheric_temperature_celsius);

  CGeocentricParallax CorrectionsForGeocentricParallax(
      double ra_hour, double ra_min, double ra_sec, double dec_deg,
      double dec_min, double dec_sec, pa_types::CoordinateType coordinate_type,
      double equatorial_hor_parallax_deg, double geog_long_deg,
      double geog_lat_deg, double height_m, int daylight_saving,
      int timezone_hours, double lcd_day, int lcd_month, int lcd_year,
      double lct_hour, double lct_min, double lct_sec);

  CHeliographicCoordinates
  HeliographicCoordinates(double helio_position_angle_deg,
                          double helio_displacement_arcmin, double gwdate_day,
                          int gwdate_month, int gwdate_year);

  int CarringtonRotationNumber(double gwdate_day, int gwdate_month,
                               int gwdate_year);

  CSelenographicCoordinates1 SelenographicCoordinates1(double gwdate_day,
                                                       int gwdate_month,
                                                       int gwdate_year);

  CSelenographicCoordinates2 SelenographicCoordinates2(double gwdate_day,
                                                       int gwdate_month,
                                                       int gwdate_year);
};
#endif