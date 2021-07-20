#include "pa_util.h"

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
