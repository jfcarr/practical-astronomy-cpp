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

SCENARIO("Convert Right Ascension to and from Hour Angle", "[coordinates]") {
  GIVEN("A PACoordinates object") {
    PACoordinates paCoordinates;

    WHEN("Right Ascension is 18 hours 32 minutes 21 seconds") {
      std::tuple<double, double, double> result =
          paCoordinates.right_ascension_to_hour_angle(
              18, 32, 21, 14, 36, 51.67, false, -4, 22, 4, 1980, -64);

      THEN("Hour angle is 9 hours 52 minutes 23.66 seconds") {
        std::tuple<double, double, double> expected =
            std::make_tuple(9, 52, 23.66);

        REQUIRE(std::get<0>(result) == std::get<0>(expected));
        REQUIRE(std::get<1>(result) == std::get<1>(expected));
        REQUIRE(std::get<2>(result) == std::get<2>(expected));
      }
    }

    WHEN("Hour Angle is 9 hours 52 minutes 23.66 seconds") {
      std::tuple<double, double, double> result =
          paCoordinates.hour_angle_to_right_ascension(
              9, 52, 23.66, 14, 36, 51.67, false, -4, 22, 4, 1980, -64);

      THEN("Right Ascension is 18 hours 32 minutes 21 seconds") {
        std::tuple<double, double, double> expected =
            std::make_tuple(18, 32, 21);

        REQUIRE(std::get<0>(result) == std::get<0>(expected));
        REQUIRE(std::get<1>(result) == std::get<1>(expected));
        REQUIRE(std::get<2>(result) == std::get<2>(expected));
      }
    }
  }
}

