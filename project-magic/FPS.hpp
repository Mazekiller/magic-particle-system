#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "Chronometer.hpp"

#ifndef FPS_HPP
#define FPS_HPP


/**Una clase estupidamente simple, calcula el FrameRate del programa y lo imprime con sf::Text al fondo de la ventana.
  *Tiene una referencia al RenderWindow para preguntar respecto al tamano de la ventana y demas.
  *Usa un cronometro simple y una variable entera.
  *No tiene sentido crear mas de un objeto FPS.
  */

class FPS
{
    public:
        explicit FPS(sf::RenderWindow& R, unsigned F = 60);
        ~FPS();

        void draw();

    private:
        unsigned FCount;
        sf::Clock C;
        sf::Text T;
		sf::Font FT;

        static sf::Time Tick;

        sf::RenderWindow& RW;


};

#endif
