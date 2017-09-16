#pragma once

#include <random>
#include <chrono>

#include <SFML/System/Time.hpp>

///Define the Distribution class for int, unsigned int, float, double, sf::Time and maybe sf::Vector2f and PolarVector.
///Wraps around std::uniform_int_distribution and std::uniform_real_distribution to define the random.
///Define a random method in my math constants file.

///Define in all a unitary constructor, that receives only one parameter and returns that constant.
///Distributions must be used insed the emitters based on need to parametrize them.

///It's possible that there will be a need for a new random generator engine, since the std one doesn't fit my purposes.


template <typename T>
struct Distribution
{
};

template <>
struct Distribution<int>
{
    typedef int Type;

    public:
        Distribution(Type unique) ///Constructs the distribution as a constant value returner.
         :min(unique)
         ,max(unique)
        {}

        Distribution(Type Min, Type Max)
         :min(Min)
         ,max(Max)
        {}

        Type min;
        Type max;

        Type uniform() const ///Returns a random of the distribution.
        {
            std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());
            std::uniform_int_distribution<Type> distribution(min,max);
            return distribution(generator);
        }
};

template <>
struct Distribution<unsigned>
{
    typedef unsigned Type;

    public:
        Distribution(Type unique) ///Constructs the distribution as a constant value returner.
         :min(unique)
         ,max(unique)
        {}

        Distribution(Type Min, Type Max)
         :min(Min)
         ,max(Max)
        {}

        Type min;
        Type max;

        Type uniform() const ///Returns a random of the distribution.
        {
            std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());
            std::uniform_int_distribution<Type> distribution(min,max);
            return distribution(generator);
        }
};

template <>
struct Distribution<float>
{
    typedef float Type;

    public:
        Distribution(Type unique) ///Constructs the distribution as a constant value returner.
         :min(unique)
         ,max(unique)
        {}

        Distribution(Type Min, Type Max)
         :min(Min)
         ,max(Max)
        {}

        Type min;
        Type max;

        Type uniform() const ///Returns a random of the distribution.
        {
            std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count()); //Time is the random seed.
            std::uniform_real_distribution<Type> distribution(min,max);
            return distribution(generator);
        }
};

template <>
struct Distribution<double>
{
    typedef double Type;

    public:
        Distribution(Type unique) ///Constructs the distribution as a constant value returner.
         :min(unique)
         ,max(unique)
        {}

        Distribution(Type Min, Type Max)
         :min(Min)
         ,max(Max)
        {}

        Type min;
        Type max;

        Type uniform() const ///Returns a random of the distribution.
        {
            std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());
            std::uniform_real_distribution<Type> distribution(min,max);
            return distribution(generator);
        }

};

template <>
struct Distribution<sf::Time>
{
    typedef sf::Time Type;

    public:
        Distribution(Type unique) ///Constructs the distribution as a constant value returner.
         :min(unique)
         ,max(unique)
        {}

        Distribution(Type Min, Type Max)
         :min(Min)
         ,max(Max)
        {}

        Type min;
        Type max;

        Type uniform() const ///Returns a random of the distribution.
        {
            std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());
            std::uniform_real_distribution<float> distribution(min.asSeconds(), max.asSeconds());
            return sf::seconds(distribution(generator));
        }

};

template <>
class Distribution<Bullet::BulletColor>
{
    typedef Bullet::BulletColor Type;

    public:
        Distribution(Type unique) ///Constructs the distribution as a constant value returner.
         :min(unique)
         ,max(unique)
        {
            unsigned m1 = static_cast<unsigned>(min);
            unsigned m2 = static_cast<unsigned>(max);

            if(m1 > m2) ///This is to handle color codes, to make sure they are in order.
            {
                Type temp = max;
                max = min;
                min = temp;
            }

        }

        Distribution(Type Min, Type Max)
         :min(Min)
         ,max(Max)
        {
            unsigned m1 = static_cast<unsigned>(min);
            unsigned m2 = static_cast<unsigned>(max);

            if(m1 > m2) ///This is to handle color codes, to make sure they are in order.
            {
                Type temp = max;
                max = min;
                min = temp;
            }
        }

        Type min;
        Type max;

        Type uniform() const ///Returns a random of the distribution.
        {
            unsigned m1 = static_cast<unsigned>(min);
            unsigned m2 = static_cast<unsigned>(max);

            std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());
            std::uniform_int_distribution<unsigned> distribution(m1,m2);
            return static_cast<Type>(distribution(generator));
        }

};


template <>
class Distribution<Bullet::BulletType>
{
    typedef Bullet::BulletType Type;

    public:
        Distribution(Type unique) ///Constructs the distribution as a constant value returner.
         :min(unique)
         ,max(unique)
        {
            unsigned m1 = static_cast<unsigned>(min);
            unsigned m2 = static_cast<unsigned>(max);

            if(m1 > m2) ///This is to handle color codes, to make sure they are in order.
            {
                Type temp = max;
                max = min;
                min = temp;
            }

        }

        Distribution(Type Min, Type Max)
         :min(Min)
         ,max(Max)
        {
            unsigned m1 = static_cast<unsigned>(min);
            unsigned m2 = static_cast<unsigned>(max);

            if(m1 > m2) ///This is to handle color codes, to make sure they are in order.
            {
                Type temp = max;
                max = min;
                min = temp;
            }
        }

        Type min;
        Type max;

        Type uniform() const ///Returns a random of the distribution.
        {
            unsigned m1 = static_cast<unsigned>(min);
            unsigned m2 = static_cast<unsigned>(max);

            std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());
            std::uniform_int_distribution<unsigned> distribution(m1,m2);
            return static_cast<Type>(distribution(generator));
        }

};
