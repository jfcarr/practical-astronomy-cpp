#include "catch2/catch.hpp"
#include "lib/pa_data.h"
#include "lib/pa_eclipses.h"
#include "lib/pa_models.h"
#include "lib/pa_types.h"
#include "lib/pa_util.h"
#include <tuple>

SCENARIO("Lunar Eclipse Occurrence") {
  GIVEN("A PAEclipses object") {
    PAEclipses paEclipses;

    WHEN("Local Date is 4/1/2015") {
      CLunarEclipseOccurrence result =
          paEclipses.LunarEclipseOccurrence(1, 4, 2015, false, 10);

      THEN("Status is Certain and Event Date is 4/4/2015") {
        CLunarEclipseOccurrence expected =
            CLunarEclipseOccurrence(ELunarEclipseStatus::Certain, 4, 4, 2015);

        REQUIRE(result.eventDateDay == expected.eventDateDay);
        REQUIRE(result.eventDateMonth == expected.eventDateMonth);
        REQUIRE(result.eventDateYear == expected.eventDateYear);
        REQUIRE(result.status == expected.status);
      }
    }
  }
}