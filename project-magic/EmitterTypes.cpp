#include "EmitterTypes.hpp"

PolarEmitter::PolarEmitter(const unsigned amount, const sf::Time& EmissionTime)
:Emitter(amount, EmissionTime)
,Range(0.f, 360.f)
,emitRadiusIndex(0.f)
,emitAngleIndex(0.f)
,hasClockwiseEmission(false)
,isSelfRotationSet(false)
{}

PolarEmitter::PolarEmitter(const unsigned amount, const sf::Time& EmissionTime, EmissionType EM)
:Emitter(amount, EmissionTime, EM)
,Range(0.f, 360.f)
,emitRadiusIndex(0.f)
,emitAngleIndex(0.f)
,hasClockwiseEmission(false)
,isSelfRotationSet(false)
{}

void PolarEmitter::setRange(const float start, const float end)
{
    Range.first = start;
    Range.second = end;
}

void PolarEmitter::setClockwiseEmission(const bool CE)
{ hasClockwiseEmission = CE; }

void PolarEmitter::setRotationToSelfOnCreation(const bool b)
{ isSelfRotationSet = b; }
