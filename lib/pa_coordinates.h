#ifndef _pa_coordinates
#define _pa_coordinates

#include "pa_types.h"
#include <tuple>

class PACoordinates {
public:
  double angle_to_decimal_degrees(double degrees, double minutes,
                                  double seconds);

  std::tuple<double, double, double>
  decimal_degrees_to_angle(double decimal_degrees);

  std::tuple<double, double, double> right_ascension_to_hour_angle(
      double ra_hours, double ra_minutes, double ra_seconds, double lct_hours,
      double lct_minutes, double lct_seconds, bool is_daylight_savings,
      int zone_correction, double local_day, int local_month, int local_year,
      double geographical_longitude);

  std::tuple<double, double, double> hour_angle_to_right_ascension(
      double hour_angle_hours, double hour_angle_minutes,
      double hour_angle_seconds, double lct_hours, double lct_minutes,
      double lct_seconds, bool is_daylight_savings, int zone_correction,
      double local_day, int local_month, int local_year,
      double geographical_longitude);

  std::tuple<double, double, double, double, double, double>
  equatorial_coordinates_to_horizon_coordinates(double hour_angle_hours,
                                                double hour_angle_minutes,
                                                double hour_angle_seconds,
                                                double declination_degrees,
                                                double declination_minutes,
                                                double declination_seconds,
                                                double geographical_latitude);

  std::tuple<double, double, double, double, double, double>
  horizon_coordinates_to_equatorial_coordinates(
      double azimuth_degrees, double azimuth_minutes, double azimuth_seconds,
      double altitude_degrees, double altitude_minutes, double altitude_seconds,
      double geographical_latitude);

  double mean_obliquity_of_the_ecliptic(double greenwich_day,
                                        int greenwich_month,
                                        int greenwich_year);

  std::tuple<double, double, double, double, double, double>
  ecliptic_coordinate_to_equatorial_coordinate(
      double ecliptic_longitude_degrees, double ecliptic_longitude_minutes,
      double ecliptic_longitude_seconds, double ecliptic_latitude_degrees,
      double ecliptic_latitude_minutes, double ecliptic_latitude_seconds,
      double greenwich_day, int greenwich_month, int greenwich_year);

  std::tuple<double, double, double, double, double, double>
  equatorial_coordinate_to_ecliptic_coordinate(
      double ra_hours, double ra_minutes, double ra_seconds, double dec_degrees,
      double dec_minutes, double dec_seconds, double gw_day, int gw_month,
      int gw_year);

  std::tuple<double, double, double, double, double, double>
  equatorial_coordinate_to_galactic_coordinate(
      double ra_hours, double ra_minutes, double ra_seconds, double dec_degrees,
      double dec_minutes, double dec_seconds);

  std::tuple<double, double, double, double, double, double>
  galactic_coordinate_to_equatorial_coordinate(
      double gal_long_deg, double gal_long_min, double gal_long_sec,
      double gal_lat_deg, double gal_lat_min, double gal_lat_sec);

  std::tuple<double, double, double> angle_between_two_objects(
      double ra_long_1_hour_deg, double ra_long_1_min, double ra_long_1_sec,
      double dec_lat_1_deg, double dec_lat_1_min, double dec_lat_1_sec,
      double ra_long_2_hour_deg, double ra_long_2_min, double ra_long_2_sec,
      double dec_lat_2_deg, double dec_lat_2_min, double dec_lat_2_sec,
      pa_types::angle_measurement_units hour_or_degree);

  std::tuple<pa_types::rise_set_status, double, double, double, double, double,
             double>
  rising_and_setting(double ra_hours, double ra_minutes, double ra_seconds,
                     double dec_deg, double dec_min, double dec_sec,
                     double gw_date_day, int gw_date_month, int gw_date_year,
                     double geog_long_deg, double geog_lat_deg,
                     double vert_shift_deg);

  std::tuple<double, double, double, double, double, double>
  correct_for_precession(double ra_hour, double ra_minutes, double ra_seconds,
                         double dec_deg, double dec_minutes, double dec_seconds,
                         double epoch_1_day, int epoch_1_month,
                         int epoch_1_year, double epoch_2_day,
                         int epoch_2_month, int epoch_2_year);

  std::tuple<double, double> nutation_in_ecliptic_longitude_and_obliquity(
      double greenwich_day, int greenwich_month, int greenwich_year);

  std::tuple<double, double, double, double, double, double>
  correct_for_aberration(double ut_hour, double ut_minutes, double ut_seconds,
                         double gw_day, int gw_month, int gw_year,
                         double true_ecl_long_deg, double true_ecl_long_min,
                         double true_ecl_long_sec, double true_ecl_lat_deg,
                         double true_ecl_lat_min, double true_ecl_lat_sec);

  std::tuple<double, double, double, double, double, double>
  atmospheric_refraction(double true_ra_hour, double true_ra_min,
                         double true_ra_sec, double true_dec_deg,
                         double true_dec_min, double true_dec_sec,
                         pa_types::coordinate_type coordinate_type1,
                         double geog_long_deg, double geog_lat_deg,
                         int daylight_saving_hours, int timezone_hours,
                         double lcd_day, int lcd_month, int lcd_year,
                         double lct_hour, double lct_min, double lct_sec,
                         double atmospheric_pressure_mbar,
                         double atmospheric_temperature_celsius);
};
#endif