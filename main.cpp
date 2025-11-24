#include "Effect.h"
#include "Volume.h"
#include <cstdint>
#include <iostream>
#include <string>

const int HEADER_SIZE = 44;

int main(int argc, char* argv[]);

int main(int argc, char* argv[]){

    if (argc != 4){
        std::cout << "usage ./AudioFilter input.wav output.wav <volume factor>" << std::endl;
        return 1;
    }

    FILE *input = fopen(argv[1], "r");
    if (input == NULL){
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float vol_factor = std::stof(argv[3]);

    // Copy header from input file to output file
    uint8_t header[HEADER_SIZE]; // array of bytes to store 44 byte header
    fread(header, HEADER_SIZE, 1, input); // read header from input file
    fwrite(header, HEADER_SIZE, 1, output); // write header to output file

    // Read samples from input file and write updated data to output file
    // How? Loop through input till eof
    // for each 2 byte sample, read into memory, update vol and write to output

    Effect* myFX = new Volume(vol_factor);
    int16_t sample;

    // Read single sample from input into buffer while there are samples left to read
    while (fread(&sample, sizeof(int16_t), 1, input) != 0){
        // Update volume of sample
        sample = myFX->process(sample);

        // Write updated sample to new file
        fwrite(&sample, sizeof(int16_t), 1, output);
    }

    // Close files
    fclose(input);
    fclose(output);

    delete myFX;

    return 0;
}
