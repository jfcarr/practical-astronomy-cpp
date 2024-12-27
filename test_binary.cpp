#include "catch2/catch.hpp"
#include "lib/pa_binary.h"
#include "lib/pa_data.h"
#include "lib/pa_models.h"
#include "lib/pa_types.h"
#include "lib/pa_util.h"
#include <tuple>

SCENARIO("Binary Star Orbital Data") {
  GIVEN("A PABinary object") {
    PABinary paBinary;

    WHEN("Greenwich Date is 1/1/1980 and Binary Star is eta-Cor") {
      CBinaryStarOrbitalData result =
          paBinary.binaryStarOrbit(1, 1, 1980, "eta-Cor");

      THEN("Position Angle is 318.5 degrees and Separation is 0.41 arcsecs") {
        CBinaryStarOrbitalData expected = CBinaryStarOrbitalData(318.5, 0.41);

        REQUIRE(result.positionAngleDeg == expected.positionAngleDeg);
        REQUIRE(result.separationArcsec == expected.separationArcsec);
      }
    }
  }
}