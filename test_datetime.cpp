#include "catch2/catch.hpp"
#include "lib/pa_datetime.h"
#include "lib/pa_types.h"
#include "lib/pa_util.h"
#include <iostream>

using namespace pa_types;
using namespace pa_util;

SCENARIO("Calculate date of Easter", "[date_time") {
  GIVEN("A PADateTime object") {
    PADateTime paDateTime;

    WHEN("The year is 2003") {
      std::tuple<int, int, int> result = paDateTime.get_date_of_easter(2003);
      std::tuple<int, int, int> expected = std::make_tuple(4, 20, 2003);

      THEN("The result is 4/20/2003") {
        REQUIRE(std::get<0>(result) == std::get<0>(expected));
        REQUIRE(std::get<1>(result) == std::get<1>(expected));
        REQUIRE(std::get<2>(result) == std::get<2>(expected));
      }
    }

    WHEN("The year is 2019") {
      std::tuple<int, int, int> result = paDateTime.get_date_of_easter(2019);
      std::tuple<int, int, int> expected = std::make_tuple(4, 21, 2019);

      THEN("The result is 4/21/2019") {
        REQUIRE(std::get<0>(result) == std::get<0>(expected));
        REQUIRE(std::get<1>(result) == std::get<1>(expected));
        REQUIRE(std::get<2>(result) == std::get<2>(expected));
      }
    }

    WHEN("The year is 2020") {
      std::tuple<int, int, int> result = paDateTime.get_date_of_easter(2020);
      std::tuple<int, int, int> expected = std::make_tuple(4, 12, 2020);

      THEN("The result is 4/12/2020") {
        REQUIRE(std::get<0>(result) == std::get<0>(expected));
        REQUIRE(std::get<1>(result) == std::get<1>(expected));
        REQUIRE(std::get<2>(result) == std::get<2>(expected));
      }
    }
  }
}

SCENARIO("Calculate civil day number", "[date_time]") {
  GIVEN("A PADateTime object") {
    PADateTime paDateTime;

    WHEN("The date is 1/1/2000") {

      int result = paDateTime.civil_date_to_day_number(1, 1, 2000);

      THEN("The result is 1") { REQUIRE(result == 1); }
    }

    WHEN("The date is 3/1/2000") {

      int result = paDateTime.civil_date_to_day_number(3, 1, 2000);

      THEN("The result is 61") { REQUIRE(result == 61); }
    }

    WHEN("The date is 6/1/2003") {

      int result = paDateTime.civil_date_to_day_number(6, 1, 2003);

      THEN("The result is 152") { REQUIRE(result == 152); }
    }

    WHEN("The date is 11/27/2009") {

      int result = paDateTime.civil_date_to_day_number(11, 27, 2009);

      THEN("The result is 331") { REQUIRE(result == 331); }
    }
  }
}

SCENARIO("Convert civil time to and from decimal hours", "[date_time]") {
  GIVEN("A PADateTime object") {
    PADateTime paDateTime;

    WHEN("Civil time is 18:31:27") {
      double result = paDateTime.civil_time_to_decimal_hours(18, 31, 27);

      THEN("Decimal hours is 18.52416667") {
        REQUIRE(round(result, 8) == 18.52416667);
      }
    }

    WHEN("Decimal hours is 18.52416667") {
      std::tuple<double, double, double> result =
          paDateTime.decimal_hours_to_civil_time(18.52416667);
      std::tuple<double, double, double> expected = std::make_tuple(18, 31, 27);

      THEN("Civil time is 18:31:27") {
        REQUIRE(std::get<0>(result) == std::get<0>(expected));
        REQUIRE(std::get<1>(result) == std::get<1>(expected));
        REQUIRE(round(std::get<2>(result), 0) == std::get<2>(expected));
      }
    }
  }
}

