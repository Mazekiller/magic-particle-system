#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <string>

#include "Chronometer.hpp"
#include "PolarVector.hpp"
#include "MathConstants.hpp"



///Player hereda de esta clase, por eso Enemy base se maneja por separado.

class Characters
{
  public:
    Characters(const float sp = 0);

    virtual ~Characters();

    //virtual bool isDead() = 0; ///Verifica si murio.

    //virtual void Die() = 0; ///La animacion de muerte.

    ///Sobrecarga de transforms

    void setSpeed(const float Sp);

    void setPosition(const float x, const float y);
    void setPosition(const sf::Vector2f V);

    void move(const float x, const float y);
    void move(const sf::Vector2f V);

    void rotate(const float angDisplace); ///Por contingencias.
    void setRotation(const float ang);

    void setScale(const float x, const float y);
    void setScale(const sf::Vector2f V);

    void setOrigin(const float x, const float y); ///Facilidad de manejo de coordenadas.
    void setOrigin(const sf::Vector2f V);

    ///Sobrecarga de gets de dichos transforms.

    const sf::Vector2f& getPosition() const;
    const sf::Vector2f& getScale() const;
    const sf::Vector2f& getOrigin() const;
    const float getRotation() const;

    const float getDisplacement() const;

    bool MoveToPoint(const sf::Vector2f& V);
    ///Utiliza calculos polares, tiempo real, los movimientos precalculados son poco practicos.
    ///El punto puede cambiar internamente, lo que puede generar resultados interesantes.

    void setSpriteSheet(const std::string& path, unsigned Rows, unsigned Columns);
    ///Asume toda la textura como rectangulo de trabajo.

    void setSpriteSheet(const std::string& path, unsigned Rows, unsigned Columns, unsigned width, unsigned length);
    ///Esta ultima tiene el proposito de setearlo todo segun un sub-rectangulo.

    void setTexture(const sf::Texture& T);

    void setTextureRect(const sf::IntRect& D);

  protected:
    float speed;
    sf::Vector2f StartPosition;
    PolarVector MotionControl; ///Para movimiento lineal.


    ///Animaciones, Sprites y Texturas.
    sf::Sprite Entity;     ///No necesita explicacion.
    sf::Texture Skin;    ///Para manejo del sprite sheet.

    unsigned SprRows;    ///Filas del Sprite Sheet.
    unsigned SprColumns; ///Columnas del Sprite Sheet.
    unsigned SprX; ///La dimension X del sprite individual.
    unsigned SprY; ///La dimension Y del sprite individual.

    sf::IntRect TR;
    Chronometer AnimMeter;
    bool controlRect;
    unsigned AnimIndex;

};
