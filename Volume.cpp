#include "Volume.h"
#include <iostream>


Volume::Volume(float factor) : m_factor(factor){

}

void Volume::process(std::vector<float>& input){

    //std::cout << "Factor is: " << m_factor << std::endl;
    for(std::size_t i = 0; i < input.size(); i++){
        input[i] *= m_factor;
    }
}

Volume::~Volume(){
    
}