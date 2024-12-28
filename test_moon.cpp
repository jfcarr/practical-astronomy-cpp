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

SCENARIO("Moon Phase and Bright Limb") {
  GIVEN("A PAMoon object") {
    PAMoon paMoon;

    WHEN("Civil Time is 0:0:0 and Local Date is 9/1/2003 and Accuracy Level is "
         "Approximate") {
      CMoonPhase result = paMoon.MoonPhase(0, 0, 0, false, 0, 1, 9, 2003,
                                           EAccuracyLevel::Approximate);

      THEN("Phase is 0.22 and Bright Limb is -71.58d") {
        CMoonPhase expected = CMoonPhase(0.22, -71.58);

        REQUIRE(result.brightLimbDeg == expected.brightLimbDeg);
        REQUIRE(result.phase == expected.phase);
      }
    }
  }
}

SCENARIO("Times of New Moon and Full Moon") {
  GIVEN("A PAMoon object") {
    PAMoon paMoon;

    WHEN("Local Date is 9/1/2003") {
      CMoonNewFull result =
          paMoon.TimesOfNewMoonAndFullMoon(false, 0, 1, 9, 2003);

      THEN("New Moon Local Time is 17:27 and New Moon Local Date is 8/27/2003 "
           "and Full Moon Local Time is 16:36 and Full Moon Local Date is "
           "9/10/2003") {
        CMoonNewFull expected =
            CMoonNewFull(17, 27, 27, 8, 2003, 16, 36, 10, 9, 2003);

        REQUIRE(result.fmLocalDateDay == expected.fmLocalDateDay);
        REQUIRE(result.fmLocalDateMonth == expected.fmLocalDateMonth);
        REQUIRE(result.fmLocalDateYear == expected.fmLocalDateYear);
        REQUIRE(result.fmLocalTimeHour == expected.fmLocalTimeHour);
        REQUIRE(result.fmLocalTimeMin == expected.fmLocalTimeMin);
        REQUIRE(result.nmLocalDateDay == expected.nmLocalDateDay);
        REQUIRE(result.nmLocalDateMonth == expected.nmLocalDateMonth);
        REQUIRE(result.nmLocalDateYear == expected.nmLocalDateYear);
        REQUIRE(result.nmLocalTimeHour == expected.nmLocalTimeHour);
        REQUIRE(result.nmLocalTimeMin == expected.nmLocalTimeMin);
      }
    }
  }
}

SCENARIO(
    "Calculate Moon's distance, angular diameter, and horizontal parallax") {
  GIVEN("A PAMoon object") {
    PAMoon paMoon;

    WHEN("Local Civil Time is 0:0:0 and Local Date is 9/1/2003") {
      CMoonDistDiameterHP result =
          paMoon.MoonDistAngDiamHorParallax(0, 0, 0, false, 0, 1, 9, 2003);

      THEN("Distance is 367964 and Angular Diameter is 0d 32m and Horizontal "
           "Parallax is 0d 59m 35.49s") {
        CMoonDistDiameterHP expected =
            CMoonDistDiameterHP(367964, 0, 32, 0, 59, 35.49);

        REQUIRE(result.angDiameterDeg == expected.angDiameterDeg);
        REQUIRE(result.angDiameterMin == expected.angDiameterMin);
        REQUIRE(result.earthMoonDist == expected.earthMoonDist);
        REQUIRE(result.horParallaxDeg == expected.horParallaxDeg);
        REQUIRE(result.horParallaxMin == expected.horParallaxMin);
        REQUIRE(result.horParallaxSec == expected.horParallaxSec);
      }
    }
  }
}