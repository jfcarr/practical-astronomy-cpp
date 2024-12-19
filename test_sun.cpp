
#include "catch2/catch.hpp"
#include "lib/pa_models.h"
#include "lib/pa_sun.h"
#include "lib/pa_types.h"
#include "lib/pa_util.h"

using namespace pa_models;
using namespace pa_types;
using namespace pa_util;

SCENARIO("Approximate Position of Sun") {
  GIVEN("A PASun object") {
    PASun paSun;

    WHEN("Local Civil Time is 00:00:00 and Local Date is 7/27/2003 and "
         "Daylight Savings is false and Zone Correction is 0") {
      CApproximatePositionOfSun result =
          paSun.ApproximatePositionOfSun(0, 0, 0, 27, 7, 2003, false, 0);

      THEN("Right Ascension is 8h 23m 33.73s and Declination is 19d 21m "
           "14.33s") {
        CApproximatePositionOfSun expected =
            CApproximatePositionOfSun(8, 23, 33.73, 19, 21, 14.33);

        REQUIRE(result.declinationDegrees == expected.declinationDegrees);
        REQUIRE(result.declinationMinutes == expected.declinationMinutes);
        REQUIRE(result.declinationSeconds == expected.declinationSeconds);
        REQUIRE(result.rightAscensionHours == expected.rightAscensionHours);
        REQUIRE(result.rightAscensionMinutes == expected.rightAscensionMinutes);
        REQUIRE(result.rightAscensionSeconds == expected.rightAscensionSeconds);
      }
    }
  }
}

SCENARIO("Precise Position of Sun") {
  GIVEN("A PASun object") {
    PASun paSun;

    WHEN("Local Civil Time is 00:00:00 and Local Date is 7/27/1988 and "
         "Daylight Savings is false and Zone Correction is 0") {
      CPrecisePositionOfSun result =
          paSun.PrecisePositionOfSun(0, 0, 0, 27, 7, 1988, false, 0);

      THEN(
          "Right Ascension is 8h 26m 3.83s and Declination is 19d 12m 49.72s") {
        CPrecisePositionOfSun expected =
            CPrecisePositionOfSun(8, 26, 3.83, 19, 12, 49.72);

        REQUIRE(result.declinationDegrees == expected.declinationDegrees);
        REQUIRE(result.declinationMinutes == expected.declinationMinutes);
        REQUIRE(result.declinationSeconds == expected.declinationSeconds);
        REQUIRE(result.rightAscensionHours == expected.rightAscensionHours);
        REQUIRE(result.rightAscensionMinutes == expected.rightAscensionMinutes);
        REQUIRE(result.rightAscensionSeconds == expected.rightAscensionSeconds);
      }
    }
  }
}

SCENARIO("Sun Distance and Angular Size") {
  GIVEN("A PASun object") {
    PASun paSun;

    WHEN("Local Civil Time is 00:00:00 and Local Date is 7/27/1988 and "
         "Daylight Savings is false and Zone Correction is 0") {
      CSunDistanceAngularSize result =
          paSun.SunDistanceAndAngularSize(0, 0, 0, 27, 7, 1988, false, 0);

      THEN("Sun Distance (km) is 151920130 and Sun Angular Size is 0h 31m "
           "29.93s") {
        CSunDistanceAngularSize expected =
            CSunDistanceAngularSize(151920130, 0, 31, 29.93);

        REQUIRE(result.angSizeDeg == expected.angSizeDeg);
        REQUIRE(result.angSizeMin == expected.angSizeMin);
        REQUIRE(result.angSizeSec == expected.angSizeSec);
        REQUIRE(result.distKm == expected.distKm);
      }
    }
  }
}

SCENARIO("Sunrise and Sunset") {
  GIVEN("A PASun object") {
    PASun paSun;

    WHEN("Local date is 3/10/1986 and Geographical Longitude/Latitude is "
         "-71.05d/42.37d") {
      CSunriseAndSunset result =
          paSun.SunriseAndSunset(10, 3, 1986, false, -5, -71.05, 42.37);

      THEN("Local sunrise is 06:05 and local sunset is 17:45 and azimuth of "
           "sunrise/sunset is 94.83d/265.43d") {
        CSunriseAndSunset expected =
            CSunriseAndSunset(6, 5, 17, 45, 94.83, 265.43, ERiseSetStatus::Ok);

        REQUIRE(result.azimuthOfSunriseDeg == expected.azimuthOfSunriseDeg);
        REQUIRE(result.azimuthOfSunsetDeg == expected.azimuthOfSunsetDeg);
        REQUIRE(result.localSunriseHour == expected.localSunriseHour);
        REQUIRE(result.localSunriseMinute == expected.localSunriseMinute);
        REQUIRE(result.localSunsetHour == expected.localSunsetHour);
        REQUIRE(result.localSunsetMinute == expected.localSunsetMinute);
        REQUIRE(result.status == expected.status);
      }
    }
  }
}

SCENARIO("Morning and Evening Twilight") {
  GIVEN("A PASun object") {
    PASun paSun;

    WHEN("Local date is 9/7/1979 and geographical longitude/latitude is 0d/52d "
         "and twilight type is astronomical") {
      CMorningAndEveningTwilight result = paSun.MorningAndEveningTwilight(
          7, 9, 1979, false, 0, 0, 52, ETwilightType::Astronomical);

      THEN("Twilight begins at 03:00 and twilight ends at 20:37 and twilight "
           "status is OK") {
        CMorningAndEveningTwilight expected =
            CMorningAndEveningTwilight(3, 17, 20, 37, ETwilightStatus::Ok);

        REQUIRE(result.amTwilightBeginsHour == expected.amTwilightBeginsHour);
        REQUIRE(result.amTwilightBeginsMin == expected.amTwilightBeginsMin);
        REQUIRE(result.pmTwilightEndsHour == expected.pmTwilightEndsHour);
        REQUIRE(result.pmTwilightEndsMin == expected.pmTwilightEndsMin);
        REQUIRE(result.status == expected.status);
      }
    }
  }
}

SCENARIO("Equation of Time") {
  GIVEN("A PASun object") {
    PASun paSun;

    WHEN("Greenwich date is 7/27/2010") {
      CEquationOfTime result = paSun.EquationOfTime(27, 7, 2010);

      THEN("Equation of time is 06:31.52") {
        CEquationOfTime expected = CEquationOfTime(6, 31.52);

        REQUIRE(result.minutes == expected.minutes);
        REQUIRE(result.seconds == expected.seconds);
      }
    }
  }
}

SCENARIO("Calculate solar elongation for a celestial body") {
  GIVEN("A PASun object") {
    PASun paSun;

    WHEN("Right Ascension is 10h 6m 45s and Declination is 11d 57m 27s and "
         "Greenwich Date is 7/27.8333333/2010") {
      double result =
          paSun.SolarElongation(10, 6, 45, 11, 57, 27, 27.8333333, 7, 2010);

      THEN("Solar Elongation is 24.78d") {
        double expected = 24.78;

        REQUIRE(result == expected);
      }
    }
  }
}