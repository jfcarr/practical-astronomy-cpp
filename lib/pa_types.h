#ifndef _pa_types
#define _pa_types
namespace pa_types {

/**
 * Warning flags for calculation results.
 */
enum class EWarningFlags {
  Ok,     /**< Calculation result is OK. */
  Warning /**< Calculation result is invalid/inaccurate. */
};

/**
 * Angle measurement units.
 */
enum class EAngleMeasurementUnits { Hours, Degrees };

/**
 * Rise/Set status of an object.
 */
enum class ERiseSetStatus {
  Ok,                      /**< Object rises and sets */
  NeverRises,              /**< Object is never visible above the horizon. */
  Circumpolar,             /**< Object never sets. */
  GstToUtConversionWarning /**< Error in conversion. */
};

/**
 * Coordinate types
 */
enum class ECoordinateType {
  Actual,  /**< actual/real */
  Apparent /**< apparent (observer) */
};

/**
 * Status of sunrise/sunset calculation.
 */
enum class ESunRiseSetStatus {
  Ok,             /**< good value */
  ConversionError /**< bad value */
};

/**
 * Status of twilight calculation.
 */
enum class ETwilightStatus {
  Ok,
  ConversionError,
  LastsAllNight,
  SunTooFarBelowHorizon
};

/**
 * \brief Twilight type
 *
 * Maps to degrees-below-horizon.
 */
enum class ETwilightType {
  Civil = 6,        /**< First period of twilight */
  Nautical = 12,    /**< Second period of twilight */
  Astronomical = 18 /**< Third period of twilight */
};

/**
 * \brief Angle measurement units.
 */
enum class EAngleMeasure {
  Degrees, /**< Measurement by degrees */
  Hours    /**< Measurement by hours */
};

/**
 * Level of precision for calculations.
 */
enum class EAccuracyLevel { Approximate, Precise };

} // namespace pa_types
#endif