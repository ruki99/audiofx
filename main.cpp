#include "Effect.h"
#include "Volume.h"
#include "Bitcrusher.h"
#include "WavFile.h"
#include <iostream>
#include <string>

int main(int argc, char* argv[]);

int main(int argc, char* argv[]){

    // args for vol
    // if (argc != 4){
    //     std::cout << "usage ./AudioFX input.wav output.wav <volume factor>" << std::endl;
    //     return 1;
    // }

    // args for bitcrusher
    if (argc != 5){
        std::cout << "usage ./AudioFX input.wav output.wav <resolution factor> <sample rate factor>" << std::endl;
        return 1;
    }

    WavFile wav(argv[1]);
    std::vector<float>& buffer = wav.getAudio();

    // testing main with volume
    // float vol_factor = std::stof(argv[3]);
    // Effect* volFX = new Volume(vol_factor);
    // volFX->process(buffer);
    // wav.save(argv[2], buffer);
    // delete volFX;

    // testing main with bitcrusher
    int res = std::stof(argv[3]);
    int rate = std::stof(argv[4]);
    Effect* BitcrusherFX = new Bitcrusher(res, rate);
    BitcrusherFX->process(buffer);
    wav.save(argv[2], buffer);
    delete BitcrusherFX;

    return 0;
}
