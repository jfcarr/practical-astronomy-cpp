#include "pa_eclipses.h"
#include "pa_data.h"
#include "pa_macros.h"
#include "pa_models.h"
#include "pa_util.h"
#include <cmath>
#include <string>

using namespace pa_types;
using namespace pa_models;
using namespace pa_util;
using namespace pa_macros;

/**
 * Determine if a lunar eclipse is likely to occur.
 */
CLunarEclipseOccurrence
PAEclipses::LunarEclipseOccurrence(double localDateDay, int localDateMonth,
                                   int localDateYear, bool isDaylightSaving,
                                   int zoneCorrectionHours) {
  int daylightSaving = isDaylightSaving ? 1 : 0;

  double julianDateOfFullMoon =
      FullMoon(daylightSaving, zoneCorrectionHours, localDateDay,
               localDateMonth, localDateYear);

  double gDateOfFullMoonDay = JulianDateDay(julianDateOfFullMoon);
  double integerDay = floor(gDateOfFullMoonDay);
  int gDateOfFullMoonMonth = JulianDateMonth(julianDateOfFullMoon);
  int gDateOfFullMoonYear = JulianDateYear(julianDateOfFullMoon);
  double utOfFullMoonHours = gDateOfFullMoonDay - integerDay;

  double localCivilDateDay = UniversalTimeLocalCivilDay(
      utOfFullMoonHours, 0.0, 0.0, daylightSaving, zoneCorrectionHours,
      integerDay, gDateOfFullMoonMonth, gDateOfFullMoonYear);
  int localCivilDateMonth = UniversalTimeLocalCivilMonth(
      utOfFullMoonHours, 0.0, 0.0, daylightSaving, zoneCorrectionHours,
      integerDay, gDateOfFullMoonMonth, gDateOfFullMoonYear);
  int localCivilDateYear = UniversalTimeLocalCivilYear(
      utOfFullMoonHours, 0.0, 0.0, daylightSaving, zoneCorrectionHours,
      integerDay, gDateOfFullMoonMonth, gDateOfFullMoonYear);

  ELunarEclipseStatus eclipseOccurrence = pa_macros::LunarEclipseOccurrence(
      daylightSaving, zoneCorrectionHours, localDateDay, localDateMonth,
      localDateYear);

  ELunarEclipseStatus status = eclipseOccurrence;
  double eventDateDay = localCivilDateDay;
  int eventDateMonth = localCivilDateMonth;
  int eventDateYear = localCivilDateYear;

  return CLunarEclipseOccurrence(status, eventDateDay, eventDateMonth,
                                 eventDateYear);
}
