#include "PlayerShot.hpp"
#include <iostream>

sf::Time PlayerShot::FocusInterval;
sf::Time PlayerShot::NoFocusInterval;

float PlayerShot::FocusSpeed;
float PlayerShot::NoFocusSpeed;

float PlayerShot::DamagePerShot;

bool PlayerShot::isFocused;
bool PlayerShot::isShooting;

PlayerShot::PlayerShot()
  :isVisible(false)
{}

void PlayerShot::setTimeIntervals(const sf::Time& FocusTime, const sf::Time& NoFocusTime)
{
    FocusInterval = FocusTime;
    NoFocusInterval = NoFocusTime;
}

void PlayerShot::setSpeeds(const float Focus, const float NoFocus)
{
    FocusSpeed = Focus;
    NoFocusSpeed = NoFocus;
}

void PlayerShot::setFocus(const bool F)
{ isFocused = F; }

void PlayerShot::setDamage(const float MP)
{ DamagePerShot = MP; }

void PlayerShot::setRotation(const float angle)
{ Spr.setRotation(angle); }

void PlayerShot::setScale(const sf::Vector2f V)
{ Spr.setScale(V); }

void PlayerShot::setScale(const float x, const float y)
{ Spr.setScale(x, y); }

void PlayerShot::setPosition(const sf::Vector2f V)
{ Spr.setPosition(V); }

void PlayerShot::setPosition(const float x, const float y)
{ Spr.setPosition(x, y); }

void PlayerShot::move(const float x, const float y)
{ Spr.move(x, y); }

void PlayerShot::move(const sf::Vector2f V)
{ Spr.move(V); }

sf::Vector2f PlayerShot::getPosition() const
{ return Spr.getPosition(); }

void PlayerShot::setTextureRect(const sf::IntRect& TR)
{ Spr.setTextureRect(TR); }

void PlayerShot::setTexture(const sf::Texture& T)
{ Spr.setTexture(T); }

void PlayerShot::setMoveAngle(const float MA)
{ moveAngle = MA; }

bool PlayerShot::isOutofBounds()
{
    if(!ShotBounds.contains(getPosition()))
    { return true; }
    return false;
}

void PlayerShot::waitForShot(const sf::Vector2f& Start)
{
    if(isFocused)
    {
        if(ShotControl.getElapsedTime() >= FocusInterval)
        { isVisible = true; ShotControl.reset(); setPosition(Start); }
    }
    else
    {
        if(ShotControl.getElapsedTime() >= NoFocusInterval)
        { isVisible = true; ShotControl.reset(); setPosition(Start); }
    }
}

void PlayerShot::update(const sf::Vector2f& Start, const float FocusAngle, const float NoFocusAngle)
{
    if(isOutofBounds())
    {
        isVisible = false;
        ShotControl.resume();
        waitForShot(Start);
        if(isFocused)
        {
            setRotation(FocusAngle);
            setMoveAngle(FocusAngle);
            currentSpeed = FocusSpeed;
        }
        else
        {
            setRotation(NoFocusAngle);
            setMoveAngle(NoFocusAngle);
            currentSpeed = NoFocusSpeed;
        }
    }
    else
    { PolarLinearMove(); }
}

bool PlayerShot::getVisibility() const
{ return isVisible; }

void PlayerShot::PolarLinearMove()
{
    sf::Vector2f Start = getPosition();
    setPosition(0.f, 0.f);
    PolarVector P( getConvertedRadius(Start), moveAngle);
    P.r += currentSpeed;
    setPosition(P.TurnToRectangular());
    move(Start);
    //std::cout << getPosition().x << ", " << getPosition().y << std::endl;
}

void PlayerShot::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if(isVisible)
    target.draw(Spr, states);
}
