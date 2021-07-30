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
};
#endif