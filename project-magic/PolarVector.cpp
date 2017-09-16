#include "PolarVector.hpp"

PolarVector::PolarVector()
 :r(0.f)
 ,t(0.f)
{}

PolarVector::PolarVector(float radius, float angle)
 :r(radius)
 ,t(angle)
{}

PolarVector::PolarVector(const sf::Vector2f V2)
 :r(getConvertedRadius(V2))
 ,t(getConvertedAngle(V2))
{}

sf::Vector2f PolarVector::TurnToRectangular() const
{ return sf::Vector2f(static_cast<float>(r* Math<float>::cos(t)), static_cast<float>(r* Math<float>::sin(t))); }

PolarVector TurnToPolar(const sf::Vector2f point)
{
    PolarVector PV;
    PV.r = getConvertedAngle(point);
    PV.t = getConvertedRadius(point);
    return PV;
}

float getConvertedRadius(const sf::Vector2f point)
{ return Math<float>::sqrt((point.x * point.x) + (point.y * point.y) ); }

float getConvertedAngle(const sf::Vector2f point)
{ return Math<float>::atan2(point.y, point.x); }

bool operator ==(const PolarVector& left, const PolarVector& right)
{
  float diffR = left.r - right.r;
  float diffA = left.t - right.t;
  return ((diffR <= EPSILON) && (diffA <= EPSILON));
}

bool operator !=(const PolarVector& left, const PolarVector& right)
{
  float diffR = left.r - right.r;
  float diffA = left.t - right.t;
  return !((diffR <= EPSILON) && (diffA <= EPSILON));
}
