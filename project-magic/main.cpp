#include "Generator.hpp"
#include "FPS.hpp"
#include "PolarVector.hpp"
#include "EmitterDefinitions.hpp"
#include "AffectorDefinitions.hpp"
#include "LuaTools.hpp"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>

///Must force an override all trigonometry functions to make fully sure they always receive degrees.

#if 1
int main()
{
    ///This is gonna be the test case for the object Generator class.
    sf::RenderWindow window(sf::VideoMode(1300, 700), "Bullet Generator Testing");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    FPS fps(window);

    sf::Texture bullets;
    bullets.loadFromFile("Resources/Images/Bullets/RemadeBulletSheet.png");

    BasicPatterns::CircleEmitter TestEMT1(50, sf::seconds(1.f), Emitter::EmissionType::Gradual);
    ///Gradual stacks the not emitted bullets, when emission is resumed it emits all it didn't when paused.
    ///Must use a real timer (not an sf::Clock, to control properly), should also give the option to stack bullets while paused or not.

    //TestEMT1.setEmitterLifetime(sf::seconds(3.f));
    TestEMT1.ResumeEmission(); ///Emission is paused by default.
    TestEMT1.setOriginPoint(sf::Vector2f(400.f, 400.f));
    TestEMT1.setColorDistribution(Distribution<Bullet::BulletColor>(Bullet::BulletColor::Gray, Bullet::BulletColor::Silver));
    TestEMT1.setTypeDistribution(Distribution<Bullet::BulletType>(Bullet::BulletType::Eye));
    TestEMT1.setLinearSpeedDistribution(Distribution<float>(120.f));
    TestEMT1.setBulletLifetimeDistribution(Distribution<sf::Time>(sf::seconds(5.f)));
    TestEMT1.setRotationToSelfOnCreation(true);
    TestEMT1.setRadius(10.f);

    BasicPatterns::RoseEmitter TestEMT2(300, sf::seconds(1.f), Emitter::EmissionType::Instant, 5.f/7.f);
    TestEMT2.setClockwiseEmission(false); ///If false it doesn't set the rotation to self angles properly.
    //TestEMT2.setRange(90.f, 180.f);
    //TestEMT2.setPetals(8);
    TestEMT2.setRoseSize(10);
    TestEMT2.ResumeEmission();
    TestEMT2.setOriginPoint(sf::Vector2f(400.f, 400.f));
    TestEMT2.setColorDistribution(Distribution<Bullet::BulletColor>(Bullet::BulletColor::Gray, Bullet::BulletColor::Silver));
    TestEMT2.setTypeDistribution(Distribution<Bullet::BulletType>(Bullet::BulletType::Circle));
    TestEMT2.setLinearSpeedDistribution(Distribution<float>(90.f, 180.f));
    TestEMT2.setBulletLifetimeDistribution(Distribution<sf::Time>(sf::seconds(5.f)));
    TestEMT2.setRotationToSelfOnCreation(true);


    LuaStateHandle L;

    BasicPatterns::LuaScriptEmitter LuaEMT(200, sf::seconds(1.f), Emitter::EmissionType::Gradual, L, "Scripts/FlowerPetals.lua");
    LuaEMT.ResumeEmission();
    LuaEMT.setRange(0.f, 360.f);
    LuaEMT.setOriginPoint(sf::Vector2f(400.f, 400.f));
    LuaEMT.setColorDistribution(Bullet::BulletColor::Cyan);
    LuaEMT.setTypeDistribution(Bullet::BulletType::Circle);
    LuaEMT.setLinearSpeedDistribution(Distribution<float>(180.f));
    LuaEMT.setBulletLifetimeDistribution(Distribution<sf::Time>(sf::seconds(5.f)));


    RenderAffectors::TypeChangeAffector T(Bullet::BulletType::Star, sf::seconds(0.5f)); //Uses Distribution implicit conversion.
    RenderAffectors::ColorChangeAffector T2(Bullet::BulletColor::Green, sf::seconds(1.f));

    Generator CircleTest(bullets);
    //CircleTest.AddEmitter(TestEMT1);
    //CircleTest.AddEmitter(TestEMT2);
    CircleTest.AddAffector(T);
    CircleTest.AddAffector(T2);
    CircleTest.AddEmitter(LuaEMT);
    CircleTest.setBulletTypeTextureRects();


    window.setFramerateLimit(60);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            { window.close(); }

            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Space) )
            {
                if(TestEMT1.isEmitting() && TestEMT2.isEmitting())
                {
                    TestEMT1.PauseEmission(true);
                    TestEMT2.PauseEmission(true);
                    LuaEMT.PauseEmission(true);
                }
                else
                {
                    TestEMT1.ResumeEmission();
                    TestEMT2.ResumeEmission();
                    LuaEMT.ResumeEmission();
                }

            }

        }

        if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
        {
            sf::Vector2f MousePos(static_cast<float>(sf::Mouse::getPosition(window).x), static_cast<float>(sf::Mouse::getPosition(window).y));
            TestEMT1.setOriginPoint(MousePos);
            TestEMT2.setOriginPoint(MousePos + sf::Vector2f(20.f, 20.f));
            LuaEMT.setOriginPoint(MousePos);
        }

        CircleTest.debug();
        CircleTest.Update();


        window.clear();
        fps.draw();
        window.draw(CircleTest);
        window.display();
    }

    return 0;
}
#else

#include "LuaTools.hpp"

int main() ///Test code for random things.
{

    //Lua state.
    /**
    lua_State *L = luaL_newstate();

    luaL_openlibs(L); //Must pass the state to any lua call.

    luaL_dofile(L, "Scripts/testScript.lua");

    lua_getglobal(L, "foo");

    lua_pushnumber(L, 0.32);
    lua_pcall(L, 1, 1, 0);



    //lua_getglobal(L, "chan");
    float x = lua_tonumber(L, -1);
    lua_pop(L, -1);
    float y;

    if(!lua_isnil(L, -1))
    {
        y = lua_tonumber(L, -1);
    }


    std::cout << x << ", other value: " << y <<std::endl;
    **/

    /**
    The dofile call is a shorthand for:
    (L is the state)

    luaL_loadfile(L, "script.lua); //Returns a lua function.
    luaL_loadfile(L, "script.lua); //Returns a lua function.
    lua_pcall(L, 0, 0 ,0, 0);
    **/

    LuaStateHandle LH = LuaStateHandle();

    float x = LH.RunEmitterFormulaScript("Scripts/testScript.lua", 0.5f);

    std::cout << x << std::endl;


    return 0;

}

#endif




