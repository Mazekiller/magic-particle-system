#pragma once

#include <utility>

#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>

///20/07/2015 Bullets could have an emitterID to be able to know which emitter emitted them.
///This could be used by the affector to have selective affecting of the bullets.

class Bullet
{
    /**The bullet class will be used as a logical unit for Bullet Generators in order to easily
       and efficiently control and generate patterns. It is not drawable and cannot be used on its own.
       It will still hold all the different types of bullets and colors respectively.
      */
    public:

        enum BulletType ///Types of Bullets, used to calculate, texture rects and sizes.
        {
            DotBlast = 0, ///Minimum, 8x8 Pixels
            Point,
            Egg,
            LaserFrag = 3, ///Small, 16x16 Pixels
            Arrow,
            Circle_O,
            Circle,
            Eye,
            Knife,
            Cristal,
            Amulet,
            BShot,
            VoidShot,
            Star,
            Anchor,
            M_Star = 15, ///Medium, 32x32 Pixels
            M_Circle,
            Butterfly,
            Blade,
            EnergyShot,
            Heart,
            M_Arrow,
            Balloid = 22, ///Big, 64x64 Pixels
            BSpark,
            SmallBirthEffect = 24, ///For on-creation effects.
            MediumBirthEffect,
            DeathEffectFrame1,
            DeathEffectFrame2,
            DeathEffectFrame3,
            DeathEffectFrame4,
            DeathEffectFrame5,
            DeathEffectFrame6,
            DeathEffectFrame7,
            DeathEffectFrame8,
        };

        enum BulletColor
        {
            Gray = 0,   //Medium, Large
            Pink,
            Red = 2,        //Medium, Large
            Magenta,
            Purple = 4,     //Medium, Large
            DarkBlue,
            Blue = 6,       //Medium, Large
            Ice,
            Cyan = 8,       //Medium, Large
            DarkGreen,
            Green = 10,      //Medium, Large
            LightGreen,
            DarkYellow,
            Yellow = 13,     //Medium, Large
            Orange,
            Silver = 15 /*15*/ //Medium, Large
        };

        enum BulletSize
        {
            Minimum = 8,
            Small = 16,
            Medium = 32,
            Large = 64
        };

    public:
        Bullet(const sf::Time& Blife);
        Bullet(BulletType B, BulletColor C, const sf::Time& BLife);
        Bullet(BulletType B, BulletColor C, const sf::Vector2f& Pos, const sf::Vector2f& Vel, const sf::Time& BLife, const float RSpeed = 0, const float RSSpeed = 0);

        void setLifetime(sf::Time T);              ///Sets the lifetime the bullet will have.
        void setLifetime(sf::Time&& T);                   ///Sets the lifetime the bullet will have. Move semantics.

        void setType(Bullet::BulletType B);
        void setColor(Bullet::BulletColor C);

        bool isAlive() const; ///Should return true if the remaining lifetime is higher than 0 seconds.

        void setPosition(const sf::Vector2f& pos);        ///Sets the position of one of the bullets to be created.
        void setPosition(sf::Vector2f&& pos);             ///Sets the position of one of the bullets to be created. Move semantics.

        void setVelocity(const sf::Vector2f& vel);        ///Sets the velocity of one of the bullets to be created.
        void setVelocity(sf::Vector2f&& vel);             ///Sets the velocity of one of the bullets to be created. Move semantics.

        void setOrigin(const sf::Vector2f& O);
        void setOrigin(sf::Vector2f&& O);

        void setLinearVelocity(const float LV);           ///Sets the velocity for linear movement based on the angle of the bullet.

        void setRotation(const float ang);                ///Sets the rotation the bullet will have to the origin and will recalcultae it's position. (Hardly every to be used)
        void setRotationSpeed(const float ASP);           ///Sets the rotation speed of the bullet around its origin (speed is measured as 1 as one 360 degrees in one second)

        void setRotationToSelf(const float RTS);          ///Sets the angle of rotation to self that the bullet will have.
        void setRotationToSelfSpeed(const float RTSS);    ///Sets the speed the bullet will rotate itself at (speed is measured as 1 as one 360 degrees in one second)

        void setScale(const sf::Vector2f& S);         ///Sets the scale the bullet will have.
        void setScale(sf::Vector2f&& S);              ///Sets the scale the bullet will have. Move semantics.


        //Gets of properties.
        const sf::Vector2f& getPosition() const;
        const sf::Vector2f& getVelocity() const;
        const sf::Vector2f& getOrigin() const;
        const sf::Vector2f& getScale() const;
        const float getLinearVelocity() const;
        const float getRotation() const;
        const float getRotationSpeed() const;
        const float getRotationToSelf() const;
        const float getRotationToSelfSpeed() const;

        BulletType getType() const;
        BulletColor getColor() const;
        BulletSize getSize() const;

        sf::Time getPassedLifetime() const;
        sf::Time getTotalLifetime() const;

        sf::Time getRemainingLifetime() const;

        void restartClock();

        bool operator<(const Bullet& B) const; ///Used to order bullets by remaining lifetime
        bool operator>(const Bullet& B) const; ///Used to order bullets by remaining lifetime

    private:

        static const unsigned MinIndex;
        static const unsigned SmallIndex;
        static const unsigned MediumIndex;
        static const unsigned LargeIndex;

        //mutable bool needTextureRecomputing;           ///<A value to tell the Bullet Generator that it needs to recompute the Texture rect of the bullet.
        bool undereffect;
        BulletType Effect;

    public:

        sf::Vector2f Position;              ///<General position of the object.
        sf::Vector2f Velocity;              ///<Change in position per second.

        float LinearVelocity;               ///<The velocity the bullet uses for linear movements.

        float RotationAngle;                ///<Rotation Angle to origin point.
        float RotationSpeed;                ///<Rotation Speed or Also angular speed per second to origin point.

        float RotationToSelfAngle;          ///<Rotation angle around bullet's axis. 0 by default.
        float RotationToSelfSpeed;          ///<Rotation Speed around the bullet's axis. 0 by default.

        sf::Color Color;                    ///<Color that vertexes should have. White by default. Not very needed.

        sf::Vector2f Scale;                 ///<Scale, uses a vector in case it is desired to not have squared bullets. (1,1) by default.

        sf::Time TimePassed;               ///<The amount of time that has passed from the start. This needs to be a chronometer.

        sf::Vector2f Origin;                ///Origin for bullet creation.

        BulletType BT;                      ///<Bullet Type as defined in enum.
        BulletColor BC;                     ///<Bullet Color as defined in enum, works differently depending on bullt size since not all bullets are offered in all colors.

        sf::Time BulletLifetime;            ///<The amount of time the bullet will be rendered for.


};
