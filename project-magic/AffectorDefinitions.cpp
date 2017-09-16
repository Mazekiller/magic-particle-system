#include "AffectorDefinitions.hpp"
#include "MathConstants.hpp"

Affector::Affector()
:Lifetime(MaxTime)
,TimePassed(sf::Time::Zero)
{}

Affector::Affector(const sf::Time& life)
:Lifetime(life)
,TimePassed(sf::Time::Zero)
{}

const bool Affector::isDead() const
{ return TimePassed.asMilliseconds() >= Lifetime.asMilliseconds(); }


namespace RenderAffectors
{
    TypeChangeAffector::TypeChangeAffector(const Distribution<Bullet::BulletType>& Verify, const Distribution<Bullet::BulletType>& ChangeTo)
      :verify(Verify)
      ,change(ChangeTo)
      ,bulletChangeTime(sf::Time::Zero)
      ,changeAll(false)
    {}

    TypeChangeAffector::TypeChangeAffector(const Distribution<Bullet::BulletType>& Verify, const Distribution<Bullet::BulletType>& ChangeTo, const sf::Time& changeTime)
      :verify(Verify)
      ,change(ChangeTo)
      ,bulletChangeTime(changeTime)
      ,changeAll(false)
    {}

    TypeChangeAffector::TypeChangeAffector(const Distribution<Bullet::BulletType>& ChangeTo, const sf::Time& changeTime)
      :change(ChangeTo)
      ,verify(ChangeTo) //Not needed in this case.
      ,bulletChangeTime(changeTime)
      ,changeAll(true)
    {}

    void TypeChangeAffector::affect(Bullet& b, const sf::Time& dt) const
    {
        if ( (b.getType() == verify.uniform() && b.getPassedLifetime() >= bulletChangeTime ) || (changeAll && b.getPassedLifetime() >= bulletChangeTime))
        { b.setType(change.uniform()); }

        TimePassed += dt;
    }

    ColorChangeAffector::ColorChangeAffector(const Distribution<Bullet::BulletColor>& Verify, const Distribution<Bullet::BulletColor>& ChangeTo)
      :verify(Verify)
      ,change(ChangeTo)
      ,bulletChangeTime(sf::Time::Zero)
      ,changeAll(false)
    {}

    ColorChangeAffector::ColorChangeAffector(const Distribution<Bullet::BulletColor>& Verify, const Distribution<Bullet::BulletColor>& ChangeTo, const sf::Time& changeTime)
      :verify(Verify)
      ,change(ChangeTo)
      ,bulletChangeTime(changeTime)
      ,changeAll(false)
    {}

    ColorChangeAffector::ColorChangeAffector(const Distribution<Bullet::BulletColor>& ChangeTo, const sf::Time& changeTime)
      :change(ChangeTo)
      ,verify(ChangeTo)
      ,bulletChangeTime(changeTime)
      ,changeAll(true)
    {}

    void ColorChangeAffector::affect(Bullet& b, const sf::Time& dt) const
    {
         if ( (b.getType() == verify.uniform() && b.getPassedLifetime() >= bulletChangeTime ) || (changeAll && b.getPassedLifetime() >= bulletChangeTime))
        { b.setColor(change.uniform()); }

        TimePassed += dt;
    }



}