SCENARIO("Convert Equatorial Coordinates to and from Horizon Coordinates",
         "[coordinates]") {
  GIVEN("A PACoordinates object") {
    PACoordinates paCoordinates;

    WHEN("Equatorial Coordinates are azimuth 5 degrees, 51 minutes, 44 seconds "
         "and altitude 23 degrees, 13 minutes, 10 seconds") {
      std::tuple<double, double, double, double, double, double> result =
          paCoordinates.equatorial_coordinates_to_horizon_coordinates(
              5, 51, 44, 23, 13, 10, 52);
      THEN("Horizon Coordinates are azimuth 283 degrees 16 minutes 15.7 "
           "seconds and altitude 19 degrees 20 minutes 3.64 seconds") {
        std::tuple<double, double, double, double, double, double> expected =
            std::make_tuple(283, 16, 15.7, 19, 20, 3.64);

        REQUIRE(std::get<0>(result) == std::get<0>(expected));
        REQUIRE(std::get<1>(result) == std::get<1>(expected));
        REQUIRE(std::get<2>(result) == std::get<2>(expected));
        REQUIRE(std::get<3>(result) == std::get<3>(expected));
        REQUIRE(std::get<4>(result) == std::get<4>(expected));
        REQUIRE(std::get<5>(result) == std::get<5>(expected));
      }
    }
    WHEN("Horizon coordinates are azimuth 283 degrees 16 minutes 15.7 seconds "
         "and altitude 19 degrees 20 minutes 3.64 seconds") {
      std::tuple<double, double, double, double, double, double> result =
          paCoordinates.horizon_coordinates_to_equatorial_coordinates(
              283, 16, 15.7, 19, 20, 3.64, 52);
      THEN("Equatorial coordinates are azimuth 5 degrees 51 minutes 44 seconds "
           "and altitude 23 degrees 13 minutes 10 seconds") {
        std::tuple<double, double, double, double, double, double> expected =
            std::make_tuple(5, 51, 44, 23, 13, 10);

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

SCENARIO("Calculate Obliquity of the Ecliptic", "[coordinates]") {
  GIVEN("A PACoordinates object") {
    PACoordinates paCoordinates;

    WHEN("Greenwich Date is July 6, 2009") {
      double result =
          round(paCoordinates.mean_obliquity_of_the_ecliptic(6, 7, 2009), 8);

      THEN("Obliquity is 23.43805531") {
        double expected = 23.43805531;

        REQUIRE(result == expected);
      }
    }
  }
}

SCENARIO("Convert Ecliptic Coordinates to and from Equatorial Coordinates",
         "[coordinates]") {
  GIVEN("A PACoordinates object") {
    PACoordinates paCoordinates;

    WHEN("Ecliptic coordinates are Ecliptic Longitude 139d 41m 10s and "
         "Ecliptic Latitude 4d 52m 31s") {
      std::tuple<double, double, double, double, double, double> result =
          paCoordinates.ecliptic_coordinate_to_equatorial_coordinate(
              139, 41, 10, 4, 52, 31, 6, 7, 2009);

      THEN("Equatorial coordinates are Right Ascension 9h 34m 53.4s and "
           "Declination 19d 32m 8.52s") {
        std::tuple<double, double, double, double, double, double> expected =
            std::make_tuple(9, 34, 53.4, 19, 32, 8.52);

        REQUIRE(std::get<0>(result) == std::get<0>(expected));
        REQUIRE(std::get<1>(result) == std::get<1>(expected));
        REQUIRE(std::get<2>(result) == std::get<2>(expected));
        REQUIRE(std::get<3>(result) == std::get<3>(expected));
        REQUIRE(std::get<4>(result) == std::get<4>(expected));
        REQUIRE(std::get<5>(result) == std::get<5>(expected));
      }
    }

    WHEN("Equatorial coordinates are Right Ascension 9h 34m 53.4s and "
         "Declination 19d 32m 8.52s") {
      std::tuple<double, double, double, double, double, double> result =
          paCoordinates.equatorial_coordinate_to_ecliptic_coordinate(
              9, 34, 53.4, 19, 32, 8.52, 6, 7, 2009);

      THEN("Ecliptic coordinates are Ecliptic Longitude 139d 41m 9.97s and "
           "Ecliptic Latitude 4d 52m 30.99s") {
        std::tuple<double, double, double, double, double, double> expected =
            std::make_tuple(139, 41, 9.97, 4, 52, 30.99);

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

SCENARIO("Convert Equatorial Coordinates to and from Galactic Coordinates",
         "[coordinates]") {
  GIVEN("A PACoordinates object") {
    PACoordinates paCoordinates;

    WHEN("Equatorial coordinates are right ascension 10h 21m 0s and "
         "declination 10d 3m 11s") {
      std::tuple<double, double, double, double, double, double> result =
          paCoordinates.equatorial_coordinate_to_galactic_coordinate(10, 21, 0,
                                                                     10, 3, 11);
      THEN("Galactic coordinates are galactic longitude 232d 14m 52.38s and "
           "galactic latitude 51d 7m 20.16s") {
        std::tuple<double, double, double, double, double, double> expected =
            std::make_tuple(232, 14, 52.38, 51, 7, 20.16);

        REQUIRE(std::get<0>(result) == std::get<0>(expected));
        REQUIRE(std::get<1>(result) == std::get<1>(expected));
        REQUIRE(std::get<2>(result) == std::get<2>(expected));
        REQUIRE(std::get<3>(result) == std::get<3>(expected));
        REQUIRE(std::get<4>(result) == std::get<4>(expected));
        REQUIRE(std::get<5>(result) == std::get<5>(expected));
      }
    }

    WHEN("Galactic coordinates are galactic longitude 232d 14m 52.38s and "
         "galactic latitude 51d 7m 20.16s") {
      std::tuple<double, double, double, double, double, double> result =
          paCoordinates.galactic_coordinate_to_equatorial_coordinate(
              232, 14, 52.38, 51, 7, 20.16);
      THEN("Equatorial coordinates are right ascension 10h 21m 0s and "
           "declination 10d 3m 11s") {
        std::tuple<double, double, double, double, double, double> expected =
            std::make_tuple(10, 21, 0, 10, 3, 11);

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

SCENARIO("Calculate angle between two objects", "[coordinates]") {
  GIVEN("A PACoordinates object") {
    PACoordinates paCoordinates;
    WHEN("Object 1 is Right Ascension 5h 13m 31.7 Declination -8d 13m 30s and "
         "Object 2 is Right Ascension 6h 44m 13.4s Declination -16h 41m 11s") {
      std::tuple<double, double, double> result =
          paCoordinates.angle_between_two_objects(
              5, 13, 31.7, -8, 13, 30, 6, 44, 13.4, -16, 41, 11,
              pa_types::angle_measurement_units::hours);
      THEN("Angular distance is 23d 40m 25.86s") {
        std::tuple<double, double, double> expected =
            std::make_tuple(23, 40, 25.86);

        REQUIRE(std::get<0>(result) == std::get<0>(expected));
        REQUIRE(std::get<1>(result) == std::get<1>(expected));
        REQUIRE(std::get<2>(result) == std::get<2>(expected));
      }
    }
  }
}

SCENARIO("Calculate rising and setting times", "[coordinates]") {
  GIVEN("A PACoordinates object") {
    PACoordinates paCoordinates;

    WHEN("Right Ascension is 23h 39m 20s and Declination is 21d 42m 0s and "
         "Greenwich Date is 8/24/2010 and Geographical Long/Lat is 64/30") {
      std::tuple<pa_types::rise_set_status, double, double, double, double,
                 double, double>
          result = paCoordinates.rising_and_setting(23, 39, 20, 21, 42, 0, 24,
                                                    8, 2010, 64, 30, 0.5667);
      THEN("Rise/Set status is OK, and rise time is 14:16 and set time is 4:10 "
           "and azimuth rise/set is 64.36/295.64") {
        std::tuple<pa_types::rise_set_status, double, double, double, double,
                   double, double>
            expected = std::make_tuple(pa_types::rise_set_status::ok, 14, 16, 4,
                                       10, 64.36, 295.64);

        REQUIRE(std::get<0>(result) == std::get<0>(expected));
        REQUIRE(std::get<1>(result) == std::get<1>(expected));
        REQUIRE(std::get<2>(result) == std::get<2>(expected));
        REQUIRE(std::get<3>(result) == std::get<3>(expected));
        REQUIRE(std::get<4>(result) == std::get<4>(expected));
        REQUIRE(std::get<5>(result) == std::get<5>(expected));
        REQUIRE(std::get<6>(result) == std::get<6>(expected));
      }
    }
  }
}

SCENARIO("Correct coordinates for precession", "[coordinates]") {
  GIVEN("A PACoordinates object") {
    PACoordinates paCoordinates;

    WHEN("Right Ascension is 9h 10m 43s, Declination is 14d 23m 25s, Epoch 1 "
         "date is 1/.923/1950, and Epoch 2 date is 6/1/1979") {
      std::tuple<double, double, double, double, double, double> result =
          paCoordinates.correct_for_precession(9, 10, 43, 14, 23, 25, 0.923, 1,
                                               1950, 1, 6, 1979);

      THEN("Corrected Right Ascension is 9h 12m 20.18s and Corrected "
           "Declination is 14d 16m 9.12s") {
        std::tuple<double, double, double, double, double, double> expected =
            std::make_tuple(9, 12, 20.18, 14, 16, 9.12);

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

SCENARIO("Nutation in Ecliptic Longitude and Obliquity", "[coordinates]") {
  GIVEN("A PACoordinates object") {
    PACoordinates paCoordinates;

    WHEN("Greenwich date is 9/1/1988") {
      std::tuple<double, double> result =
          paCoordinates.nutation_in_ecliptic_longitude_and_obliquity(1, 9,
                                                                     1988);

      THEN("Ecliptic Longitude is .001525808 and Obliquity is .0025671") {
        std::tuple<double, double> expected =
            std::make_tuple(.001525808, .0025671);

        REQUIRE(round(std::get<0>(result), 9) == std::get<0>(expected));
        REQUIRE(round(std::get<1>(result), 7) == std::get<1>(expected));
      }
    }
  }
}

SCENARIO("Correct ecliptic coordinates for the effects of aberration.") {
  GIVEN("A PACoordinates object") {
    PACoordinates paCoordinates;

    WHEN("UT is 0:0:0 and Greenwich Date is 9/8/1988 and Ecliptic Longitude is "
         "352d 37m 10.1s and Ecliptic Latitude is -1d 32m 56.4s") {
      std::tuple<double, double, double, double, double, double> result =
          paCoordinates.correct_for_aberration(0, 0, 0, 8, 9, 1988, 352, 37,
                                               10.1, -1, 32, 56.4);

      THEN("Apparent Ecliptic Longitude is 352d 37m 30.45s and Apparent "
           "Ecliptic Latitude is -1d 32m 56.33s") {
        std::tuple<double, double, double, double, double, double> expected =
            std::make_tuple(352, 37, 30.45, -1, 32, 56.33);

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

SCENARIO("Correct for atmospheric refraction") {
  GIVEN("A PACoordinates object") {
    PACoordinates paCoordinates;

    WHEN("True Right Ascension is 23h 14m 0s and True Declination is 40d 10m "
         "0s and Coordinate Type is actual and Geographical Longitude is 0.17d "
         "and Geographical Latitude is 51.2036110d and Daylight Savings offset "
         "is 0h and Timezone offset is 0h and Local Civil Date is 3/23/1987 "
         "and Local Civil Time is 01:01:24 and Atmospheric Pressure "
         "Millibar/Temperature Celsius is 1012/21.7") {
      std::tuple<double, double, double, double, double, double> result =
          paCoordinates.atmospheric_refraction(
              23, 14, 0, 40, 10, 0, pa_types::coordinate_type::actual, 0.17,
              51.2036110, 0, 0, 23, 3, 1987, 1, 1, 24, 1012, 21.7);

      THEN("Corrected Right Ascension is 23h 13m 44.74s and Corrected "
           "Declination is 40d 19m 45.76s") {
        std::tuple<double, double, double, double, double, double> expected =
            std::make_tuple(23, 13, 44.74, 40, 19, 45.76);

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

SCENARIO("Corrections for geocentric parallax") {
  GIVEN("A PACoordinates object") {
    PACoordinates paCoordinates;

    WHEN("Right Ascension is 22h 35m 19s and Declination is -7d 41m 13s and "
         "Geographical Longitude/Latitude is -100/50 and Local Civil Date is "
         "2/26/1979 and Local Civil Time is 10:45:00") {
      std::tuple<double, double, double, double, double, double> result =
          paCoordinates.corrections_for_geocentric_parallax(
              22, 35, 19, -7, 41, 13, pa_types::coordinate_type::actual,
              1.019167, -100, 50, 60, 0, -6, 26, 2, 1979, 10, 45, 0);

      THEN("Corrected Right Ascension is 22h 36m 43.22s and Corrected "
           "Declination is -8d 32m 17.4s") {
        std::tuple<double, double, double, double, double, double> expected =
            std::make_tuple(22, 36, 43.22, -8, 32, 17.4);

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

SCENARIO("Calculate heliographic coordinates") {
  GIVEN("A PACoordinates object") {
    PACoordinates paCoordinates;

    WHEN("Position angle is 220d and Displacement is 10.5 arcmin and Greenwich "
         "Date is 5/1/1988") {
      std::tuple<double, double> result =
          paCoordinates.heliographic_coordinates(220, 10.5, 1, 5, 1988);

      THEN("Heliographic Longitude/Latitude is 142.59d/-19.94d") {
        std::tuple<double, double> expected = std::make_tuple(142.59, -19.94);

        REQUIRE(std::get<0>(result) == std::get<0>(expected));
        REQUIRE(std::get<1>(result) == std::get<1>(expected));
      }
    }
  }
}

SCENARIO("Calculate carrington rotation number") {
  GIVEN("A PACoordinates object") {
    PACoordinates paCoordinates;

    WHEN("Greenwich Date is 1/27/1975") {
      int result = paCoordinates.carrington_rotation_number(27, 1, 1975);

      THEN("Carrington Rotation Number is 1624") {
        int expected = 1624;

        REQUIRE(result == expected);
      }
    }
  }
}

SCENARIO("Selenographic Coordinates (1)") {
  GIVEN("A PACoordinates object") {
    PACoordinates paCoordinates;

    WHEN("Greenwich Date is 5/1/1988") {
      std::tuple<double, double, double> result =
          paCoordinates.selenographic_coordinates_1(1, 5, 1988);

      THEN("Sub-Earth Longitude/Latitude is -4.88d/4.04d and Position Angle of "
           "Pole is 19.78d") {
        std::tuple<double, double, double> expected =
            std::make_tuple(-4.88, 4.04, 19.78);

        REQUIRE(std::get<0>(result) == std::get<0>(expected));
        REQUIRE(std::get<1>(result) == std::get<1>(expected));
        REQUIRE(std::get<2>(result) == std::get<2>(expected));
      }
    }
  }
}

SCENARIO("Selenographic Coordinates (2)") {
  GIVEN("A PACoordinates object") {
    PACoordinates paCoordinates;

    WHEN("Greenwich Date is 5/1/1988") {
      std::tuple<double, double, double> result =
          paCoordinates.selenographic_coordinates_2(1, 5, 1988);

      THEN("Sub-Solar Longitude, Colongitude, and Latitude is 6.81d, 83.19d, "
           "and 1.19d, respectively") {
        std::tuple<double, double, double> expected =
            std::make_tuple(6.81, 83.19, 1.19);

        REQUIRE(std::get<0>(result) == std::get<0>(expected));
        REQUIRE(std::get<1>(result) == std::get<1>(expected));
        REQUIRE(std::get<2>(result) == std::get<2>(expected));
      }
    }
  }
}