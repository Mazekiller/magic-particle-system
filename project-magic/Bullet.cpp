#include "Bullet.hpp"
#include "MathConstants.hpp"
#include "TextureHolder.hpp"

#include <cmath>
#include <iostream>


const unsigned MinIndex = 3;
const unsigned SmallIndex = 15;
const unsigned MediumIndex = 22;
const unsigned LargeIndex = 24;

Bullet::Bullet(const sf::Time& BLife)
: BT(BulletType::Circle) ///Default Bullet
, BC(BulletColor::Gray)  ///Default Color
, BulletLifetime(BLife)
, Position()
, Velocity()
, Origin()
, LinearVelocity(0.f)
, RotationAngle(0.f)
, RotationSpeed(0.f)
, RotationToSelfAngle(0.f)
, RotationToSelfSpeed(0.f)
, Color(sf::Color(255, 255, 255, 255))
, Scale(1.f, 1.f)
, TimePassed(sf::Time::Zero)
, undereffect(false)
, Effect(BulletType::MediumBirthEffect)
{}

Bullet::Bullet(BulletType B, BulletColor C, const sf::Time& BLife)
: BT(B)
, BC(C)
, BulletLifetime(BLife)
, Position()
, Velocity()
, Origin()
, LinearVelocity(0.f)
, RotationAngle(0.f)
, RotationSpeed(0.f)
, RotationToSelfAngle(0.f)
, RotationToSelfSpeed(0.f)
, Color(sf::Color(255, 255, 255, 255))
, Scale(1.f, 1.f)
, TimePassed(sf::Time::Zero)
, undereffect(false)
, Effect(BulletType::MediumBirthEffect)
{}

Bullet::Bullet(BulletType B, BulletColor C, const sf::Vector2f& Pos, const sf::Vector2f& Vel, const sf::Time& BLife, const float RSpeed, const float RSSpeed)
: BT(B)
, BC(C)
, BulletLifetime(BLife)
, Origin()
, LinearVelocity(0.f)
, Position(Pos)
, Velocity(Vel)
, RotationAngle(0.f)
, RotationSpeed(RSpeed)
, RotationToSelfAngle(0.f)
, RotationToSelfSpeed(RSSpeed)
, Color(sf::Color(255, 255, 255, 255))
, Scale(1.f, 1.f)
, TimePassed(sf::Time::Zero)
, undereffect(false)
, Effect(BulletType::MediumBirthEffect)
{}

sf::Time Bullet::getPassedLifetime() const
{ return TimePassed; }

sf::Time Bullet::getTotalLifetime() const
{ return BulletLifetime; }

void Bullet::setLifetime(sf::Time T)
{ BulletLifetime = T; }

void Bullet::setLifetime(sf::Time&& T)
{ BulletLifetime = std::move(T); }

void Bullet::setType(BulletType T)
{ BT = T; }

void Bullet::setColor(BulletColor C)
{ BC = C; }

void Bullet::setPosition(const sf::Vector2f& pos)
{ Position = pos; }

void Bullet::setPosition(sf::Vector2f&& pos)
{ Position = std::move(pos); }

void Bullet::setVelocity(const sf::Vector2f& vel)
{ Velocity = vel; }

void Bullet::setVelocity(sf::Vector2f&& vel)
{ Velocity = std::move(vel); }

void Bullet::setOrigin(const sf::Vector2f& O)
{ Origin = O; }

void Bullet::setOrigin(sf::Vector2f&& O)
{ Origin = std::move(O); }

void Bullet::setLinearVelocity(const float LV)
{ LinearVelocity = LV; }

void Bullet::setRotation(const float ang)
{ RotationAngle = ang; }

void Bullet::setRotationSpeed(const float ASP)
{ RotationSpeed = ASP; }

void Bullet::setRotationToSelf(const float RTS)
{ RotationToSelfAngle = fmod(RTS, 360.f); }

void Bullet::setRotationToSelfSpeed(const float RTSS)
{ RotationToSelfSpeed = RTSS; }

void Bullet::setScale(const sf::Vector2f& S)
{ Scale = S; }

void Bullet::setScale(sf::Vector2f&& S)
{ Scale = std::move(S); }

const sf::Vector2f& Bullet::getPosition() const
{ return Position; }

const sf::Vector2f& Bullet::getVelocity() const
{ return Velocity; }

const sf::Vector2f& Bullet::getOrigin() const
{ return Origin; }

const sf::Vector2f& Bullet::getScale() const
{ return Scale; }

const float Bullet::getLinearVelocity() const
{ return LinearVelocity; }

const float Bullet::getRotation() const
{ return RotationAngle; }

const float Bullet::getRotationSpeed() const
{ return RotationSpeed; }

const float Bullet::getRotationToSelf() const
{ return RotationToSelfAngle; }

const float Bullet::getRotationToSelfSpeed() const
{ return RotationToSelfSpeed; }

Bullet::BulletType Bullet::getType() const
{ return BT; }

Bullet::BulletColor Bullet::getColor() const
{ return BC; }

Bullet::BulletSize Bullet::getSize() const
{
    if(static_cast<unsigned>(BT) < 3/*MinIndex*/)
    { return BulletSize::Minimum; }
    else if (static_cast<unsigned>(BT) < 15/*SmallIndex*/)
    { return BulletSize::Small; }
    else if (static_cast<unsigned>(BT) < 22/*MediumIndex*/)
    { return BulletSize::Medium; }
    else
    { return BulletSize::Large; }
}

bool Bullet::isAlive() const
{ return (BulletLifetime.asSeconds() > TimePassed.asSeconds()); }

void Bullet::restartClock()
{ TimePassed = sf::Time::Zero; }

bool Bullet::operator<(const Bullet& B) const
{ return(B.TimePassed < TimePassed); }

bool Bullet::operator>(const Bullet& B) const
{ return(B.TimePassed > TimePassed); }
