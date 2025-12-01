#include "WavFile.h"
#include <fstream>
#include <iostream>
#include <string>

const int HEADER_SIZE = 44;

WavFile::WavFile(const std::string& filename){
    // opening file
    std::ifstream file(filename, std::ios::binary);

    // checking if file opened successfuly
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file");
    }

    // Reading header data into the private member variables:
    file.seekg(20, std::ios::beg);
    file.read(reinterpret_cast<char*>(&audioFmat_m), sizeof(audioFmat_m));

    file.seekg(22, std::ios::beg);
    file.read(reinterpret_cast<char*>(&numChannels_m), sizeof(numChannels_m));

    file.seekg(24, std::ios::beg);
    file.read(reinterpret_cast<char*>(&sampleRate_m), sizeof(sampleRate_m));

    file.seekg(34, std::ios::beg);
    file.read(reinterpret_cast<char*>(&bitsPerSample_m), sizeof(bitsPerSample_m));

    file.seekg(40, std::ios::beg);
    file.read(reinterpret_cast<char*>(&Subchunk2Size_m), sizeof(Subchunk2Size_m));

    // calculate sample count
    int numSamples = Subchunk2Size_m / sizeof(uint16_t);

    // create and size vector 
    std::vector<int16_t> inputDataInt(numSamples);

    // read data into vector
    file.seekg(44, std::ios::beg);
    file.read(reinterpret_cast<char*>(inputDataInt.data()), Subchunk2Size_m);

    // convert to float
    convertIntToFloat(inputDataInt);

    file.close();
}

WavFile::~WavFile(){

}

 void WavFile::save(const std::string& outputFilename, const std::vector<float>& processedAudio){

 }

std::vector<float>& WavFile::getAudio(){
    return audioData_m;
}

uint16_t WavFile::getAudioFmat() const{
    return audioFmat_m;
}

uint16_t WavFile::getNumChannels() const {
    return numChannels_m;
}

uint32_t WavFile::getSampleRate() const {
    return sampleRate_m;
}

uint16_t WavFile::getBitsPerSample() const {
    return bitsPerSample_m;
}

uint32_t WavFile::getSubchunk2Size() const {
    return Subchunk2Size_m;
}

void WavFile::convertIntToFloat(const std::vector<int16_t>& input){

    audioData_m.resize(input.size());

    for (std::size_t i = 0; i < input.size(); i++) {
        audioData_m[i] = input[i] / 32768.0;
    }

}