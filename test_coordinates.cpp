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