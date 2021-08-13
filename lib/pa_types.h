#ifndef _pa_types
#define _pa_types
namespace pa_types {
/**
 * Warning flags for calculation results.
 */
enum class WarningFlags {
  Ok,     /**< Calculation result is OK. */
  Warning /**< Calculation result is invalid/inaccurate. */
};

/**
 * Angle measurement units.
 */
enum AngleMeasurementUnits { Hours, Degrees };

/**
 * Rise/Set status of an object.
 */
enum class RiseSetStatus {
  Ok,                      /**< Object rises and sets */
  NeverRises,              /**< Object is never visible above the horizon. */
  Circumpolar,             /**< Object never sets. */
  GstToUtConversionWarning /**< Error in conversion. */
};

/**
 * Coordinate types
 */
enum class CoordinateType {
  Actual,  /**< actual/real */
  Apparent /**< apparent (observer) */
};

/**
 * Status of sunrise/sunset calculation.
 *
 */
enum class SunRiseSetStatus {
  Ok,             /**< good value */
  ConversionError /**< bad value */
};
} // namespace pa_types
#endif