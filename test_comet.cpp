#include "catch2/catch.hpp"
#include "lib/pa_comet.h"
#include "lib/pa_data.h"
#include "lib/pa_models.h"
#include "lib/pa_types.h"
#include "lib/pa_util.h"
#include <tuple>

SCENARIO("Position of Elliptical Comet") {
  GIVEN("A PAComet object") {
    PAComet paComet;

    WHEN("Civil Time is 0:0:0 and Local Date is 1/1/1984 and comet is Halley") {
      CCometPosition result = paComet.PositionOfEllipticalComet(
          0, 0, 0, false, 0, 1, 1, 1984, "Halley");

      THEN("Right Ascension is 6h 29m 0s and Declination is 10d 13m 0s and "
           "Distance From Earth is 8.13") {
        CCometPosition expected = CCometPosition(6, 29, 0, 10, 13, 0, 8.13);

        REQUIRE(result.decDeg == expected.decDeg);
        REQUIRE(result.decMin == expected.decMin);
        REQUIRE(result.decSec == expected.decSec);
        REQUIRE(result.distEarth == expected.distEarth);
        REQUIRE(result.raHour == expected.raHour);
        REQUIRE(result.raMin == expected.raMin);
        REQUIRE(result.raSec == expected.raSec);
      }
    }
  }
}