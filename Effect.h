#ifndef EFFECT_H
#define EFFECT_H
#include <cstdint>
#include <vector>

class Effect{
    public:
        virtual void process(std::vector<float>& input) = 0;

        virtual ~Effect();
    private:
};

#endif