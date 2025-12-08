#include "Overdrive.h"
#include <cmath>
#include <iostream>

Overdrive::Overdrive(float drive_val){
    drive_val_m = drive_val;
    bias_m = 0.5;
}

void Overdrive::process(std::vector<float>& input){

    for (std::size_t i = 0; i < input.size(); i++){
        
        float processed;
        
        if (input[i] > 0){
            processed = tanh(input[i] * drive_val_m);
        } else {
            float drive_val_neg = drive_val_m * bias_m;
            processed = tanh(input[i] * drive_val_neg);
        }

        input[i] = processed;
    }

}

Overdrive::~Overdrive(){

}