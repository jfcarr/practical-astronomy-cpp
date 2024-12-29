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

/**
 * Calculate the circumstances of a lunar eclipse.
 */
CLunarEclipseCircumstances
PAEclipses::LunarEclipseCircumstances(double localDateDay, int localDateMonth,
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

  double utMaxEclipse =
      UTMaxLunarEclipse(localDateDay, localDateMonth, localDateYear,
                        daylightSaving, zoneCorrectionHours);
  double utFirstContact =
      UTFirstContactLunarEclipse(localDateDay, localDateMonth, localDateYear,
                                 daylightSaving, zoneCorrectionHours);
  double utLastContact =
      UTLastContactLunarEclipse(localDateDay, localDateMonth, localDateYear,
                                daylightSaving, zoneCorrectionHours);
  double utStartUmbralPhase =
      UTStartUmbraLunarEclipse(localDateDay, localDateMonth, localDateYear,
                               daylightSaving, zoneCorrectionHours);
  double utEndUmbralPhase =
      UTEndUmbraLunarEclipse(localDateDay, localDateMonth, localDateYear,
                             daylightSaving, zoneCorrectionHours);
  double utStartTotalPhase =
      UTStartTotalLunarEclipse(localDateDay, localDateMonth, localDateYear,
                               daylightSaving, zoneCorrectionHours);
  double utEndTotalPhase =
      UTEndTotalLunarEclipse(localDateDay, localDateMonth, localDateYear,
                             daylightSaving, zoneCorrectionHours);

  double eclipseMagnitude1 =
      MagLunarEclipse(localDateDay, localDateMonth, localDateYear,
                      daylightSaving, zoneCorrectionHours);

  double lunarEclipseCertainDateDay = localCivilDateDay;
  int lunarEclipseCertainDateMonth = localCivilDateMonth;
  int lunarEclipseCertainDateYear = localCivilDateYear;

  double utStartPenPhaseHour =
      (utFirstContact == -99.0) ? -99.0
                                : DecimalHoursHour(utFirstContact + 0.008333);
  double utStartPenPhaseMinutes =
      (utFirstContact == -99.0) ? -99.0
                                : DecimalHoursMinute(utFirstContact + 0.008333);

  double utStartUmbralPhaseHour =
      (utStartUmbralPhase == -99.0)
          ? -99.0
          : DecimalHoursHour(utStartUmbralPhase + 0.008333);
  double utStartUmbralPhaseMinutes =
      (utStartUmbralPhase == -99.0)
          ? -99.0
          : DecimalHoursMinute(utStartUmbralPhase + 0.008333);

  double utStartTotalPhaseHour =
      (utStartTotalPhase == -99.0)
          ? -99.0
          : DecimalHoursHour(utStartTotalPhase + 0.008333);
  double utStartTotalPhaseMinutes =
      (utStartTotalPhase == -99.0)
          ? -99.0
          : DecimalHoursMinute(utStartTotalPhase + 0.008333);

  double utMidEclipseHour = (utMaxEclipse == -99.0)
                                ? -99.0
                                : DecimalHoursHour(utMaxEclipse + 0.008333);
  double utMidEclipseMinutes =
      (utMaxEclipse == -99.0) ? -99.0
                              : DecimalHoursMinute(utMaxEclipse + 0.008333);

  double utEndTotalPhaseHour =
      (utEndTotalPhase == -99.0) ? -99.0
                                 : DecimalHoursHour(utEndTotalPhase + 0.008333);
  double utEndTotalPhaseMinutes =
      (utEndTotalPhase == -99.0)
          ? -99.0
          : DecimalHoursMinute(utEndTotalPhase + 0.008333);

  double utEndUmbralPhaseHour =
      (utEndUmbralPhase == -99.0)
          ? -99.0
          : DecimalHoursHour(utEndUmbralPhase + 0.008333);
  double utEndUmbralPhaseMinutes =
      (utEndUmbralPhase == -99.0)
          ? -99.0
          : DecimalHoursMinute(utEndUmbralPhase + 0.008333);

  double utEndPenPhaseHour = (utLastContact == -99.0)
                                 ? -99.0
                                 : DecimalHoursHour(utLastContact + 0.008333);
  double utEndPenPhaseMinutes =
      (utLastContact == -99.0) ? -99.0
                               : DecimalHoursMinute(utLastContact + 0.008333);

  double eclipseMagnitude =
      (eclipseMagnitude1 == -99.0) ? -99.0 : Round(eclipseMagnitude1, 2);

  return CLunarEclipseCircumstances(
      lunarEclipseCertainDateDay, lunarEclipseCertainDateMonth,
      lunarEclipseCertainDateYear, utStartPenPhaseHour, utStartPenPhaseMinutes,
      utStartUmbralPhaseHour, utStartUmbralPhaseMinutes, utStartTotalPhaseHour,
      utStartTotalPhaseMinutes, utMidEclipseHour, utMidEclipseMinutes,
      utEndTotalPhaseHour, utEndTotalPhaseMinutes, utEndUmbralPhaseHour,
      utEndUmbralPhaseMinutes, utEndPenPhaseHour, utEndPenPhaseMinutes,
      eclipseMagnitude);
}

/**
 * Determine if a solar eclipse is likely to occur.
 */
CSolarEclipseOccurrence
PAEclipses::SolarEclipseOccurrence(double localDateDay, int localDateMonth,
                                   int localDateYear, bool isDaylightSaving,
                                   int zoneCorrectionHours) {
  int daylightSaving = isDaylightSaving ? 1 : 0;

  double julianDateOfNewMoon =
      NewMoon(daylightSaving, zoneCorrectionHours, localDateDay, localDateMonth,
              localDateYear);
  double gDateOfNewMoonDay = JulianDateDay(julianDateOfNewMoon);
  double integerDay = floor(gDateOfNewMoonDay);
  int gDateOfNewMoonMonth = JulianDateMonth(julianDateOfNewMoon);
  int gDateOfNewMoonYear = JulianDateYear(julianDateOfNewMoon);
  double utOfNewMoonHours = gDateOfNewMoonDay - integerDay;

  double localCivilDateDay = UniversalTimeLocalCivilDay(
      utOfNewMoonHours, 0.0, 0.0, daylightSaving, zoneCorrectionHours,
      integerDay, gDateOfNewMoonMonth, gDateOfNewMoonYear);
  int localCivilDateMonth = UniversalTimeLocalCivilMonth(
      utOfNewMoonHours, 0.0, 0.0, daylightSaving, zoneCorrectionHours,
      integerDay, gDateOfNewMoonMonth, gDateOfNewMoonYear);
  int localCivilDateYear = UniversalTimeLocalCivilYear(
      utOfNewMoonHours, 0.0, 0.0, daylightSaving, zoneCorrectionHours,
      integerDay, gDateOfNewMoonMonth, gDateOfNewMoonYear);

  enum ESolarEclipseStatus eclipseOccurrence =
      pa_macros::SolarEclipseOccurrence(daylightSaving, zoneCorrectionHours,
                                        localDateDay, localDateMonth,
                                        localDateYear);

  enum ESolarEclipseStatus status = eclipseOccurrence;
  double eventDateDay = localCivilDateDay;
  int eventDateMonth = localCivilDateMonth;
  int eventDateYear = localCivilDateYear;

  return CSolarEclipseOccurrence(status, eventDateDay, eventDateMonth,
                                 eventDateYear);
}