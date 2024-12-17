#ifndef _pa_datetime
#define _pa_datetime

#include "pa_models.h"
#include "pa_types.h"
#include <tuple>

using namespace pa_models;

class PADateTime {
public:
  CMonthDayYear GetDateOfEaster(int inputYear);

  int CivilDateToDayNumber(int month, int day, int year);

  double CivilTimeToDecimalHours(double hours, double minutes, double seconds);

  CCivilTime DecimalHoursToCivilTime(double decimalHours);

  CUniversalDateTime
  LocalCivilTimeToUniversalTime(double lctHours, double lctMinutes,
                                double lctSeconds, bool isDaylightSavings,
                                int zoneCorrection, double localDay,
                                int localMonth, int localYear);

  CCivilDateTime UniversalTimeToLocalCivilTime(double utHours, double utMinutes,
                                               double utSeconds,
                                               bool isDaylightSavings,
                                               int zoneCorrection, int gwDay,
                                               int gwMonth, int gwYear);

  CGreenwichSiderealTime
  UniversalTimeToGreenwichSiderealTime(double utHours, double utMinutes,
                                       double utSeconds, double gwDay,
                                       int gwMonth, int gwYear);

  CUniversalTime GreenwichSiderealTimeToUniversalTime(double gstHours,
                                                      double gstMinutes,
                                                      double gstSeconds,
                                                      double gwDay, int gwMonth,
                                                      int gwYear);

  CLocalSiderealTime
  GreenwichSiderealTimeToLocalSiderealTime(double gstHours, double gstMinutes,
                                           double gstSeconds,
                                           double geographicalLongitude);

  CGreenwichSiderealTime
  LocalSiderealTimeToGreenwichSiderealTime(double lstHours, double lstMinutes,
                                           double lstSeconds,
                                           double geographicalLongitude);
};
#endif
