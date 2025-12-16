#include "Effect.h"
#include "Volume.h"
#include "Bitcrusher.h"
#include "Overdrive.h"
#include "Distortion.h"
#include "Tremolo.h"
#include "WavFile.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

int main(int argc, char* argv[]);

int main(int argc, char* argv[]){

    if (argc != 3){
        std::cout << "usage ./AudioFX input.wav output.wav" << std::endl;
        return 1;
    }


    WavFile wav(argv[1]);
    std::vector<float>& buffer = wav.getAudio();
    uint32_t sampleRate = wav.getSampleRate();

    std::cout << "Welcome to your digital pedalboard!\n" << std::endl;

    std::string helpMenu = "EFFECT         COMMAND\n"
                        "Bitcrusher     bitcrusher <resolution> <rate>\n"
                        "Distortion     distortion <gain>\n"
                        "Overdrive      overdrive <gain>\n"
                        "Tremolo        tremolo <depth> <modulation frequency>\n"
                        "NOTE: COMMANDS ARE CASE-SENSITIVE\n";
    std::cout << helpMenu << std::endl;
    std::cout << "enter 'help' to display the menu again.\n"
                "After applying effects, enter 'save' to exit." << std::endl;

    // main loop
    while (true){

        std::string usrCmd;
        std::cout << ">";
        std::getline(std::cin, usrCmd);
        std::stringstream ss(usrCmd);
        std::string word;

        std::vector<std::string> vec;

        while( std::getline(ss, word, ' ')){
            vec.push_back(word);
        }

        // checks for no input
        if (vec.size() == 0){
            continue;
        }

        // for (int i = 0; i < vec.size(); i++){
        //     std::cout << vec[i] << std::endl;
        // }

        if (vec[0] == "bitcrusher") {

            // check for valid number of args
            if (vec.size() != 3 ){
                std::cout << "incorrect number of arguments" << std::endl;
                return 1;
            }

            unsigned int res = std::stoi(vec[1]);
            unsigned int rate = std::stoi(vec[2]);
            Effect* BitcrusherFX = new Bitcrusher(res, rate);
            BitcrusherFX->process(buffer);
            delete BitcrusherFX;

        } else if (vec[0] == "distortion") {

            if (vec.size() != 2 ){
                std::cout << "incorrect number of arguments" << std::endl;
                return 1;
            }

            float gain = std::stof(vec[1]);
            Effect* DistortionFX = new Distortion(gain);
            DistortionFX->process(buffer);
            delete DistortionFX;

        } else if (vec[0] == "overdrive") {

            if (vec.size() != 2 ){
                std::cout << "incorrect number of arguments" << std::endl;
                return 1;
            }
            
            float drive = std::stof(vec[1]);
            Effect* OverdriveFX = new Overdrive(drive);
            OverdriveFX->process(buffer);
            delete OverdriveFX;

        } else if (vec[0] == "tremolo") {

            if (vec.size() != 3 ){
                std::cout << "incorrect number of arguments" << std::endl;
                return 1;
            }

            float depth = std::stof(vec[1]);
            float modFreq = std::stof(vec[2]);
            Effect* TremoloFX = new Tremolo(depth, modFreq, sampleRate);
            TremoloFX->process(buffer);
            delete TremoloFX;

        } else if (vec[0] == "save") {
            std::cout << "saving audio" << std::endl;
            wav.save(argv[2], buffer);
            break;
        } else if (vec[0] == "help") {
            std::cout << helpMenu<< std::endl;
        } else {
            std::cout << "invalid command. terminating program." << std::endl;
            continue;
        }

    }

    std::cout << "done." << std::endl;

    return 0;
}
