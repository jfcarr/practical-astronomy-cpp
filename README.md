# practical-astronomy-cpp

Algorithms from "[Practical Astronomy with your Calculator or Spreadsheet](https://www.amazon.com/Practical-Astronomy-your-Calculator-Spreadsheet/dp/1108436072)" by Peter Duffett-Smith, implemented in C++.

If you're interested in this topic, please buy the book! It provides far more detail and context.

## Library Functions - Status

### Date/Time

- [x] Calculate -> Date of Easter
- [x] Convert -> Civil Date to Day Number
- [x] Convert -> Civil Time <-> Decimal Hours
- [x] Extract -> Hour, Minutes, and Seconds parts of Decimal Hours
- [x] Convert -> Local Civil Time <-> Universal Time
- [x] Convert -> Universal Time <-> Greenwich Sidereal Time
- [x] Convert -> Greenwich Sidereal Time <-> Local Sidereal Time

### Coordinates

- [x] Convert -> Angle <-> Decimal Degrees
- [x] Convert -> Right Ascension <-> Hour Angle
- [x] Convert -> Equatorial Coordinates <-> Horizon Coordinates
- [x] Calculate -> Obliquity of the Ecliptic
- [x] Convert -> Ecliptic Coordinates <-> Equatorial Coordinates
- [x] Convert -> Equatorial Coordinates <-> Galactic Coordinates
- [x] Calculate -> Angle between two objects
- [x] Calculate -> Rising and Setting times for an object
- [x] Calculate -> Precession (corrected coordinates between two epochs)
- [x] Calculate -> Nutation (in ecliptic longitude and obliquity) for a Greenwich date
- [x] Calculate -> Effects of aberration for ecliptic coordinates
- [x] Calculate -> RA and Declination values, corrected for atmospheric refraction
- [x] Calculate -> RA and Declination values, corrected for geocentric parallax
- [x] Calculate -> Heliographic coordinates
- [x] Calculate -> Carrington rotation number
- [x] Calculate -> Selenographic (lunar) coordinates (sub-Earth and sub-Solar)

### The Sun

- [x] Calculate -> Approximate and precise positions of the Sun
- [x] Calculate -> Sun's distance and angular size
- [x] Calculate -> Local sunrise and sunset
- [x] Calculate -> Morning and evening twilight
- [x] Calculate -> Equation of time
- [x] Calculate -> Solar elongation

### Planets

- [x] Calculate -> Approximate position of planet
- [x] Calculate -> Precise position of planet
- [x] Calculate -> Visual aspects of planet (distance, angular diameter, phase, light time, position angle of bright limb, and apparent magnitude)

### Comets

- [x] Calculate -> Position of comet (elliptical)
- [x] Calculate -> Position of comet (parabolic)

### Binary Stars

- [x] Calculate -> Binary star orbit data

### The Moon

- [x] Calculate -> Approximate position of Moon
- [x] Calculate -> Precise position of Moon
- [x] Calculate -> Moon phase and position angle of bright limb
- [x] Calculate -> Times of new Moon and full Moon
- [x] Calculate -> Moon's distance, angular diameter, and horizontal parallax
- [x] Calculate -> Local moonrise and moonset

### Eclipses

- [x] Calculate -> Lunar eclipse occurrence
- [x] Calculate -> Lunar eclipse circumstances
- [x] Calculate -> Solar eclipse occurrence
- [x] Calculate -> Solar eclipse circumstances
