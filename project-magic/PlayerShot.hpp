#ifndef PLAYERSHOT_HPP
#define PLAYERSHOT_HPP

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Time.hpp>

#include "PolarVector.hpp"
#include "Chronometer.hpp"
#include "MathConstants.hpp"

class PlayerShot : public sf::Drawable
{
    public:
        PlayerShot();

        void setTexture(const sf::Texture& T);
        void setTextureRect(const sf::IntRect& TR);

        void setPosition(const float x, const float y);
        void setPosition(const sf::Vector2f V);

        void setRotation(const float angle);

        void move(const float x, const float y);
        void move(const sf::Vector2f V);

        void setScale(const float x, const float y);
        void setScale(const sf::Vector2f V);

        sf::Vector2f getPosition() const;

        bool isOutofBounds(); ///Checkeo de posicion basico.

        void waitForShot(const sf::Vector2f& Start);

        bool getVisibility() const;

        static void setDamage(const float MP);
        static void setFocus(const bool F);
        static void setSpeeds(const float Focus, const float NoFocus);
        static void setTimeIntervals(const sf::Time& FocusTime, const sf::Time& NoFocusTime);

        void setMoveAngle(const float MA);

        void update(const sf::Vector2f& Start, const float FocusAngle, const float NoFocusAngle);
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    private:
        void PolarLinearMove();

    private:
        sf::Sprite Spr;

        float currentSpeed;
        float moveAngle;

        bool isVisible;

        static bool isFocused;
        static bool isShooting;

        static float FocusSpeed;
        static float NoFocusSpeed;

        static float DamagePerShot;

        static sf::Time FocusInterval;
        static sf::Time NoFocusInterval;

        Chronometer ShotControl;
};

#endif // PLAYERSHOT_HPP
