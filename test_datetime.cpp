#include "catch2/catch.hpp"
#include "lib/pa_datetime.h"
#include "lib/pa_models.h"
#include "lib/pa_types.h"
#include "lib/pa_util.h"
#include <iostream>

using namespace pa_types;
using namespace pa_models;
using namespace pa_util;

SCENARIO("Calculate date of Easter", "[date_time") {
  GIVEN("A PADateTime object") {
    PADateTime paDateTime;

    WHEN("The year is 2003") {
      CMonthDayYear result = paDateTime.GetDateOfEaster(2003);

      THEN("The result is 4/20/2003") {
        CMonthDayYear expected = CMonthDayYear(4, 20, 2003);

        REQUIRE(result.month == expected.month);
        REQUIRE(result.day == expected.day);
        REQUIRE(result.year == expected.year);
      }
    }

    WHEN("The year is 2019") {
      CMonthDayYear result = paDateTime.GetDateOfEaster(2019);

      THEN("The result is 4/21/2019") {
        CMonthDayYear expected = CMonthDayYear(4, 21, 2019);

        REQUIRE(result.month == expected.month);
        REQUIRE(result.day == expected.day);
        REQUIRE(result.year == expected.year);
      }
    }

    WHEN("The year is 2020") {
      CMonthDayYear result = paDateTime.GetDateOfEaster(2020);

      THEN("The result is 4/12/2020") {
        CMonthDayYear expected = CMonthDayYear(4, 12, 2020);

        REQUIRE(result.month == expected.month);
        REQUIRE(result.day == expected.day);
        REQUIRE(result.year == expected.year);
      }
    }
  }
}

SCENARIO("Calculate civil day number", "[date_time]") {
  GIVEN("A PADateTime object") {
    PADateTime paDateTime;

    WHEN("The date is 1/1/2000") {

      int result = paDateTime.CivilDateToDayNumber(1, 1, 2000);

      THEN("The result is 1") { REQUIRE(result == 1); }
    }

    WHEN("The date is 3/1/2000") {

      int result = paDateTime.CivilDateToDayNumber(3, 1, 2000);

      THEN("The result is 61") { REQUIRE(result == 61); }
    }

    WHEN("The date is 6/1/2003") {

      int result = paDateTime.CivilDateToDayNumber(6, 1, 2003);

      THEN("The result is 152") { REQUIRE(result == 152); }
    }

    WHEN("The date is 11/27/2009") {

      int result = paDateTime.CivilDateToDayNumber(11, 27, 2009);

      THEN("The result is 331") { REQUIRE(result == 331); }
    }
  }
}

SCENARIO("Convert civil time to and from decimal hours", "[date_time]") {
  GIVEN("A PADateTime object") {
    PADateTime paDateTime;

    WHEN("Civil time is 18:31:27") {
      double result = paDateTime.CivilTimeToDecimalHours(18, 31, 27);

      THEN("Decimal hours is 18.52416667") {
        REQUIRE(Round(result, 8) == 18.52416667);
      }
    }

    WHEN("Decimal hours is 18.52416667") {
      CCivilTime result = paDateTime.DecimalHoursToCivilTime(18.52416667);

      THEN("Civil time is 18:31:27") {
        CCivilTime expected = CCivilTime(18, 31, 27);

        REQUIRE(result.hours == expected.hours);
        REQUIRE(result.minutes == expected.minutes);
        REQUIRE(result.seconds == expected.seconds);
      }
    }
  }
}

