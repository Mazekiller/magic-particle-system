#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <vector>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "Characters.hpp"
#include "Item.hpp"

///La clase Agnar, de objeto unico.
///Es necesario definir todos los detalles de las bombas y demas.
///Hacer con herencia.
///Necesita conocer el estado actual del juego.


///Los ShotTypes deben de tener su propia clase. Como Agnar y Luce ShotTypes respectivamente.

class Player : public Characters, public sf::Drawable
{
    public:

        enum PlayableCharacter : unsigned
        {
            Agnar,
            Luce,
        };

        enum PlayerAnimStates : unsigned
        {
            P_Static,
            P_Left,
            P_Right,
        };

        enum SpeedStates : unsigned
        {
            P_Focused,
            P_Unfocused,
        };

        enum Ailment : unsigned
        {
            Dead,
            Invincible,
            Healthy,
            Poison,
            Frost,
            PermaFrost,
            Burn,
            Silenced,
            Stunned,
        };

    public:
        Player();

        void setMagicResistance(const float MR);
        void setAttackPower(const float AP);

        //void setShooter(Shooter::ShotType S);
        //void setSatelliteAmount(Shooter::SatNumber SN);

        void update();

        void eventHandler(sf::Event& e); ///Maneja todos los eventos protected.

        void RealTimeEventHandle();

        void ApplyItemModifiers();

        void setCharacter(PlayableCharacter Pl);

        void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    private:
        void PollMoveEvent();
        void FocusPollEvent();

        void PollShootEvent(sf::Event& X); ///Evento que modifica una booleana.
        ///La booleana es usada por el shooter para ver si debe disparar o no.
        ///Se usa como un toggle, no como un disparador normal.

        void setAnimationOrder(PlayerAnimStates First, PlayerAnimStates Second, PlayerAnimStates Third);
        ///Setea el orden que debe de seguirse para ejecutar las animaciones.

        void AnimationManagement();
        void AilmentManagement();

    private:
        float MagicResistance;
        float AttackPower;
        float FocusSpeed;

        ///Mana y Reverse Mana son Mana/Black Mana y Sun/Moon Mana segun sea el personaje.

        float ManaMax;
        float ReverseManaMax;

        float Mana;
        float ReverseMana;

        //Shooter SH;
        ///Puntero a ser usado segun los diversos tipos de shooters que hay.

        ///Bomb* B;

        PlayableCharacter PPC;
        SpeedStates PIP;
        PlayerAnimStates PAS;
        Ailment isHurt;

        bool isShooting;

        std::vector<Item> ItemHolder;
        std::vector< std::pair<unsigned, PlayerAnimStates> > OrderControl;

        static const float BasicDamage; ///Minimum damage a player can do.
};

#endif
