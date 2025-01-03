#ifndef _pa_eclipses
#define _pa_eclipses

#include "pa_models.h"
#include <string>
#include <tuple>

using namespace pa_models;

class PAEclipses {
public:
  CLunarEclipseOccurrence LunarEclipseOccurrence(double localDateDay,
                                                 int localDateMonth,
                                                 int localDateYear,
                                                 bool isDaylightSaving,
                                                 int zoneCorrectionHours);

  CLunarEclipseCircumstances LunarEclipseCircumstances(double localDateDay,
                                                       int localDateMonth,
                                                       int localDateYear,
                                                       bool isDaylightSaving,
                                                       int zoneCorrectionHours);

  CSolarEclipseOccurrence SolarEclipseOccurrence(double localDateDay,
                                                 int localDateMonth,
                                                 int localDateYear,
                                                 bool isDaylightSaving,
                                                 int zoneCorrectionHours);

  CSolarEclipseCircumstances
  SolarEclipseCircumstances(double localDateDay, int localDateMonth,
                            int localDateYear, bool isDaylightSaving,
                            int zoneCorrectionHours, double geogLongitudeDeg,
                            double geogLatitudeDeg);
};

#endif