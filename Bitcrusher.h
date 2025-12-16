#ifndef BITCRUSHER_H
#define BITCRUSHER_H
#include "Effect.h"
#include <vector>

class Bitcrusher: public Effect{
    public:
        Bitcrusher(unsigned int bitDepth, unsigned int rate);
        ~Bitcrusher();
        void process(std::vector<float>& input) override;

    private:
        unsigned int bitDepth_m; 
        unsigned int rate_m; 
        unsigned int counter_m;
        float curSample_m;

};

#endif