#ifndef VOLUME_H
#define VOLUME_H
#include "Effect.h"

class Volume : public Effect{
    public:
        // constrcutor
        Volume(float factor);
        
        // destructor
        ~Volume();

        float process(float input) override;
    
        private:
        // volume multiplication factor
        float factor; 
};

#endif