SCENARIO("Convert civil time to and from universal time", "[date_time]") {
  GIVEN("A PADateTime object") {
    PADateTime paDateTime;

    WHEN("Civil time is 03:37:00") {
      CUniversalDateTime result = paDateTime.LocalCivilTimeToUniversalTime(
          3, 37, 0, true, 4, 1, 7, 2013);

      THEN("Universal time is 22:37:00") {
        CUniversalDateTime expected =
            CUniversalDateTime(22, 37, 0, 30, 6, 2013);

        REQUIRE(result.hours == expected.hours);
        REQUIRE(result.minutes == expected.minutes);
        REQUIRE(result.seconds == expected.seconds);
        REQUIRE(result.day == expected.day);
        REQUIRE(result.month == expected.month);
        REQUIRE(result.year == expected.year);
      }
    }

    WHEN("Universal time is 22:37:00") {
      CCivilDateTime result = paDateTime.UniversalTimeToLocalCivilTime(
          22, 37, 0, true, 4, 30, 6, 2013);

      THEN("Civil time is 03:37:00") {
        CCivilDateTime expected = CCivilDateTime(3, 37, 0, 1, 7, 2013);

        REQUIRE(result.hours == expected.hours);
        REQUIRE(result.minutes == expected.minutes);
        REQUIRE(result.seconds == expected.seconds);
        REQUIRE(result.day == expected.day);
        REQUIRE(result.month == expected.month);
        REQUIRE(result.year == expected.year);
      }
    }
  }
}

SCENARIO("Convert universal time to and from Greenwich sidereal time",
         "[date_time]") {
  GIVEN("A PADateTime object") {
    PADateTime paDateTime;

    WHEN("Universal time is 14:36:51.67") {
      CGreenwichSiderealTime result =
          paDateTime.UniversalTimeToGreenwichSiderealTime(14, 36, 51.67, 22, 4,
                                                          1980);

      THEN("Greenwich sidereal time is 4:40:5.23") {
        CGreenwichSiderealTime expected = CGreenwichSiderealTime(4, 40, 5.23);

        REQUIRE(result.hours == expected.hours);
        REQUIRE(result.minutes == expected.minutes);
        REQUIRE(result.seconds == expected.seconds);
      }
    }

    WHEN("Greenwich sidereal time is 4:40:5.23") {
      CUniversalTime result = paDateTime.GreenwichSiderealTimeToUniversalTime(
          4, 40, 5.23, 22, 4, 1980);

      THEN("Universal time is 14:36:51.67") {
        CUniversalTime expected =
            CUniversalTime(14, 36, 51.67, EWarningFlags::Ok);

        REQUIRE(result.hours == expected.hours);
        REQUIRE(result.minutes == expected.minutes);
        REQUIRE(result.seconds == expected.seconds);
        REQUIRE(result.warningFlag == expected.warningFlag);
      }
    }
  }
}

SCENARIO("Convert Greenwich Sidereal Time to and from Local Sidereal Time",
         "[date_time]") {
  GIVEN("A PADateTime object") {
    PADateTime paDateTime;

    WHEN("Greenwich Sidereal Time is 04:40:05.23, with Geographical Longitude "
         "of -64") {
      CLocalSiderealTime result =
          paDateTime.GreenwichSiderealTimeToLocalSiderealTime(4, 40, 5.23, -64);

      THEN("Local Sidereal Time is 00:24:5.23") {
        CLocalSiderealTime expected = CLocalSiderealTime(0, 24, 5.23);

        REQUIRE(result.hours == expected.hours);
        REQUIRE(result.minutes == expected.minutes);
        REQUIRE(result.seconds == expected.seconds);
      }
    }

    WHEN("Local Sidereal Time is 00:24:05.23, with Geographical Longitude "
         "of -64") {
      CGreenwichSiderealTime result =
          paDateTime.LocalSiderealTimeToGreenwichSiderealTime(0, 24, 5.23, -64);

      THEN("Greenwich Sidereal Time is 04:40:5.23") {
        CGreenwichSiderealTime expected = CGreenwichSiderealTime(4, 40, 5.23);

        REQUIRE(result.hours == expected.hours);
        REQUIRE(result.minutes == expected.minutes);
        REQUIRE(result.seconds == expected.seconds);
      }
    }
  }
}