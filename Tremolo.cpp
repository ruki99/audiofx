#include "Tremolo.h"
#include <cmath>
#include <iostream>
#include <vector>

Tremolo::Tremolo(float depth, float modFreq, uint32_t sampleRate){
    depth_m = depth;
    modF_m = modFreq;
    sampleRate_m = sampleRate;
}

void Tremolo::process(std::vector<float>& input){

    for (std::size_t i = 0; i < input.size(); i++){

        float trem = 1 + (depth_m * (sin ( 2 * M_PI * i * (modF_m / sampleRate_m) ) ) );
        
        // normalize trem to remove possible distortion when sin term exceeds 1
        trem = trem / (1 + depth_m); 

        float processed = trem * input[i];
        input[i] = processed;
    }
}

Tremolo::~Tremolo(){

}