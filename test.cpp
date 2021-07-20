#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this
                          // in one cpp file
#include "catch2/catch.hpp"
#include "lib/pa_datetime.h"

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
