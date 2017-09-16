#include "Characters.hpp"

Characters::Characters(const float sp)
  :speed(sp), SprRows(0), SprColumns(0), SprX(0), SprY(0)
  ,AnimIndex(0), AnimMeter(), controlRect(true), TR()
{}

Characters::~Characters() {}

void Characters::setSpeed(const float Sp)
{ speed = Sp; }

void Characters::setOrigin(const float x, const float y)
{ Entity.setOrigin(x, y); }

void Characters::setOrigin(const sf::Vector2f V)
{ Entity.setOrigin(V); }

void Characters::setPosition(const float x, const float y)
{ Entity.setPosition(x, y); }

void Characters::setPosition(const sf::Vector2f V)
{ Entity.setPosition(V); }

void Characters::setRotation(const float ang)
{ Entity.setRotation(ang); }

void Characters::rotate(const float angDisplace)
{ Entity.rotate(angDisplace); }

void Characters::setScale(const float x, const float y)
{ Entity.setScale(x, y); }

void Characters::setScale(const sf::Vector2f V)
{ Entity.setScale(V); }

void Characters::move(const float x, const float y)
{ Entity.move(x, y); }

void Characters::move(const sf::Vector2f V)
{ Entity.move(V); }

const sf::Vector2f& Characters::getPosition() const
{ return Entity.getPosition(); }

const sf::Vector2f& Characters::getScale() const
{ return Entity.getScale(); }

const sf::Vector2f& Characters::getOrigin() const
{ return Entity.getOrigin(); }

const float Characters::getRotation() const
{ return Entity.getRotation(); }

bool Characters::MoveToPoint(const sf::Vector2f& V)
{

}

void Characters::setSpriteSheet(const std::string& path, unsigned Rows, unsigned Columns)
{
    Skin.loadFromFile(path);
    Entity.setTexture(Skin);
    SprRows = Rows;
    SprColumns = Columns;
    SprX = Skin.getSize().x/Rows;
    SprY = Skin.getSize().y/Columns;
}

void Characters::setSpriteSheet(const std::string& path, unsigned Rows, unsigned Columns, unsigned width, unsigned length)
{
    Skin.loadFromFile(path);
    Entity.setTexture(Skin);
    SprRows = Rows;
    SprColumns = Columns;
    SprX = width/Rows;
    SprY = length/Columns;
}










