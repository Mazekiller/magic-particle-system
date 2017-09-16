#include "Item.hpp"

Item::Item()
{
    //ctor
}

Item::~Item()
{
    //dtor
}

Item::Item(const Item& other)
{
    //copy ctor
}

Item& Item::operator=(const Item& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    return *this;
}
