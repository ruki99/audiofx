#ifndef TREMOLO_H
#define TREMOLO_H
#include "Effect.h"
#include <vector>

class Tremolo : public Effect {
    public:
        Tremolo(float depth, float modFreq, uint32_t sampleRate);
        ~Tremolo();

        void process(std::vector<float>& input) override;


    private:
        float depth_m; // value between 0 and 1
        float modF_m; // modulation frequency, use value < 20Hz
        uint32_t sampleRate_m;
};


#endif