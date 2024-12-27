#ifndef _pa_binary
#define _pa_binary

#include "pa_models.h"
#include <string>
#include <tuple>

using namespace pa_models;

class PABinary {
public:
  CBinaryStarOrbitalData binaryStarOrbit(double greenwichDateDay,
                                         int greenwichDateMonth,
                                         int greenwichDateYear,
                                         std::string binaryName);
};

#endif
