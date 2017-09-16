#include "Emitter.hpp"
#include "MathConstants.hpp"

#include <cmath>
#include <cstdlib>
#include <iostream>

Emitter::Emitter(const unsigned amount, const sf::Time& EmissionTime)
:emissionRate(amount, EmissionTime)
,emitterLifetime(MaxTime) ///Life of the emitter is endless by default
,emissionClock()
,emissionCue(0.f)
,lifetimeClock()
,isEmissionPaused(true)
,BulletTransformOrigin(0.f, 0.f)
,EMT(Emitter::EmissionType::Gradual) ///The default emission type.
,OriginPoint(0.f, 0.f)
,DBC(Bullet::BulletColor::Gray)
,DBT(Bullet::BulletType::Circle)
,DLS(0.f)
,DRA(0.f)
,DRS(0.f)
,DRTSS(0.f)
,BLT(sf::Time::Zero)
,Timepassed(sf::Time::Zero)
,AccumulateBullets(false)
//,EmitterAffector()
{}

Emitter::Emitter(const unsigned amount, const sf::Time& EmissionTime, EmissionType EM)
:emissionRate(amount, EmissionTime)
,emitterLifetime(MaxTime) ///Life of the emitter is endless by default
,emissionClock()
,emissionCue(0.f)
,lifetimeClock()
,isEmissionPaused(true)
,BulletTransformOrigin(0.f, 0.f)
,EMT(EM)
,OriginPoint(0.f, 0.f)
,DBC(Bullet::BulletColor::Gray)
,DBT(Bullet::BulletType::Circle)
,DLS(0.f)
,DRA(0.f)
,DRS(0.f)
,DRTSS(0.f)
,BLT(sf::Time::Zero)
,Timepassed(sf::Time::Zero)
,AccumulateBullets(false)
//,EmitterAffector()
{}

void Emitter::PauseEmission(const bool Accumulate)
{
    isEmissionPaused = true;
    AccumulateBullets = Accumulate;
}

void Emitter::ResumeEmission()
{ isEmissionPaused = false; }

Emitter::EmissionRate Emitter::getEmissionRate() const
{ return emissionRate; }

Emitter::EmissionType Emitter::getEmissionType() const
{ return EMT; }

const bool Emitter::isEmitting() const
{ return !isEmissionPaused; }

const bool Emitter::isDead() const
{ return Timepassed >= emitterLifetime; }

const sf::Time& Emitter::getEmitterLifetime() const
{ return emitterLifetime; }

void Emitter::setEmitterLifetime(const sf::Time& T)
{ emitterLifetime = T; }

void Emitter::setEmitterLifetime(sf::Time&& T)
{ emitterLifetime = std::move(T); }

void Emitter::setEmissionType(EmissionType EM)
{ EMT = EM; }

void Emitter::setEmissionRate(const unsigned Amount, const sf::Time& T)
{
    emissionRate.amount = Amount;
    emissionRate.timespan = T;
}

void Emitter::setEmissionRate(const EmissionRate& ER)
{ emissionRate = ER; }

void Emitter::setEmissionRate(EmissionRate&& ER)
{ emissionRate = std::move(ER); }

void Emitter::setOriginPoint(const sf::Vector2f& OP)
{ OriginPoint = OP; }

const sf::Vector2f& Emitter::getOriginPoint() const
{ return OriginPoint; }

void Emitter::emit(const Generator& g, const sf::Time& dt) const
{

    if(!isEmissionPaused)
    {
        if(EMT == Emitter::EmissionType::Instant)
        {
            if(emissionClock.getElapsedTime().asMilliseconds() >= emissionRate.timespan.asMilliseconds())
            {
                for(unsigned x = 0; x < emissionRate.amount; ++x)
                { create(g); }
                emissionClock.restart();
            }
        }
        else
        {
            emissionCue += ( ( emissionRate.amount / emissionRate.timespan.asSeconds() ) / 1000 ) * emissionClock.getElapsedTime().asMilliseconds();
            unsigned thisEmission = static_cast<unsigned>(emissionCue); //Know how many bullets will be emitted this frame.

            emissionCue -= thisEmission; //Once the amount of bullets to emit this frame is known, they are eliminated from the emissionCue,

            for(unsigned x = 0; x < thisEmission; ++x)
            { create(g); }
            emissionClock.restart();
        }

        Timepassed += dt;
    }
    else
    {
        if(!AccumulateBullets)
        { emissionClock.restart(); }
    }
}

void Emitter::setBulletLifetimeDistribution(Distribution<sf::Time> BulletLifeTime)
{ BLT = std::move(BulletLifeTime); }

void Emitter::setColorDistribution(Distribution<Bullet::BulletColor> RandomColor)
{ DBC = std::move(RandomColor); }

void Emitter::setTypeDistribution(Distribution<Bullet::BulletType> RandomType)
{ DBT = std::move(RandomType); }

void Emitter::setLinearSpeedDistribution(Distribution<float> RandomLineSpeed)
{ DLS = std::move(RandomLineSpeed); }

void Emitter::setRotationToSelfSpeedDistribution(Distribution<float> RandomRotationToSelfSpeed)
{ DRTSS = std::move(RandomRotationToSelfSpeed); }

void Emitter::setRotationSpeedDistribution(Distribution<float> RandomRotationSpeed)
{ DRS = std::move(RandomRotationSpeed); }

void Emitter::setRotationAngleDistribution(Distribution<float> RandomRotationAngle)
{ DRA = std::move(RandomRotationAngle); }
