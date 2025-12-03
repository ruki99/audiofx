#ifndef BITCRUSHER_H
#define BITCRUSHER_H
#include "Effect.h"
#include <vector>

class Bitcrusher: public Effect{
    public:
        Bitcrusher(int res, int rate);
        ~Bitcrusher();
        void process(std::vector<float>& input) override;

    private:
        int res_m; // resolution factor
        int rate_m; // sample rate factor
        int counter_m;
        float curSample_m;

};

#endif