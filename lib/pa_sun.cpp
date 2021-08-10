#include "pa_sun.h"
#include "pa_macros.h"
#include "pa_types.h"
#include "pa_util.h"
#include <cmath>

using namespace pa_types;
using namespace pa_util;
using namespace pa_macros;

/**
 * \brief Calculate approximate position of the sun for a local date and time.
 *
 * @return tuple <double sun_ra_hour, double sun_ra_main, double sun_ra_sec,
 * double sun_dec_deg, double sun_dec_min, double sun_dec_sec>
 */
std::tuple<double, double, double, double, double, double>
PASun::approximate_position_of_sun(double lct_hours, double lct_minutes,
                                   double lct_seconds, double local_day,
                                   int local_month, int local_year,
                                   bool is_daylight_saving,
                                   int zone_correction) {
  int daylight_saving = (is_daylight_saving == true) ? 1 : 0;

  double greenwich_date_day = local_civil_time_greenwich_day(
      lct_hours, lct_minutes, lct_seconds, daylight_saving, zone_correction,
      local_day, local_month, local_year);
  int greenwich_date_month = local_civil_time_greenwich_month(
      lct_hours, lct_minutes, lct_seconds, daylight_saving, zone_correction,
      local_day, local_month, local_year);
  int greenwich_date_year = local_civil_time_greenwich_year(
      lct_hours, lct_minutes, lct_seconds, daylight_saving, zone_correction,
      local_day, local_month, local_year);
  double ut_hours = local_civil_time_to_universal_time(
      lct_hours, lct_minutes, lct_seconds, daylight_saving, zone_correction,
      local_day, local_month, local_year);
  double ut_days = ut_hours / 24;
  double jd_days =
      civil_date_to_julian_date(greenwich_date_day, greenwich_date_month,
                                greenwich_date_year) +
      ut_days;
  double d_days = jd_days - civil_date_to_julian_date(0, 1, 2010);
  double n_deg = 360 * d_days / 365.242191;
  double m_deg1 = n_deg + sun_e_long(0, 1, 2010) - sun_peri(0, 1, 2010);
  double m_deg2 = m_deg1 - 360 * floor(m_deg1 / 360);
  double e_c_deg =
      360 * sun_ecc(0, 1, 2010) * sin(degrees_to_radians(m_deg2)) / M_PI;
  double l_s_deg1 = n_deg + e_c_deg + sun_e_long(0, 1, 2010);
  double l_s_deg2 = l_s_deg1 - 360 * floor(l_s_deg1 / 360);
  double ra_deg = pa_macros::ec_ra(l_s_deg2, 0, 0, 0, 0, 0, greenwich_date_day,
                                   greenwich_date_month, greenwich_date_year);
  double ra_hours = decimal_degrees_to_degree_hours(ra_deg);
  double dec_deg =
      pa_macros::ec_dec(l_s_deg2, 0, 0, 0, 0, 0, greenwich_date_day,
                        greenwich_date_month, greenwich_date_year);

  int sun_ra_hour = decimal_hours_hour(ra_hours);
  int sun_ra_min = decimal_hours_minute(ra_hours);
  double sun_ra_sec = decimal_hours_second(ra_hours);
  double sun_dec_deg = decimal_degrees_degrees(dec_deg);
  double sun_dec_min = decimal_degrees_minutes(dec_deg);
  double sun_dec_sec = decimal_degrees_seconds(dec_deg);

  return std::tuple<double, double, double, double, double, double>{
      sun_ra_hour, sun_ra_min,  sun_ra_sec,
      sun_dec_deg, sun_dec_min, sun_dec_sec};
}

/**
 * \brief Calculate precise position of the sun for a local date and time.
 */
std::tuple<double, double, double, double, double, double>
PASun::precise_position_of_sun(double lct_hours, double lct_minutes,
                               double lct_seconds, double local_day,
                               int local_month, int local_year,
                               bool is_daylight_saving, int zone_correction) {
  int daylight_saving = (is_daylight_saving == true) ? 1 : 0;

  double g_day = local_civil_time_greenwich_day(
      lct_hours, lct_minutes, lct_seconds, daylight_saving, zone_correction,
      local_day, local_month, local_year);
  int g_month = local_civil_time_greenwich_month(
      lct_hours, lct_minutes, lct_seconds, daylight_saving, zone_correction,
      local_day, local_month, local_year);
  int g_year = local_civil_time_greenwich_year(
      lct_hours, lct_minutes, lct_seconds, daylight_saving, zone_correction,
      local_day, local_month, local_year);
  double sun_ecliptic_longitude_deg =
      sun_long(lct_hours, lct_minutes, lct_seconds, daylight_saving,
               zone_correction, local_day, local_month, local_year);
  double ra_deg =
      ec_ra(sun_ecliptic_longitude_deg, 0, 0, 0, 0, 0, g_day, g_month, g_year);
  double ra_hours = decimal_degrees_to_degree_hours(ra_deg);
  double dec_deg =
      ec_dec(sun_ecliptic_longitude_deg, 0, 0, 0, 0, 0, g_day, g_month, g_year);

  int sun_ra_hour = decimal_hours_hour(ra_hours);
  int sun_ra_min = decimal_hours_minute(ra_hours);
  double sun_ra_sec = decimal_hours_second(ra_hours);
  double sun_dec_deg = decimal_degrees_degrees(dec_deg);
  double sun_dec_min = decimal_degrees_minutes(dec_deg);
  double sun_dec_sec = decimal_degrees_seconds(dec_deg);

  return std::tuple<double, double, double, double, double, double>{
      sun_ra_hour, sun_ra_min,  sun_ra_sec,
      sun_dec_deg, sun_dec_min, sun_dec_sec};
}
