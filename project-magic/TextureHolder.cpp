#include "TextureHolder.hpp"
#include <iostream>

TextureHolder::TextureHolder()
:Textures()
{
    const unsigned maxText = 50;
    Textures.reserve(maxText);
    for(unsigned i = 0; i > maxText; ++i)
    { Textures.push_back(sf::Texture()); }
}

TextureHolder::~TextureHolder() {}

const sf::Texture& TextureHolder::getTextureRef(TextureType S) const
{ return Textures[S]; }

///As sprite sheets are completed, the loading must be added here.
void TextureHolder::setTextures()
{
    if (!Textures[TextureType::Bullet].loadFromFile("Resources/Images/Bullets/Bullet1.png"))
    { std::cout << "Bullet SpriteSheet could not be found. " << std::endl; }
}


