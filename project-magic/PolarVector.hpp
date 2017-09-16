#pragma once

#include "MathConstants.hpp"
#include <cmath>

class PolarVector
{
  public:
        float r;
        float t; ///Angle stored in degrees.

        PolarVector();
        PolarVector(float radius, float angle);
        PolarVector(const sf::Vector2f V2); ///Conversion constructor.

        sf::Vector2f TurnToRectangular() const;

};

PolarVector TurnToPolar(const sf::Vector2f point);

float getConvertedRadius(const sf::Vector2f point);

float getConvertedAngle(sf::Vector2f point);

bool operator ==(const PolarVector& left, const PolarVector& right);

bool operator !=(const PolarVector& left, const PolarVector& right);
