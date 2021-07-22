#ifndef _pa_datetime
#define _pa_datetime

#include <tuple>
struct full_date {
  int month;
  int day;
  int year;
};

struct full_time {
  int hours;
  int minutes;
  double seconds;
};

class PADateTime {
public:
  struct full_date get_date_of_easter(int input_year);
  int civil_date_to_day_number(int month, int day, int year);
  double civil_time_to_decimal_hours(double hours, double minutes,
                                     double seconds);
  std::tuple<double, double, double>
  decimal_hours_to_civil_time(double decimal_hours);
};
#endif
