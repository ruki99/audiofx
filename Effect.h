#ifndef EFFECT_H
#define EFFECT_H
#include <cstdint>

class Effect{
    public:
        virtual float process(int16_t input) = 0;

        virtual ~Effect();
    private:
};

#endif