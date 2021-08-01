#include "catch2/catch.hpp"
#include "lib/pa_coordinates.h"
#include "lib/pa_types.h"
#include "lib/pa_util.h"
#include <iostream>

using namespace pa_types;
using namespace pa_util;

SCENARIO("Convert angle to and from decimal degrees", "[coordinates") {
  GIVEN("A PACoordinates object") {
    PACoordinates paCoordinates;

    WHEN("The angle is 182d 31m 27s") {
      double result =
          round(paCoordinates.angle_to_decimal_degrees(182, 31, 27), 6);

      THEN("The result is 182.524167") {
        double expected = 182.524167;

        REQUIRE(result == expected);
      }
    }

    WHEN("Decimal degrees are 182.524167") {
      std::tuple<double, double, double> result =
          paCoordinates.decimal_degrees_to_angle(182.524167);
      THEN("The result is 182d 31m 27s") {
        std::tuple<double, double, double> expected =
            std::make_tuple(182, 31, 27);

        REQUIRE(std::get<0>(result) == std::get<0>(expected));
        REQUIRE(std::get<1>(result) == std::get<1>(expected));
        REQUIRE(std::get<2>(result) == std::get<2>(expected));
      }
    }
  }
}

SCENARIO("Convert Right Ascension to and from Hour Angle", "[coordinates]") {
  GIVEN("A PACoordinates object") {
    PACoordinates paCoordinates;

    WHEN("Right Ascension is 18 hours 32 minutes 21 seconds") {
      std::tuple<double, double, double> result =
          paCoordinates.right_ascension_to_hour_angle(
              18, 32, 21, 14, 36, 51.67, false, -4, 22, 4, 1980, -64);

      THEN("Hour angle is 9 hours 52 minutes 23.66 seconds") {
        std::tuple<double, double, double> expected =
            std::make_tuple(9, 52, 23.66);

        REQUIRE(std::get<0>(result) == std::get<0>(expected));
        REQUIRE(std::get<1>(result) == std::get<1>(expected));
        REQUIRE(std::get<2>(result) == std::get<2>(expected));
      }
    }

    WHEN("Hour Angle is 9 hours 52 minutes 23.66 seconds") {
      std::tuple<double, double, double> result =
          paCoordinates.hour_angle_to_right_ascension(
              9, 52, 23.66, 14, 36, 51.67, false, -4, 22, 4, 1980, -64);

      THEN("Right Ascension is 18 hours 32 minutes 21 seconds") {
        std::tuple<double, double, double> expected =
            std::make_tuple(18, 32, 21);

        REQUIRE(std::get<0>(result) == std::get<0>(expected));
        REQUIRE(std::get<1>(result) == std::get<1>(expected));
        REQUIRE(std::get<2>(result) == std::get<2>(expected));
      }
    }
  }
}

SCENARIO("Convert Equatorial Coordinates to and from Horizon Coordinates") {
  GIVEN("A PACoordinates object") {
    PACoordinates paCoordinates;

    WHEN("Equatorial Coordinates are azimuth 5 degrees, 51 minutes, 44 seconds "
         "and altitude 23 degrees, 13 minutes, 10 seconds") {
      std::tuple<double, double, double, double, double, double> result =
          paCoordinates.equatorial_coordinates_to_horizon_coordinates(
              5, 51, 44, 23, 13, 10, 52);
      THEN("Horizon Coordinates are azimuth 283 degrees 16 minutes 15.7 "
           "seconds and altitude 19 degrees 20 minutes 3.64 seconds") {
        std::tuple<double, double, double, double, double, double> expected =
            std::make_tuple(283, 16, 15.7, 19, 20, 3.64);

        REQUIRE(std::get<0>(result) == std::get<0>(expected));
        REQUIRE(std::get<1>(result) == std::get<1>(expected));
        REQUIRE(std::get<2>(result) == std::get<2>(expected));
        REQUIRE(std::get<3>(result) == std::get<3>(expected));
        REQUIRE(std::get<4>(result) == std::get<4>(expected));
        REQUIRE(std::get<5>(result) == std::get<5>(expected));
      }
    }
    WHEN("Horizon coordinates are azimuth 283 degrees 16 minutes 15.7 seconds "
         "and altitude 19 degrees 20 minutes 3.64 seconds") {
      std::tuple<double, double, double, double, double, double> result =
          paCoordinates.horizon_coordinates_to_equatorial_coordinates(
              283, 16, 15.7, 19, 20, 3.64, 52);
      THEN("Equatorial coordinates are azimuth 5 degrees 51 minutes 44 seconds "
           "and altitude 23 degrees 13 minutes 10 seconds") {
        std::tuple<double, double, double, double, double, double> expected =
            std::make_tuple(5, 51, 44, 23, 13, 10);

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

SCENARIO("Calculate Obliquity of the Ecliptic") {
  GIVEN("A PACoordinates object") {
    PACoordinates paCoordinates;

    WHEN("Greenwich Date is July 6, 2009") {
      double result =
          round(paCoordinates.mean_obliquity_of_the_ecliptic(6, 7, 2009), 8);

      THEN("Obliquity is 23.43805531") {
        double expected = 23.43805531;

        REQUIRE(result == expected);
      }
    }
  }
}