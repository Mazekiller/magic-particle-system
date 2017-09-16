#pragma once

#include "Emitter.hpp"

///This is to have some Separation of concerns, since the attributes that a polar emitter needs for calculations are not the same as the ones a cartessian emitter needs.


class PolarEmitter : public Emitter
{
    ///Does not define create(), therefore it can't be instantiated.
    public:

        PolarEmitter(const unsigned amount, const sf::Time& EmissionTime);
        PolarEmitter(const unsigned amount, const sf::Time& EmissionTime, EmissionType EM);

        void setRange(const float start, const float end);
        void setRotationToSelfOnCreation(const bool b);

        void setClockwiseEmission(const bool CE);

    protected:

        mutable bool isSelfRotationSet;

        mutable bool hasClockwiseEmission;

        std::pair<float, float> Range;                    ///< Range for function emission, this class uses polar functions as default, so this is important.
        mutable float emitRadiusIndex;                         ///< For now we assume that there is only one emitRadius, but there can be more. 05/05/2015.
        mutable float emitAngleIndex;                    ///< emitAngleIndex is to keep track of the progress of the emission. It's dependant on emitRadius.

};

class CartessianEmitter : public Emitter ///Being cartessian doesn't mean that it can't use polar vectors inside it, it just means that it doesn't need a polar range and other variables.
{
    ///Will be implemented when cartessian emitters are needed for the first time. Could be used for streaming.
    ///Does not define create(), therefore it can't be instantiated.
    public:

    protected:

        ///Add variables that are necessary for the functioning of the code
};

