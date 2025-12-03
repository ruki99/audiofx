#include "Bitcrusher.h"
#include <cmath>
#include <iostream>

Bitcrusher::Bitcrusher(int res, int rate){
    res_m = res;
    rate_m = rate;
    counter_m = rate;
    curSample_m = 0.0f;

}

void Bitcrusher::process(std::vector<float>& input){

    for(std::size_t i = 0; i < input.size(); i++){
        
        if (counter_m < rate_m) {
            counter_m++;
        } else {
            curSample_m = input[i];
            counter_m = 0;
        }

        float processed = round(curSample_m * res_m) / res_m;
        input[i] = processed;
    }

}

Bitcrusher::~Bitcrusher(){
    
}