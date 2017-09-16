#pragma once

#include "EmitterTypes.hpp"
#include "LuaTools.hpp"

///Define the emitters that will be actually used.
///Classes must allow distributions to be passed to them.

///Personalized emitters set several different settings as automatic, these settings can be overriden.

///Emitters will be categorized this way:
/**
  *Basic (Basic shapes used in all stages, like circles and multi-petal flowers or spirals)
  *Stage Specific

**/

namespace BasicPatterns
{
    class CircleEmitter : public PolarEmitter
    { ///Parametrizar cada emitter.
        public:
            friend class EmitterAffector; ///Friends are not inherited.

            CircleEmitter(const unsigned amount, const sf::Time& EmissionTime);
            CircleEmitter(const unsigned amount, const sf::Time& EmissionTime, EmissionType EM);

            void setRadius(const float r);

        private:

            float radius;
            virtual void create(const Generator& g) const;
    };

    class GapCircleEmitter : public PolarEmitter
    {
        public:
            friend class EmitterAffector;

        private:
            float GapSize;
            unsigned GapAmount;
    };

    ///This class automatically sets the range from 0 to 1800, which is what most polar roses need.
    class RoseEmitter : public PolarEmitter
    {
        public:
            friend class EmitterAffector; ///This class must always be friend.

            RoseEmitter(const unsigned amount, const sf::Time& EmissionTime, const float calculatedValue);
            RoseEmitter(const unsigned amount, const sf::Time& EmissionTime, const float calculatedValue, const unsigned RoseSize);

            RoseEmitter(const unsigned amount, const sf::Time& EmissionTime, EmissionType EM, const float calculatedValue);
            RoseEmitter(const unsigned amount, const sf::Time& EmissionTime, EmissionType EM, const float calculatedValue, const unsigned RoseSize);

            void setRoseCalculationValue(const float calcVal);
            void setRoseSize(const unsigned size);


        private:

            float k; ///Parameter for calculation of rose.
            unsigned roseSize;

            virtual void create(const Generator& g) const;
    };

    class FlowerEmitter : public PolarEmitter
    {
        public:
            friend class EmitterAffector;
            FlowerEmitter(const unsigned amount, const sf::Time& EmissionTime);
            FlowerEmitter(const unsigned amount, const sf::Time& EmissionTime, EmissionType EM);

            void setPetals(const unsigned Petals);
            void setFlowerSize(const unsigned size);

        private:
            unsigned petals;
            unsigned flowerSize;

            virtual void create(const Generator& g) const;

    };

    class LuaScriptEmitter : public PolarEmitter
    {
        public:
            friend class EmitterAffector;

            LuaScriptEmitter(const unsigned amount, const sf::Time& EmissionTime, EmissionType EM, LuaStateHandle& l, const std::string& path);

        private:
            LuaStateHandle& LuaRef;
            std::string scriptPath;

            virtual void create(const Generator& g) const;
    };

} //End of basic patterns

namespace StageOnePatterns
{

} //End of stage 1 patterns


namespace StageTwoPatterns
{

} //End of stage 2 patterns
