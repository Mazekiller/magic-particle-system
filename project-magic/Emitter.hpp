#pragma once

#include <utility>
#include <functional>

#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Vector2.hpp>

#include "Bullet.hpp"
#include "Distribution.hpp"

///The class emitter is supposed to be a base class for emitters of different types of shapes and things.

///However because of technical challenges I will attempt to make it as a bullet generator only for now, then as a base class for all emitters needed
///This class is the emitter for bullets as of now 20/04/2015. It will not be used as a base class,
///it will be used as a class held by the real programmed emitter, but avoiding unnecessary polymorphism.

///29/05/2015 Update, Emitter and Affector must have a list of bullet types and colors not accessible to the particular emitters, since no texture rect exists for them.
///This is so that there may be a data control system to avoid run-time errors at emission or affection time. This may change with the use of a new texture.

///Once tests give an ok, must implement an EmitRadius funcionality.
///03/07/2015 Must add Thor to use some basic functionalities implemented in it.

class Generator;

class Emitter
{
    public:

        enum EmissionType
        {
            Gradual,  ///Gradual makes the bullets be emitted equally with time.
            Instant   ///Instant emits all bullets stated by the emission rate per second.
        };

    private:

        struct EmissionRate
        {
            public:
                EmissionRate(const unsigned a, const sf::Time& t) :amount(a), timespan(t) {}

                unsigned amount;
                sf::Time timespan;
        };

    public:
        Emitter(const unsigned amount, const sf::Time& EmissionTime);
        Emitter(const unsigned amount, const sf::Time& EmissionTime, EmissionType EM);

        virtual ~Emitter() = default;

        ///Make set functions for parametrized values.

        void PauseEmission(const bool Accumulate = false);
        void ResumeEmission();

        EmissionRate getEmissionRate() const;
        EmissionType getEmissionType() const;

        const sf::Vector2f& getOriginPoint() const;

        const sf::Time& getEmitterLifetime() const;
        const bool isEmitting() const;
        const bool isDead() const;

        void setEmissionRate(const EmissionRate& ER);
        void setEmissionRate(EmissionRate&& ER);
        void setEmissionRate(const unsigned Amount, const sf::Time& T);

        void setEmissionType(EmissionType EM);

        void setEmitterLifetime(const sf::Time& T);
        void setEmitterLifetime(sf::Time&& T);

        void setOriginPoint(const sf::Vector2f& OP);

    public:

        void setColorDistribution(Distribution<Bullet::BulletColor> RandomColor);
        void setTypeDistribution(Distribution<Bullet::BulletType> RandomType);
        void setLinearSpeedDistribution(Distribution<float> RandomLineSpeed);
        void setRotationToSelfSpeedDistribution(Distribution<float> RandomRotationToSelfSpeed);
        void setRotationSpeedDistribution(Distribution<float> RandomRotationSpeed);
        void setRotationAngleDistribution(Distribution<float> RandomRotationAngle);
        void setBulletLifetimeDistribution(Distribution<sf::Time> BulletLifeTime);

    protected:
        ///Distributions for colors and types will be used by most all emitters.

        Distribution<float> DRA;    ///Rotation Angle distribution.
        Distribution<float> DRTSS;  ///Rotation to self speed distribution.
        Distribution<float> DRS;    ///Rotation Speed distribution.
        Distribution<float> DLS;    ///Linear Speed distribution.

        Distribution<Bullet::BulletColor> DBC;
        Distribution<Bullet::BulletType> DBT;

        Distribution<sf::Time> BLT;

    protected:

        //std::function EmitterAffector;
        bool AccumulateBullets;

        EmissionRate emissionRate;       ///< Emission Rate, uses unsigned (amount of bullets) and sf::Time (time to emit said amount).

        void emit(const Generator& g, const sf::Time& dt) const; ///This function is called by Generator to emit all the bullets needed.
        virtual void create(const Generator& g) const = 0; ///The creator function, generates all bullets on call from emit. Should be a functor to a function that creates the bullet based on formula.

        sf::Vector2f OriginPoint;

        sf::Time emitterLifetime;                         ///< Amount of time the emitter will live for.
        sf::Time lifetimeClock;                          ///< Controls the lifetime of the emitter, use a thor::chronometer instead.

        mutable sf::Time Timepassed;

        mutable sf::Clock emissionClock;                         ///< Clock used for on frame calculations.

        mutable float emissionCue;

        sf::Vector2f BulletTransformOrigin;               ///< The origin used for the transformations of the bullets
        bool isEmissionPaused;

        EmissionType EMT;                                 ///< The type of emission that the emitter uses. Gradual or Instant.

        friend class Generator;

};

void CreateBullet(const Generator& g, const sf::Time& life,Bullet::BulletType T, Bullet::BulletColor C, const sf::Vector2f& ori,const sf::Vector2f& pos, const sf::Vector2f& vel, const float LinVel,const sf::Vector2f& scale, const float rot = 0.f, const float rotSp = 0.f, const float rotSelf = 0.f, const float rotSelfSp = 0.f);
