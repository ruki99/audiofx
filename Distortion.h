#ifndef DISTORTION_H
#define DISTORTION_H
#include "Effect.h"
#include <vector>

class Distortion : public Effect {
    public:
        Distortion(float gain);
        ~Distortion();

        void process(std::vector<float>& input) override;


    private:
        float gain_m;
};


#endif