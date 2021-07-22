#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this
                          // in one cpp file
#include "catch2/catch.hpp"
#include "lib/pa_datetime.h"
#include "lib/pa_util.h"
#include <iostream>

SCENARIO("Calculate date of Easter", "[date_time") {
  GIVEN("A PADateTime object") {
    PADateTime paDateTime;

    WHEN("The year is 2003") {
      full_date result = paDateTime.get_date_of_easter(2003);

      THEN("The result is 4/20/2003") {
        REQUIRE(result.month == 4);
        REQUIRE(result.day == 20);
        REQUIRE(result.year == 2003);
      }
    }

    WHEN("The year is 2019") {
      full_date result = paDateTime.get_date_of_easter(2019);

      THEN("The result is 4/21/2019") {
        REQUIRE(result.month == 4);
        REQUIRE(result.day == 21);
        REQUIRE(result.year == 2019);
      }
    }

    WHEN("The year is 2020") {
      full_date result = paDateTime.get_date_of_easter(2020);

      THEN("The result is 4/12/2020") {
        REQUIRE(result.month == 4);
        REQUIRE(result.day == 12);
        REQUIRE(result.year == 2020);
      }
    }
  }
}

SCENARIO("Calculate civil day number, [date_time]") {
  GIVEN("A PADateTime object") {
    PADateTime paDateTime;

    WHEN("The date is 1/1/2000") {

      int result = paDateTime.civil_date_to_day_number(1, 1, 2000);

      THEN("The result is 1") { REQUIRE(result == 1); }
    }

    WHEN("The date is 3/1/2000") {

      int result = paDateTime.civil_date_to_day_number(3, 1, 2000);

      THEN("The result is 61") { REQUIRE(result == 61); }
    }

    WHEN("The date is 6/1/2003") {

      int result = paDateTime.civil_date_to_day_number(6, 1, 2003);

      THEN("The result is 152") { REQUIRE(result == 152); }
    }

    WHEN("The date is 11/27/2009") {

      int result = paDateTime.civil_date_to_day_number(11, 27, 2009);

      THEN("The result is 331") { REQUIRE(result == 331); }
    }
  }
}

SCENARIO("Convert civil time to and from decimal hours, [date_time]") {
  GIVEN("A PADateTime object") {
    PADateTime paDateTime;

    WHEN("Civil time is 18:31:27") {
      double result = paDateTime.civil_time_to_decimal_hours(18, 31, 27);

      THEN("Decimal hours is 18.52416667") {
        REQUIRE(round_d(result, 8) == 18.52416667);
      }
    }

    WHEN("Decimal hours is 18.52416667") {
      std::tuple<double, double, double> result =
          paDateTime.decimal_hours_to_civil_time(18.52416667);
      std::tuple<double, double, double> expected = std::make_tuple(18, 31, 27);

      THEN("Civil time is 18:31:27") {
        REQUIRE(std::get<0>(result) == std::get<0>(expected));
        REQUIRE(std::get<1>(result) == std::get<1>(expected));
        REQUIRE(round_d(std::get<2>(result), 0) == std::get<2>(expected));
      }
    }
  }
}