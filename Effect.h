#ifndef EFFECT_H
#define EFFECT_H

class Effect{
    public:
        virtual float process(float input) = 0;

        virtual ~Effect();
    private:
};

#endif