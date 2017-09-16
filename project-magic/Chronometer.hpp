#include <SFML/System/Clock.hpp>

#pragma once

class Chronometer
{
    public:

        Chronometer(const sf::Time initialTime = sf::Time::Zero);

        sf::Time add(const sf::Time time);
        sf::Time reset(const bool start = false);

        sf::Time pause();
        void resume();

        sf::Time toggle();

        bool isRunning() const;
        sf::Time getElapsedTime() const;


        operator sf::Time() const
        { return getElapsedTime(); }

    private:
        enum  States{ STOPPED, RUNNING, PAUSED };
        sf::Time m_time;
        sf::Clock m_clock;
        States m_state;
};

