#ifndef _pa_types
#define _pa_types
namespace pa_types {
/**
 * Warning flags for calculation results.
 */
enum warning_flags {
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
enum rise_set_status {
  rise_set_ok, /**< Object rises and sets */
  never_rises, /**< Object is never visible above the horizon. */
  circumpolar  /**< Object never sets. */
};
} // namespace pa_types
#endif