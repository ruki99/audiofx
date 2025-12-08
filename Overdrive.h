#ifndef OVERDRIVE_H
#define OVERDRIVE_H
#include "Effect.h"
#include <vector>

class Overdrive : public Effect {
    public:
        Overdrive(float drive_val);
        ~Overdrive();

        void process(std::vector<float>& input) override;


    private:
        float drive_val_m;
        float bias_m;
};


#endif