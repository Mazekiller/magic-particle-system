#ifndef ITEM_HPP
#define ITEM_HPP

#include <SFML/Graphics/Drawable.hpp>

///Clase para los Items a usar, ya sean los items consumibles.
///Es una clase para todos los tipos de items, el como interpretar lo que hacen es trabajo de la clase player.
///Es necesario una pantalla y un estado de preparacion donde los sprites de los Items son visibles, asi como sus caracteristicas.


class Item : public sf::Drawable
{
    public:
        Item();
        ~Item();
        Item(const Item& other);
        Item& operator=(const Item& other);

        friend class Agnar;
        friend class Luce;

        enum ItemIdentifier
        {

        };

        enum SpecialAttack
        {

        };

    private:
        std::string Name;
        std::string Description;
        std::string StatDescription;

        float ManaModifier;
        float MagicResistanceModifier;
        float PowerModifier;
        SpecialAttack SA;

        bool StoryModify; ///True si es un item que modifica la historia del juego. Herencia?



};

#endif // ITEM_HPP
