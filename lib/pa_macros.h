
#ifndef _pa_macros
#define _pa_macros
double hms_dh(double hours, double minutes, double seconds);

int decimal_hours_hour(double decimalHours);
int decimal_hours_minute(double decimal_hours);
double decimal_hours_second(double decimal_hours);
double civil_date_to_julian_date(double day, double month, double year);
double julian_date_day(double julian_date);
int julian_date_month(double julian_date);
int julian_date_year(double julian_date);
#endif