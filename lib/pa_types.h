#ifndef _pa_types
#define _pa_types
namespace pa_types {
/**
 * Warning flags for calculation results.
 */
enum class warning_flags {
  ok,     /**< Calculation result is OK. */
  warning /**< Calculation result is invalid/inaccurate. */
};

/**
 * Angle measurement units.
 */
enum angle_measurement_units { hours, degrees };

/**
 * Rise/Set status of an object.
 */
enum class rise_set_status {
  ok,          /**< Object rises and sets */
  never_rises, /**< Object is never visible above the horizon. */
  circumpolar  /**< Object never sets. */
};

/**
 * Coordinate types
 */
enum class coordinate_type {
  actual,  /**< actual/real */
  apparent /**< apparent (observer) */
};
} // namespace pa_types
#endif