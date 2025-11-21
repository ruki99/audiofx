#include "AudioFile.h"
#include "Effect.h"
#include "Volume.h"
#include <iostream>
#include <string>

int main(int argc, char* argv[]);

int main(int argc, char* argv[]){

    if (argc != 4){
        std::cout << "usage ./audiofx input.wav output.wav <volume factor>" << std::endl;
        return 1;
    }

    std::string input = argv[1];
    std::string output = argv[2];

    float vol_factor = std::stof(argv[3]);

    // create audiofile instance
    AudioFile<float> audioFile;
    bool isLoaded = audioFile.load(input);

    if (!isLoaded){
        std::cout << "failed to load input" << std::endl;
        return 1;
    }

    // create new volume object
    Effect* myFX = new Volume(vol_factor);

    auto& audioData = audioFile.samples[0];

    for (float& sample : audioData){
        sample = myFX->process(sample);
    }

    bool saved = audioFile.save(output);

    if (!saved){
        std::cout << "Error: couldn't save output" << std::endl;
        delete myFX;
        return 1;
    }

    delete myFX;

    return 0;
}
