#include "EmitterDefinitions.hpp"

#include "PolarVector.hpp"
#include "MathConstants.hpp"

#include <iostream>

namespace BasicPatterns
{

    ///Circle emitter definitions.
    CircleEmitter::CircleEmitter(const unsigned amount, const sf::Time& EmissionTime)
    :PolarEmitter(amount, EmissionTime)
    ,radius(0.f)
    {
        setRange(0.f, 360.f);
        setClockwiseEmission(true);
    }

    CircleEmitter::CircleEmitter(const unsigned amount, const sf::Time& EmissionTime, EmissionType EM)
    :PolarEmitter(amount, EmissionTime, EM)
    ,radius(0.f)
    {
        setRange(0.f, 360.f);
        setClockwiseEmission(true);
    }

    void CircleEmitter::setRadius(const float r)
    { radius = r; }

    void CircleEmitter::create(const Generator& g) const
    { //Use Emitter defined parameters to write as little code as possible.
        float angSpace = Range.second / emissionRate.amount;

        PolarVector PV(radius, emitAngleIndex);
        sf::Vector2f R = PV.TurnToRectangular();

        float x = Range.second - Range.first;

        emitAngleIndex = fmod(emitAngleIndex, x);

        emitAngleIndex += Range.first;

        if(isSelfRotationSet)
        { CreateBullet(g, BLT.uniform(), DBT.uniform(), DBC.uniform(), OriginPoint, R, sf::Vector2f(0.f, 0.f), DLS.uniform(), sf::Vector2f(1.f, 1.f), DRA.uniform(), DRS.uniform(), std::abs(fmod(emitAngleIndex + 360, Range.second)), DRTSS.uniform()); }
        else
        { CreateBullet(g, BLT.uniform(), DBT.uniform(), DBC.uniform(), OriginPoint, R, sf::Vector2f(0.f, 0.f), DLS.uniform(), sf::Vector2f(1.f, 1.f), DRA.uniform(), DRS.uniform(), 0.f, 0.f); }

        if(!hasClockwiseEmission)
        { emitAngleIndex -= angSpace; }
        else
        { emitAngleIndex += angSpace; }

    }

    ///Flower Emitter Definition.
    FlowerEmitter::FlowerEmitter(const unsigned amount, const sf::Time& EmissionTime)
      :PolarEmitter(amount, EmissionTime)
      ,petals(0)
    {}

    FlowerEmitter::FlowerEmitter(const unsigned amount, const sf::Time& EmissionTime, EmissionType EM)
      :PolarEmitter(amount, EmissionTime, EM)
      ,petals(0)
    {}

    void FlowerEmitter::setPetals(const unsigned Petals)
    { petals = Petals; }

    void FlowerEmitter::setFlowerSize(const unsigned size)
    { flowerSize = size; }


    void FlowerEmitter::create(const Generator& g) const
    { ///Use Emitter defined parameters to write as little code as possible.
        float angSpace = Range.second / emissionRate.amount;

        PolarVector PV(flowerSize * 10 * Math<float>::sin(emitAngleIndex * petals), emitAngleIndex);
        sf::Vector2f R = PV.TurnToRectangular();

        float x = Range.second - Range.first;

        emitAngleIndex = fmod(emitAngleIndex, x);

        emitAngleIndex += Range.first;

        if(isSelfRotationSet)
        { CreateBullet(g, BLT.uniform(), DBT.uniform(), DBC.uniform(), OriginPoint, R, sf::Vector2f(0.f, 0.f), DLS.uniform(), sf::Vector2f(1.f, 1.f), DRA.uniform(), DRS.uniform(), std::abs(fmod(emitAngleIndex + 360, Range.second)), DRTSS.uniform()); }
        else
        { CreateBullet(g, BLT.uniform(), DBT.uniform(), DBC.uniform(), OriginPoint, R, sf::Vector2f(0.f, 0.f), DLS.uniform(), sf::Vector2f(1.f, 1.f), DRA.uniform(), DRS.uniform(), 0.f, 0.f); }

        //This is just a test.
        if(!hasClockwiseEmission)
        { emitAngleIndex -= angSpace; }
        else
        { emitAngleIndex += angSpace; }

    }

    ///Rose Emitter Definition.
    RoseEmitter::RoseEmitter(const unsigned amount, const sf::Time& EmissionTime, const float calculatedValue)
      :PolarEmitter(amount, EmissionTime)
      ,k(calculatedValue)
      ,roseSize(1)
    { setRange(0.f, 1800.f); }

