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
} // namespace pa_types
#endif