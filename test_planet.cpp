#include "catch2/catch.hpp"
#include "lib/pa_data.h"
#include "lib/pa_planet.h"
#include "lib/pa_types.h"
#include "lib/pa_util.h"
#include <tuple>

SCENARIO("Approximate Position of Planet") {
  GIVEN("A PAPlanet object") {
    PAPlanet paPlanet;

    WHEN("Local Civil Time is 00:00:00 and Local Date is 11/22/2003 and planet "
         "is Jupiter") {
      std::tuple<double, double, double, double, double, double> result =
          paPlanet.ApproximatePositionOfPlanet(0, 0, 0, false, 0, 22, 11, 2003,
                                               "Jupiter");

      THEN("Right Ascension is 11h 11m 13.8s and Declination is 6d 21m 25.1s") {
        std::tuple<double, double, double, double, double, double> expected =
            std::make_tuple(11, 11, 13.8, 6, 21, 25.1);

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