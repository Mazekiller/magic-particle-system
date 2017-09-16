
#include <vector>

#include <SFML/Graphics/Texture.hpp>

#pragma once

/**The texture holder class is a wrapper for holding all the textures that will be used.
  *to avoid performance issues it is better to just have all textures in one place.
  *Texture holder makes sure that nobody has access to the textures themselves other than itself,
  *granting access by reference to all that request it, but not access to the textures themselves.
  *All textures receive access by the usage of the TextureTypes enum, since the textures are located in a vector
  that orders the textures according to the order in TextureTypes.
  */

class TextureHolder
{
    public:
        enum TextureType
        {
            Bullet,
            Player,
            Enemy
        ///Whatever texture there is, it goes here.
        };

    public:
        TextureHolder();
        ~TextureHolder();

        const sf::Texture& getTextureRef(TextureType S) const;

    private:
        ///Private Members
        std::vector<sf::Texture> Textures; ///Texture that holds the all bullets shot by enemies.

        ///Private Functions

        ///Set textures takes care of loading all of the textures that texture holder will give others to use.
        void setTextures();
};
