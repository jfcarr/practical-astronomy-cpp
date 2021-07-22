#include "pa_util.h"
#include <cmath>
#include <iostream>

bool is_leap_year(int input_year) {
  double year = (double)input_year;

  if ((int)year % 4 == 0) {
    if ((int)year % 100 == 0) {
      return ((int)year % 400 == 0) ? true : false;
    } else {
      return true;
    }
  } else {
    return false;
  }
}

double round_d(double input, int places) {
  double multiplier = pow(10, places);

  double a = input * multiplier;
  a = (a >= 0) ? a + 0.5 : a - 0.5;

  return (int)a / multiplier;
}