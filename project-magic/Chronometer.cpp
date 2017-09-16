#include "Chronometer.hpp"


Chronometer::Chronometer(sf::Time initialTime)
  :m_state(STOPPED), m_time(initialTime)
{ if(initialTime != sf::Time::Zero) m_state = PAUSED; }

sf::Time Chronometer::add(sf::Time time)
{
    m_time += time;
    if (m_state == STOPPED) m_state = PAUSED;
    return getElapsedTime();
}

sf::Time Chronometer::reset(const bool start)
{
    sf::Time time = getElapsedTime();
    m_time = sf::Time::Zero;
    m_state = STOPPED;
    if (start) resume();
    return time;
}

sf::Time Chronometer::pause()
{
    if (isRunning())
    {
        m_state = PAUSED;
        m_time += m_clock.getElapsedTime();
    }
    return getElapsedTime();
}

void Chronometer::resume()
{
    if (!isRunning())
    {
        m_state = RUNNING;
        m_clock.restart();
    }
}

sf::Time Chronometer::toggle()
{
    if (isRunning()) pause();
    else resume();
    return getElapsedTime();
}

bool Chronometer::isRunning() const
{ return m_state == RUNNING; }

sf::Time Chronometer::getElapsedTime() const
{
    if (m_state == STOPPED) return sf::Time::Zero;

    if (m_state == RUNNING) return m_time + m_clock.getElapsedTime();

    if (m_state == PAUSED) return m_time;
}





