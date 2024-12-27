#include "pa_binary.h"
#include "pa_data.h"
#include "pa_macros.h"
#include "pa_models.h"
#include "pa_util.h"
#include <cmath>
#include <string>

using namespace pa_types;
using namespace pa_models;
using namespace pa_util;
using namespace pa_macros;

/**
 * Calculate orbital data for binary star.
 */
CBinaryStarOrbitalData PABinary::binaryStarOrbit(double greenwichDateDay,
                                                 int greenwichDateMonth,
                                                 int greenwichDateYear,
                                                 std::string binaryName) {
  pa_data::BinaryStarData binaryInfo = pa_data::getBinaryStarData(binaryName);

  double yYears = greenwichDateYear +
                  (CivilDateToJulianDate(greenwichDateDay, greenwichDateMonth,
                                         greenwichDateYear) -
                   CivilDateToJulianDate(0, 1, greenwichDateYear)) /
                      365.242191 -
                  binaryInfo.epoch_peri;
  double mDeg = 360 * yYears / binaryInfo.period;
  double mRad = DegreesToRadians(mDeg - 360 * floor(mDeg / 360));
  double eccentricity = binaryInfo.ecc;
  double trueAnomalyRad = TrueAnomaly(mRad, eccentricity);
  double rArcsec =
      (1 - eccentricity * cos(EccentricAnomaly(mRad, eccentricity))) *
      binaryInfo.axis;
  double raPeriRad = trueAnomalyRad + DegreesToRadians(binaryInfo.long_peri);

  double y = sin(raPeriRad) * cos(DegreesToRadians(binaryInfo.incl));
  double x = cos(raPeriRad);
  double aDeg = WToDegrees(atan2(y, x));
  double thetaDeg1 = aDeg + binaryInfo.pa_node;
  double thetaDeg2 = thetaDeg1 - 360 * floor(thetaDeg1 / 360);
  double rhoArcsec = rArcsec * cos(raPeriRad) /
                     cos(DegreesToRadians((thetaDeg2 - binaryInfo.pa_node)));

  double positionAngleDeg = Round(thetaDeg2, 1);
  double separationArcsec = Round(rhoArcsec, 2);

  return CBinaryStarOrbitalData(positionAngleDeg, separationArcsec);
}
