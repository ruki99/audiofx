#include "Volume.h"
#include <iostream>


Volume::Volume(float factor) : m_factor(factor){

}

float Volume::process(int16_t input){

    //std::cout << "Factor is: " << m_factor << std::endl;
    return input * m_factor;

}

Volume::~Volume(){
    
}