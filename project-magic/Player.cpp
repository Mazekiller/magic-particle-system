#include "Player.hpp"
#include <iostream>

const float Player::BasicDamage = 2.f;

Player::Player()
  :Characters(), MagicResistance(0), AttackPower(0), PIP(P_Unfocused)
  ,PAS(P_Static), isHurt(Healthy), ItemHolder(), OrderControl(3)
{}

void Player::setAttackPower(const float AP)
{ AttackPower = AP; }

void Player::setMagicResistance(const float MR)
{ MagicResistance = MR; }

#if 0
void Player::setSatelliteAmount(Shooter::SatNumber SN)
{ SH.setSatelliteAmount(SN); }

void Player::setShooter(Shooter::ShotType SS)
{ SH.setShotType(SS); }
#endif

void Player::eventHandler(sf::Event& e)
{
    PollShootEvent(e);
}

void Player::RealTimeEventHandle()
{
    PollMoveEvent();
    FocusPollEvent();
}

void Player::PollMoveEvent()
{
    PAS = P_Static;
    if(PIP == P_Focused)
    {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            Entity.move(-FocusSpeed, 0.f);
            //SH.displaceShotPoints(sf::Vector2f(-FocusSpeed, 0.f));
            PAS = P_Left;
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            Entity.move(FocusSpeed, 0.f);
            //SH.displaceShotPoints(sf::Vector2f(FocusSpeed, 0.f));
            PAS = P_Right;
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            Entity.move(0.f, -FocusSpeed);
            //SH.displaceShotPoints(sf::Vector2f(0.f, -FocusSpeed));
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            Entity.move(0.f, FocusSpeed);
            //SH.displaceShotPoints(sf::Vector2f(0.f, FocusSpeed));
        }

    }
    else
    {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            Entity.move(-speed, 0.f);
            //SH.displaceShotPoints(sf::Vector2f(-speed, 0.f));
            PAS = P_Left;
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            Entity.move(speed, 0.f);
            //SH.displaceShotPoints(sf::Vector2f(speed, 0.f));
            PAS = P_Right;
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            Entity.move(0.f, -speed);
            //SH.displaceShotPoints(sf::Vector2f(0.f, -speed));
        }


        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            Entity.move(0.f, speed);
            //SH.displaceShotPoints(sf::Vector2f(0.f, speed));
        }

    }

    if(AnimIndex > (SprRows - 1)) AnimIndex = 0;
}

void Player::PollShootEvent(sf::Event& X)
{
    if(X.type == sf::Event::KeyPressed )
    {
        if(X.key.code == sf::Keyboard::Z)
        {
            if(!isShooting)
            { isShooting = true; }
            else
            { isShooting = false; }
        }
    }
}

void Player::FocusPollEvent()
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
    { PIP = P_Focused; }
    else
    { PIP = P_Unfocused; }
}

void Player::setCharacter(PlayableCharacter Pl)
{
    PPC = Pl;

    if (Pl == Agnar)
    {
        setAnimationOrder(P_Static, P_Left, P_Right);
        setSpriteSheet("C:/Users/Carlos/Desktop/Game Making/Projects/ProjectGame/Resources/Images/Characters/Player/Agnar/pl00.png", 8, 3, 256, 168);
        speed = 2.f;
        FocusSpeed = 1.f;
        //SH.setShotTexture(Skin);
        //SH.setFocus(true);
    }
    else
    {
        ///Detalles del Sprite Sheet.
    }
}


void Player::setAnimationOrder(PlayerAnimStates First, PlayerAnimStates Second, PlayerAnimStates Third)
{
    OrderControl[0] = std::pair<unsigned, PlayerAnimStates> (0, First);
    OrderControl[1] = std::pair<unsigned, PlayerAnimStates> (1, Second);
    OrderControl[2] = std::pair<unsigned, PlayerAnimStates> (2, Third);
}

void Player::AnimationManagement()
{
    ///Bugged code.

    unsigned i = 0;
    while(PAS != OrderControl[i].second)
    {
        if(i == OrderControl.size()) break;
        ++i;
    }

    TR.left = 0;
    TR.top = SprY * i;
    TR.width = SprX;
    TR.height = SprY;

    AnimMeter.resume();

    TR.left = SprX * AnimIndex;
    Entity.setTextureRect(TR);

    if(PAS == P_Static)
    {
        if (controlRect)
        {

            if(AnimMeter.getElapsedTime() > sf::seconds( 1.f/(SprRows*1.5f) ) )
            { ++AnimIndex; AnimMeter.reset(); }
            if(AnimIndex >= (SprRows - 1) ) { controlRect = false; }
        }
        else
        {
            AnimIndex = 0;
            controlRect = true;
        }
    }
    else if (PAS == P_Left || PAS == P_Right)
    {
        if (AnimIndex < (SprRows - 1) && AnimMeter.getElapsedTime() > sf::seconds( 1.f/(SprRows*1.75f) ) )
        { ++AnimIndex; AnimMeter.reset(); controlRect = true; }
    }
}

void Player::update()
{
    PollMoveEvent();
    //SH.Shoot();
    AnimationManagement();
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    //target.draw(SH, states);
    target.draw(Entity, states);
}