    RoseEmitter::RoseEmitter(const unsigned amount, const sf::Time& EmissionTime, const float calculatedValue, const unsigned RoseSize)
      :PolarEmitter(amount, EmissionTime)
      ,k(calculatedValue)
      ,roseSize(RoseSize)
    { setRange(0.f, 1800.f); }

    RoseEmitter::RoseEmitter(const unsigned amount, const sf::Time& EmissionTime, EmissionType EM, const float calculatedValue)
      :PolarEmitter(amount, EmissionTime, EM)
      ,k(calculatedValue)
      ,roseSize(1)
    { setRange(0.f, 1800.f); }

    RoseEmitter::RoseEmitter(const unsigned amount, const sf::Time& EmissionTime, EmissionType EM, const float calculatedValue, const unsigned RoseSize)
      :PolarEmitter(amount, EmissionTime, EM)
      ,k(calculatedValue)
      ,roseSize(RoseSize)
    { setRange(0.f, 1800.f); }

    void RoseEmitter::setRoseCalculationValue(const float calcVal)
    { k = calcVal; }

    void RoseEmitter::setRoseSize(const unsigned size)
    { roseSize = size; }

    void RoseEmitter::create(const Generator& g) const
    {
       float angSpace = Range.second / emissionRate.amount;

        PolarVector PV(roseSize * 10 * Math<float>::sin(emitAngleIndex * k), emitAngleIndex);
        sf::Vector2f R = PV.TurnToRectangular();

        float x = Range.second - Range.first;

        emitAngleIndex = fmod(emitAngleIndex, x);

        emitAngleIndex += Range.first;

        if(isSelfRotationSet)
        { CreateBullet(g, BLT.uniform(), DBT.uniform(), DBC.uniform(), OriginPoint, R, sf::Vector2f(0.f, 0.f), DLS.uniform(), sf::Vector2f(1.f, 1.f), DRA.uniform(), DRS.uniform(), std::abs(fmod(emitAngleIndex + 360, Range.second)), DRTSS.uniform()); }
        else
        { CreateBullet(g, BLT.uniform(), DBT.uniform(), DBC.uniform(), OriginPoint, R, sf::Vector2f(0.f, 0.f), DLS.uniform(), sf::Vector2f(1.f, 1.f), DRA.uniform(), DRS.uniform(), 0.f, 0.f); }

        if(!hasClockwiseEmission)
        { emitAngleIndex -= angSpace; }
        else
        { emitAngleIndex += angSpace; }
    }

    LuaScriptEmitter::LuaScriptEmitter(const unsigned amount, const sf::Time& EmissionTime, EmissionType EM, LuaStateHandle& l, const std::string& path)
      :PolarEmitter(amount, EmissionTime, EM)
      ,LuaRef(l)
      ,scriptPath(path)
    {}

    void LuaScriptEmitter::create(const Generator& g) const
    {
        float angSpace = Range.second / emissionRate.amount;

        //float ff = LuaRef.RunEmitterFormulaScript(scriptPath, emitAngleIndex);

        PolarVector PV(LuaRef.RunEmitterFormulaScript(scriptPath, emitAngleIndex), emitAngleIndex);
        sf::Vector2f R = PV.TurnToRectangular();

        float x = Range.second - Range.first;

        emitAngleIndex = fmod(emitAngleIndex, x);

        emitAngleIndex += Range.first;

        if(isSelfRotationSet)
        { CreateBullet(g, BLT.uniform(), DBT.uniform(), DBC.uniform(), OriginPoint, R, sf::Vector2f(0.f, 0.f), DLS.uniform(), sf::Vector2f(1.f, 1.f), DRA.uniform(), DRS.uniform(), std::abs(fmod(emitAngleIndex + 360, Range.second)), DRTSS.uniform()); }
        else
        { CreateBullet(g, BLT.uniform(), DBT.uniform(), DBC.uniform(), OriginPoint, R, sf::Vector2f(0.f, 0.f), DLS.uniform(), sf::Vector2f(1.f, 1.f), DRA.uniform(), DRS.uniform(), 0.f, 0.f); }

        if(!hasClockwiseEmission)
        { emitAngleIndex -= angSpace; }
        else
        { emitAngleIndex += angSpace; }
    }



} //End of Basic Patterns



