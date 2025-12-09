#include "Distortion.h"
#include <iostream>
#include <vector>

Distortion::Distortion(float gain){
    gain_m = gain;
}

void Distortion::process(std::vector<float>& input){

    for (std::size_t i = 0; i < input.size(); i++){

        float processed = input[i] * gain_m;
        if (processed > 0.6) {
            processed = 0.6;
        } else if (processed < -0.6) {
            processed = -0.6;
        }

        input[i] = processed;
    }

}

Distortion::~Distortion(){

}