SCENARIO("Convert civil time to and from universal time", "[date_time]") {
  GIVEN("A PADateTime object") {
    PADateTime paDateTime;

    WHEN("Civil time is 03:37:00") {
      std::tuple<int, int, int, int, int, int> result =
          paDateTime.local_civil_time_to_universal_time(3, 37, 0, true, 4, 1, 7,
                                                        2013);
      std::tuple<int, int, int, int, int, int> expected =
          std::make_tuple(22, 37, 0, 30, 6, 2013);

      THEN("Universal time is 22:37:00") {
        REQUIRE(std::get<0>(result) == std::get<0>(expected));
        REQUIRE(std::get<1>(result) == std::get<1>(expected));
        REQUIRE(std::get<2>(result) == std::get<2>(expected));
        REQUIRE(std::get<3>(result) == std::get<3>(expected));
        REQUIRE(std::get<4>(result) == std::get<4>(expected));
        REQUIRE(std::get<5>(result) == std::get<5>(expected));
      }
    }

    WHEN("Universal time is 22:37:00") {
      std::tuple<int, int, int, int, int, int> result =
          paDateTime.universal_time_to_local_civil_time(22, 37, 0, true, 4, 30,
                                                        6, 2013);
      std::tuple<int, int, int, int, int, int> expected =
          std::make_tuple(3, 37, 0, 1, 7, 2013);

      THEN("Civil time is 03:37:00") {
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

SCENARIO("Convert universal time to and from Greenwich sidereal time",
         "[date_time]") {
  GIVEN("A PADateTime object") {
    PADateTime paDateTime;

    WHEN("Universal time is 14:36:51.67") {
      std::tuple<int, int, double> result =
          paDateTime.universal_time_to_greenwich_sidereal_time(14, 36, 51.67,
                                                               22, 4, 1980);

      THEN("Greenwich sidereal time is 4:40:5.23") {
        std::tuple<int, int, double> expected = std::make_tuple(4, 40, 5.23);

        REQUIRE(std::get<0>(result) == std::get<0>(expected));
        REQUIRE(std::get<1>(result) == std::get<1>(expected));
        REQUIRE(std::get<2>(result) == std::get<2>(expected));
      }
    }

    WHEN("Greenwich sidereal time is 4:40:5.23") {
      std::tuple<int, int, double, warning_flags> result =
          paDateTime.greenwich_sidereal_time_to_universal_time(4, 40, 5.23, 22,
                                                               4, 1980);
      THEN("Universal time is 14:36:51.67") {
        std::tuple<int, int, double, warning_flags> expected =
            std::make_tuple(14, 36, 51.67, warning_flags::ok);

        REQUIRE(std::get<0>(result) == std::get<0>(expected));
        REQUIRE(std::get<1>(result) == std::get<1>(expected));
        REQUIRE(std::get<2>(result) == std::get<2>(expected));
        REQUIRE(std::get<3>(result) == std::get<3>(expected));
      }
    }
  }
}

SCENARIO("Convert Greenwich Sidereal Time to and from Local Sidereal Time",
         "[date_time]") {
  GIVEN("A PADateTime object") {
    PADateTime paDateTime;

    WHEN("Greenwich Sidereal Time is 04:40:05.23, with Geographical Longitude "
         "of -64") {
      std::tuple<int, int, double> result =
          paDateTime.greenwich_sidereal_time_to_local_sidereal_time(4, 40, 5.23,
                                                                    -64);

      THEN("Local Sidereal Time is 00:24:5.23") {
        std::tuple<int, int, double> expected = std::make_tuple(0, 24, 5.23);

        REQUIRE(std::get<0>(result) == std::get<0>(expected));
        REQUIRE(std::get<1>(result) == std::get<1>(expected));
        REQUIRE(std::get<2>(result) == std::get<2>(expected));
      }
    }

    WHEN("Local Sidereal Time is 00:24:05.23, with Geographical Longitude "
         "of -64") {
      std::tuple<int, int, double> result =
          paDateTime.local_sidereal_time_to_greenwich_sidereal_time(0, 24, 5.23,
                                                                    -64);
      THEN("Greenwich Sidereal Time is 04:40:5.23") {
        std::tuple<int, int, double> expected = std::make_tuple(4, 40, 5.23);

        REQUIRE(std::get<0>(result) == std::get<0>(expected));
        REQUIRE(std::get<1>(result) == std::get<1>(expected));
        REQUIRE(std::get<2>(result) == std::get<2>(expected));
      }
    }
  }
}