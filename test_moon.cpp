#include "catch2/catch.hpp"
#include "lib/pa_data.h"
#include "lib/pa_models.h"
#include "lib/pa_moon.h"
#include "lib/pa_types.h"
#include "lib/pa_util.h"
#include <tuple>

SCENARIO("Approximate Position of Moon") {
  GIVEN("A PAMoon object") {
    PAMoon paMoon;

    WHEN("Civil Time is 0:0:0 and Local Date is 9/1/2003") {
      CMoonApproximatePosition result =
          paMoon.ApproximatePositionOfMoon(0, 0, 0, false, 0, 1, 9, 2003);

      THEN("Right Ascension is 14h 12m 42.31s and Declination is -11d 31m "
           "38.27s") {
        CMoonApproximatePosition expected =
            CMoonApproximatePosition(14, 12, 42.31, -11, 31, 38.27);

        REQUIRE(result.decDeg == expected.decDeg);
        REQUIRE(result.decMin == expected.decMin);
        REQUIRE(result.decSec == expected.decSec);
        REQUIRE(result.raHour == expected.raHour);
        REQUIRE(result.raMin == expected.raMin);
        REQUIRE(result.raSec == expected.raSec);
      }
    }
  }
}

SCENARIO("Precise Position of Moon") {
  GIVEN("A PAMoon object") {
    PAMoon paMoon;

    WHEN("Civil Time is 0:0:0 and Local Date is 9/1/2003") {
      CMoonPrecisePosition result =
          paMoon.PrecisePositionOfMoon(0, 0, 0, false, 0, 1, 9, 2003);

      THEN("Right Ascension is 14h 12m 10.21s and Declination is -11d 34m "
           "57.83s and Earth-Moon Distance is 367964km and Horizontal Parallax "
           "is 0.993191d") {
        CMoonPrecisePosition expected = CMoonPrecisePosition(
            14, 12, 10.21, -11, 34, 57.83, 367964, 0.993191);

        REQUIRE(result.decDeg == expected.decDeg);
        REQUIRE(result.decMin == expected.decMin);
        REQUIRE(result.decSec == expected.decSec);
        REQUIRE(result.earthMoonDistKM == expected.earthMoonDistKM);
        REQUIRE(result.horParallaxDeg == expected.horParallaxDeg);
        REQUIRE(result.raHour == expected.raHour);
        REQUIRE(result.raMin == expected.raMin);
        REQUIRE(result.raSec == expected.raSec);
      }
    }
  }
}