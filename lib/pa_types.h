#ifndef _pa_types
#define _pa_types
/**
 * Warning flags for calculation results.
 */
enum pa_warning_flags {
  ok,     /**< Calculation result is OK. */
  warning /**< Calculation result is invalid/inaccurate. */
};
#endif