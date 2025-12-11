#include "Effect.h"
#include "Volume.h"
#include "Bitcrusher.h"
#include "Overdrive.h"
#include "Distortion.h"
#include "Tremolo.h"
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
    // if (argc != 5){
    //     std::cout << "usage ./AudioFX input.wav output.wav <resolution factor> <sample rate factor>" << std::endl;
    //     return 1;
    // }

    // args for overdrive
    // if (argc != 4){
    //     std::cout << "usage ./AudioFX input.wav output.wav <drive_val>" << std::endl;
    //     return 1;
    // }

    // args for distortion
    // if (argc != 4){
    //     std::cout << "usage ./AudioFX input.wav output.wav <gain>" << std::endl;
    //     return 1;
    // }

    // args for tremolo
    if (argc != 5){
        std::cout << "usage ./AudioFX input.wav output.wav <depth> <modulation frequency>" << std::endl;
        return 1;
    }


    WavFile wav(argv[1]);
    std::vector<float>& buffer = wav.getAudio();
    uint32_t sampleRate = wav.getSampleRate();

    // testing main with volume

    // float vol_factor = std::stof(argv[3]);
    // Effect* volFX = new Volume(vol_factor);
    // volFX->process(buffer);
    // wav.save(argv[2], buffer);
    // delete volFX;

    // testing main with bitcrusher

    // int res = std::stof(argv[3]);
    // int rate = std::stof(argv[4]);
    // Effect* BitcrusherFX = new Bitcrusher(res, rate);
    // BitcrusherFX->process(buffer);
    // wav.save(argv[2], buffer);
    // delete BitcrusherFX;

    // testing main with Overdrive

    // float drive = std::stof(argv[3]);
    // Effect* OverdriveFX = new Overdrive(drive);
    // OverdriveFX->process(buffer);
    // wav.save(argv[2], buffer);
    // delete OverdriveFX;

    // testing main with Distortion

    // float gain = std::stof(argv[3]);
    // Effect* DistortionFX = new Distortion(gain);
    // DistortionFX->process(buffer);
    // wav.save(argv[2], buffer);
    // delete DistortionFX;

    // testing main with Tremolo

    float depth = std::stof(argv[3]);
    float modFreq = std::stof(argv[4]);
    Effect* TremoloFX = new Tremolo(depth, modFreq, sampleRate);
    TremoloFX->process(buffer);
    wav.save(argv[2], buffer);
    delete TremoloFX;

    return 0;
}
