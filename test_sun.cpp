
#include "catch2/catch.hpp"
#include "lib/pa_sun.h"
#include "lib/pa_types.h"
#include "lib/pa_util.h"
#include <iostream>

using namespace pa_types;
using namespace pa_util;

SCENARIO("Approximate Position of Sun") {
  GIVEN("A PASun object") {
    PASun paSun;

    WHEN("Local Civil Time is 00:00:00 and Local Date is 7/27/2003 and "
         "Daylight Savings is false and Zone Correction is 0") {
      std::tuple<double, double, double, double, double, double> result =
          paSun.approximate_position_of_sun(0, 0, 0, 27, 7, 2003, false, 0);

      THEN("Right Ascension is 8h 23m 33.73s and Declination is 19d 21m "
           "14.33s") {
        std::tuple<double, double, double, double, double, double> expected =
            std::make_tuple(8, 23, 33.73, 19, 21, 14.33);

        REQUIRE(std::get<0>(result) == std::get<0>(expected));
        REQUIRE(std::get<1>(result) == std::get<1>(expected));
        REQUIRE(std::get<2>(result) == std::get<2>(expected));
        REQUIRE(std::get<3>(result) == std::get<3>(expected));
        REQUIRE(std::get<4>(result) == std::get<4>(expected));
        REQUIRE(std::get<5>(result) == std::get<5>(expected));
      }
    }
  }
}

SCENARIO("Precise Position of Sun") {
  GIVEN("A PASun object") {
    PASun paSun;
    WHEN("Local Civil Time is 00:00:00 and Local Date is 7/27/1988 and "
         "Daylight Savings is false and Zone Correction is 0") {
      std::tuple<double, double, double, double, double, double> result =
          paSun.precise_position_of_sun(0, 0, 0, 27, 7, 1988, false, 0);
      THEN(
          "Right Ascension is 8h 26m 3.83s and Declination is 19d 12m 49.72s") {
        std::tuple<double, double, double, double, double, double> expected =
            std::make_tuple(8, 26, 3.83, 19, 12, 49.72);

        REQUIRE(std::get<0>(result) == std::get<0>(expected));
        REQUIRE(std::get<1>(result) == std::get<1>(expected));
        REQUIRE(std::get<2>(result) == std::get<2>(expected));
        REQUIRE(std::get<3>(result) == std::get<3>(expected));
        REQUIRE(std::get<4>(result) == std::get<4>(expected));
        REQUIRE(std::get<5>(result) == std::get<5>(expected));
      }
    }
  }
}