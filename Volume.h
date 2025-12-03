#ifndef VOLUME_H
#define VOLUME_H
#include "Effect.h"
#include <cstdint>
#include <vector>

class Volume : public Effect{
    public:
        Volume(float factor);
        ~Volume();
        void process(std::vector<float>& input) override;
    
    private:
        // volume multiplication factor
        float m_factor; 
};

#endif