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