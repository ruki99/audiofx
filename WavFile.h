#ifndef WAVFILE_H
#define WAVFILE_H
#include <cstdint>
#include <string>
#include <vector>

class WavFile{
    public:
        // constructor
        WavFile(const std::string& filename);
        
        // destructor
        ~WavFile();

        // for saving processed audio back into a wav file
        void save(const std::string& outputFilename, const std::vector<float>& processedAudio);

        // Used in main for getting converted audio for effects processing
        std::vector<float>& getAudio();

        uint16_t getAudioFmat() const;
        uint16_t getNumChannels() const;
        uint32_t getSampleRate() const;
        uint16_t getBitsPerSample() const;
        uint32_t getSubchunk2Size() const;

    private:
        std::vector<float> audioData_m; // float data written to by void conversion function
        std::vector<uint8_t> headerBuffer_m; // hold original header data to write to processed audio

        // .wav header data
        uint16_t audioFmat_m; // byte 20-21: audio fmat
        uint16_t numChannels_m; // byte 22-23: num channels
        uint32_t sampleRate_m; // byte 24-27: sample rate
        uint16_t bitsPerSample_m; // byte 34-35: bits per sample
        uint32_t Subchunk2Size_m; // byte 40-43: Subchunk2Size (total no. of bytes of audio data)

        void convertIntToFloat(const std::vector<int16_t>& input);
};

#endif