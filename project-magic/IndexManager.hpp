#pragma once

#include "PolarVector.hpp"

struct PolarIndex
{
    float o;
    PolarVector PV;
    PolarIndex();
    PolarIndex(float angle);
};
