#include "Volume.h"
#include <iostream>


Volume::Volume(float factor){

    factor = factor;

}

float Volume::process(float input){

    return input*factor;

}