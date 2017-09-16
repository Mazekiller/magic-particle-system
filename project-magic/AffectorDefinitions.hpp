#pragma once

#include "Bullet.hpp"
#include "Distribution.hpp"

///Base affector class, holds nothing but a function called affect that is to be defined by affectors.

class Affector
{
    public:

        Affector();                         ///Creates an affector with a lifetime of maxtime.
        Affector(const sf::Time& life);     ///Creates an affector with specified lifetime.

        virtual ~Affector() = default;

        const bool isDead() const;

    protected:

        sf::Time Lifetime;
        mutable sf::Time TimePassed;

        virtual void affect(Bullet& b, const sf::Time& dt) const = 0;

        friend class Generator;
};

namespace TransformationAffectors
{

    class InitialSpeedBurstAffector : public Affector
    {
        public:

        private:

            virtual void affect(Bullet& b, const sf::Time& dt) const;

    };

    class LinearAccelerationAffector : public Affector
    {
        public:

        private:
            virtual void affect(Bullet& b, const sf::Time& dt) const;

    };

} //End of transformation affectors.


namespace RenderAffectors
{

    ///Requires a change in the texture to use.
    class BirthAnimationAffector : public Affector
    {
        public:

        private:

            virtual void affect(Bullet& b, const sf::Time& dt) const;

    };



    ///Requires a change in the texture to use.
    class DeathAnimationAffector : public Affector
    {
        public:

        private:

            virtual void affect(Bullet& b, const sf::Time& dt);
    };



    class TypeChangeAffector : public Affector ///BulletType change must be more restrictive than color type change.
    {
        public:

            TypeChangeAffector(const Distribution<Bullet::BulletType>& Verify, const Distribution<Bullet::BulletType>& ChangeTo);
            TypeChangeAffector(const Distribution<Bullet::BulletType>& Verify, const Distribution<Bullet::BulletType>& ChangeTo, const sf::Time& changeTime);

            TypeChangeAffector(const Distribution<Bullet::BulletType>& ChangeTo, const sf::Time& changeTime);

            void changeAllBullets(const bool change); ///Allow any bullet to be changed regardless of type.

        private:
            Distribution<Bullet::BulletType> verify;  ///Change only "verify" type bullets to "change" type.
            Distribution<Bullet::BulletType> change;

            sf::Time bulletChangeTime;

            bool changeAll;

            virtual void affect(Bullet& b, const sf::Time& dt) const;
    };

    class ColorChangeAffector : public Affector
    {
        public:
            ColorChangeAffector(const Distribution<Bullet::BulletColor>& Verify, const Distribution<Bullet::BulletColor>& ChangeTo);
            ColorChangeAffector(const Distribution<Bullet::BulletColor>& Verify, const Distribution<Bullet::BulletColor>& ChangeTo, const sf::Time& changeTime);

            ColorChangeAffector(const Distribution<Bullet::BulletColor>& ChangeTo, const sf::Time& changeTime);

            void changeAllBullets(const bool change); ///Allow any bullet to be changed regardless of color.

        private:
            Distribution<Bullet::BulletColor> verify;
            Distribution<Bullet::BulletColor> change;

            sf::Time bulletChangeTime;

            bool changeAll;
            virtual void affect(Bullet& b, const sf::Time& dt) const;
    };

} //End of render affectors
