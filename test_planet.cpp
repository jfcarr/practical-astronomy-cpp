#include "catch2/catch.hpp"
#include "lib/pa_data.h"
#include "lib/pa_models.h"
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

SCENARIO("Precise Position of Planet") {
  GIVEN("A PAPlanet object") {
    PAPlanet paPlanet;

    WHEN("Local Civil Time is 00:00:00 and Local Date is 11/22/2003 and planet "
         "is Jupiter") {
      pa_models::CPrecisePositionOfPlanet result =
          paPlanet.PrecisePositionOfPlanet(0, 0, 0, false, 0, 22, 11, 2003,
                                           "Jupiter");
      THEN("Right Ascension is 11h 10m 30.99s and Declination is 6h 25m "
           "49.46s") {
        pa_models::CPrecisePositionOfPlanet expected =
            pa_models::CPrecisePositionOfPlanet(11, 10, 30.99, 6, 25, 49.46);

        REQUIRE(result.PlanetRAHour == expected.PlanetRAHour);
        REQUIRE(result.PlanetRAMin == expected.PlanetRAMin);
        REQUIRE(result.PlanetRASec == expected.PlanetRASec);
        REQUIRE(result.PlanetDecDeg == expected.PlanetDecDeg);
        REQUIRE(result.PlanetDecMin == expected.PlanetDecMin);
        REQUIRE(result.PlanetDecSec == expected.PlanetDecSec);
      }
    }
  }
}

SCENARIO("Visual Aspects of a Planet") {
  GIVEN("A PAPlanet object") {
    PAPlanet paPlanet;

    WHEN("Local Civil Time is 00:00:00 and Local Date is 11/22/2003 and planet "
         "is Jupiter") {
      CPlanetVisualAspects result = paPlanet.VisualAspectsOfAPlanet(
          0, 0, 0, false, 0, 22, 11, 2003, "Jupiter");
      THEN("Distance is 5.59829 AU and Angular Diameter is 35.1 arcsecs and "
           "Phase is 0.99 and Light Time is 00:46:33.32 and Position Angle of "
           "the Bright Limb is 113.2 and Approximate Magnitude is -2.0") {
        CPlanetVisualAspects expected = CPlanetVisualAspects(
            5.59829, 35.1, 0.99, 0, 46, 33.32, 113.2, -2.0);

        REQUIRE(result.distanceAU == expected.distanceAU);
        REQUIRE(result.angDiaArcsec == expected.angDiaArcsec);
        REQUIRE(result.phase == expected.phase);
        REQUIRE(result.lightTimeHour == expected.lightTimeHour);
        REQUIRE(result.lightTimeMinutes == expected.lightTimeMinutes);
        REQUIRE(result.lightTimeSeconds == expected.lightTimeSeconds);
        REQUIRE(result.lightTimeSeconds == expected.lightTimeSeconds);
        REQUIRE(result.posAngleBrightLimbDeg == expected.posAngleBrightLimbDeg);
        REQUIRE(result.approximateMagnitude == expected.approximateMagnitude);
      }
    }
  }
}