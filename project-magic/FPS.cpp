#include "FPS.hpp"
#include <sstream>
#include <string>

sf::Time FPS::Tick = sf::seconds(1.f);

FPS::FPS(sf::RenderWindow& R, unsigned F)
:FCount(F), C(), FT(), T(), RW(R)
{
    T.setPosition(RW.getSize().x - 30, RW.getSize().y - 30);
    Tick = sf::seconds(1.f);
	FT.loadFromFile("Resources/Fonts/sansation.ttf");
	T.setString("60");
	T.setFont(FT);
	T.setCharacterSize(18);
}

FPS::~FPS() {}

void FPS::draw()
{
    if((C.getElapsedTime() > Tick))
    { C.restart();  std::stringstream ss; ss << FCount; T.setString(ss.str()); ss.str(""); FCount = 1; }
    else
    { ++FCount; }

    RW.draw(T);
}
