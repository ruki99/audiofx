#include "WavFile.h"
#include <fstream>
#include <iostream>
#include <string>

WavFile::WavFile(const std::string& filename){
    // opening file
    std::ifstream file(filename, std::ios::binary);

    // checking if file opened successfuly
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file");
    }

    headerBuffer_m.resize(44); // resize header buffer to hold all header chunks
    file.read(reinterpret_cast<char*>(headerBuffer_m.data()), 44); //store header into buffer

    // Reading header data into the private member variables:
    file.seekg(20, std::ios::beg);
    file.read(reinterpret_cast<char*>(&audioFmat_m), sizeof(audioFmat_m));

    if (audioFmat_m != 1) {
        std::cerr << "ERROR: Only PCM (uncompressed) files are supported." << std::endl;
        throw std::runtime_error("Compressed WAV");
    }

    file.seekg(22, std::ios::beg);
    file.read(reinterpret_cast<char*>(&numChannels_m), sizeof(numChannels_m));

    file.seekg(24, std::ios::beg);
    file.read(reinterpret_cast<char*>(&sampleRate_m), sizeof(sampleRate_m));

    file.seekg(34, std::ios::beg);
    file.read(reinterpret_cast<char*>(&bitsPerSample_m), sizeof(bitsPerSample_m));

    // error check for non 16-bit audio
    if (bitsPerSample_m != 16){
        std::cerr << "ERROR: only 16-bit WAV files are supported. This file is "
                  << bitsPerSample_m << "-bit." << std::endl;
        throw std::runtime_error("Invalid Bit Depth");
    }

    // Start looking after the standard header stuff (Byte 36)
    file.seekg(36, std::ios::beg);
    char chunkID[4];
    while (true){
        file.read(chunkID, 4);

        uint32_t currChunkSize;
        file.read(reinterpret_cast<char*>(&currChunkSize), 4);

        if (file.eof()) {
            throw std::runtime_error("Couldn't find 'data' chunk in WAV file");
        }

        if (chunkID[0] == 'd' && chunkID[1] == 'a' && chunkID[2] == 't' && chunkID[3] == 'a') {
            Subchunk2Size_m = currChunkSize;
            break;
        } else {
            file.seekg(currChunkSize, std::ios::cur);
        }
    }

    std::cout << "--- HEADER DEBUG ---" << std::endl;
    std::cout << "Sample Rate: " << sampleRate_m << std::endl;
    std::cout << "Bits Per Sample: " << bitsPerSample_m << std::endl;
    std::cout << "Data Size (Subchunk2): " << Subchunk2Size_m << " bytes" << std::endl;
    std::cout << "--------------------" << std::endl;

    // calculate sample count
    int numSamples = Subchunk2Size_m / sizeof(uint16_t);

    // create and size vector 
    std::vector<int16_t> inputDataInt(numSamples);

    // read data into vector
    file.read(reinterpret_cast<char*>(inputDataInt.data()), Subchunk2Size_m);

    // convert to float
    convertIntToFloat(inputDataInt);

    file.close();
}

WavFile::~WavFile(){

}

 void WavFile::save(const std::string& outputFilename, const std::vector<float>& processedAudio){
    // opening output file
    std::ofstream outFile(outputFilename, std::ios::binary);

    //writing to output file
    outFile.write(reinterpret_cast<const char*>(headerBuffer_m.data()), 44);

    std::vector<int16_t> float2int_buff;
    float2int_buff.resize(processedAudio.size());

    for (std::size_t i = 0; i < processedAudio.size(); i++) {
        float temp = processedAudio[i] * 32767.0f;
        if(temp > 32767) {
            temp = 32767;
        }
        if (temp < -32768) {
            temp = -32768;
        }
        float2int_buff[i] = static_cast<int16_t>(temp);
    }

    outFile.write(reinterpret_cast<const char*>(float2int_buff.data()), float2int_buff.size() * sizeof(int16_t));

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