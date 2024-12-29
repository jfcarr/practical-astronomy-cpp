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

SCENARIO("Lunar Eclipse Circumstances") {
  GIVEN("A PAEclipses object") {
    PAEclipses paEclipses;

    WHEN("Local Date is 4/1/2015") {
      CLunarEclipseCircumstances result =
          paEclipses.LunarEclipseCircumstances(1, 4, 2015, false, 10);

      THEN("Certain Date is 4/4/2015 and Penumbral Phase Start is 9:00 and "
           "Umbral Phase Start is 10:16 and Total Phase Start is 11:55 and Mid "
           "Eclipse is 12:01 and Total Phase End is 12:07 and Umbral Phase End "
           "is 13:46 and Penumbral Phase End is 15:01 and Magnitude is 1.01") {
        CLunarEclipseCircumstances expected =
            CLunarEclipseCircumstances(4, 4, 2015, 9, 0, 10, 16, 11, 55, 12, 1,
                                       12, 7, 13, 46, 15, 1, 1.01);

        REQUIRE(result.certainDateDay == expected.certainDateDay);
        REQUIRE(result.certainDateMonth == expected.certainDateMonth);
        REQUIRE(result.certainDateYear == expected.certainDateYear);
        REQUIRE(result.eclipseMagnitude == expected.eclipseMagnitude);
        REQUIRE(result.utEndPenPhaseHour == expected.utEndPenPhaseHour);
        REQUIRE(result.utEndPenPhaseMinutes == expected.utEndPenPhaseMinutes);
        REQUIRE(result.utEndTotalPhaseHour == expected.utEndTotalPhaseHour);
        REQUIRE(result.utEndTotalPhaseMinutes ==
                expected.utEndTotalPhaseMinutes);
        REQUIRE(result.utEndUmbralPhaseHour == expected.utEndUmbralPhaseHour);
        REQUIRE(result.utEndUmbralPhaseMinutes ==
                expected.utEndUmbralPhaseMinutes);
        REQUIRE(result.utMidEclipseHour == expected.utMidEclipseHour);
        REQUIRE(result.utMidEclipseMinutes == expected.utMidEclipseMinutes);
        REQUIRE(result.utStartPenPhaseHour == expected.utStartPenPhaseHour);
        REQUIRE(result.utStartPenPhaseMinutes ==
                expected.utStartPenPhaseMinutes);
        REQUIRE(result.utStartTotalPhaseHour == expected.utStartTotalPhaseHour);
        REQUIRE(result.utStartTotalPhaseMinutes ==
                expected.utStartTotalPhaseMinutes);
        REQUIRE(result.utStartUmbralPhaseHour ==
                expected.utStartUmbralPhaseHour);
        REQUIRE(result.utStartUmbralPhaseMinutes ==
                expected.utStartUmbralPhaseMinutes);
      }
    }
  }
}

SCENARIO("Solar Eclipse Occurrence") {
  GIVEN("A PAEclipses object") {
    PAEclipses paEclipses;

    WHEN("Local Date is 4/1/2015") {
      CSolarEclipseOccurrence result =
          paEclipses.SolarEclipseOccurrence(1, 4, 2015, false, 10);

      THEN("Status is Certain and Event Date is 3/20/2015") {
        CSolarEclipseOccurrence expected =
            CSolarEclipseOccurrence(ESolarEclipseStatus::Certain, 20, 3, 2015);

        REQUIRE(result.eventDateDay == expected.eventDateDay);
        REQUIRE(result.eventDateMonth == expected.eventDateMonth);
        REQUIRE(result.eventDateYear == expected.eventDateYear);
        REQUIRE(result.status == expected.status);
      }
    }
  }
}
