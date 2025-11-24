#ifndef VOLUME_H
#define VOLUME_H
#include "Effect.h"
#include <cstdint>

class Volume : public Effect{
    public:
        // constrcutor
        Volume(float factor);
        
        // destructor
        ~Volume();

        float process(int16_t input) override;
    
        private:
        // volume multiplication factor
        float m_factor; 
};

#endif