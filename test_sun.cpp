
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
          paSun.ApproximatePositionOfSun(0, 0, 0, 27, 7, 2003, false, 0);

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
          paSun.PrecisePositionOfSun(0, 0, 0, 27, 7, 1988, false, 0);

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

SCENARIO("Sun Distance and Angular Size") {
  GIVEN("A PASun object") {
    PASun paSun;

    WHEN("Local Civil Time is 00:00:00 and Local Date is 7/27/1988 and "
         "Daylight Savings is false and Zone Correction is 0") {
      std::tuple<double, double, double, double> result =
          paSun.SunDistanceAndAngularSize(0, 0, 0, 27, 7, 1988, false, 0);

      THEN("Sun Distance (km) is 151920130 and Sun Angular Size is 0h 31m "
           "29.93s") {
        std::tuple<double, double, double, double> expected =
            std::make_tuple(151920130, 0, 31, 29.93);

        REQUIRE(std::get<0>(result) == std::get<0>(expected));
        REQUIRE(std::get<1>(result) == std::get<1>(expected));
        REQUIRE(std::get<2>(result) == std::get<2>(expected));
        REQUIRE(std::get<3>(result) == std::get<3>(expected));
      }
    }
  }
}

SCENARIO("Sunrise and Sunset") {
  GIVEN("A PASun object") {
    PASun paSun;

    WHEN("Local date is 3/10/1986 and Geographical Longitude/Latitude is "
         "-71.05d/42.37d") {
      std::tuple<double, double, double, double, double, double,
                 pa_types::RiseSetStatus>
          result =
              paSun.SunriseAndSunset(10, 3, 1986, false, -5, -71.05, 42.37);

      THEN("Local sunrise is 06:05 and local sunset is 17:45 and azimuth of "
           "sunrise/sunset is 94.83d/265.43d") {
        std::tuple<double, double, double, double, double, double,
                   pa_types::RiseSetStatus>
            expected = std::make_tuple(6, 5, 17, 45, 94.83, 265.43,
                                       pa_types::RiseSetStatus::Ok);

        REQUIRE(std::get<0>(result) == std::get<0>(expected));
        REQUIRE(std::get<1>(result) == std::get<1>(expected));
        REQUIRE(std::get<2>(result) == std::get<2>(expected));
        REQUIRE(std::get<3>(result) == std::get<3>(expected));
        REQUIRE(std::get<4>(result) == std::get<4>(expected));
        REQUIRE(std::get<5>(result) == std::get<5>(expected));
        REQUIRE(std::get<6>(result) == std::get<6>(expected));
      }
    }
  }
}