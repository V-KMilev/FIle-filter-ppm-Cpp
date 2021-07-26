#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>

#include "FileWizard.h"

using namespace std;

static int MAX_COLOR_VALUE = 0;

int getMaxColor() {
    return MAX_COLOR_VALUE;
}

FileWizard::FileWizard() {}

Image FileWizard::fileLoaderP6(const char* input_file_name) {

    Image image;

    int index = 0;

    uint8_t red = 0;
    uint8_t green = 0;
    uint8_t blue = 0;

    //file read
    FILE *input_file;
    input_file = fopen(input_file_name, "rb");


    char buff[4];

    fgetc(input_file);
    fgetc(input_file);
    fgetc(input_file);

    fscanf(input_file, "%d %d\n", &image.x, &image.y);
    fscanf(input_file, "%d\n", &image.MAX_COLOR_VALUE);
    
    fgetc(input_file);

    image.resolution = std::to_string(image.x) + " " + std::to_string(image.y);
    image.max_color_value = std::to_string(image.MAX_COLOR_VALUE);

    MAX_COLOR_VALUE = image.MAX_COLOR_VALUE;

    image.pixels.resize(image.y*image.x);

    fread(&image.pixels[0].red, sizeof(Pixel<uint8_t>),image.x*image.y,input_file);
    fclose(input_file);

    return image;
}

Image FileWizard::fileLoaderP3(const char* input_file_name) {

    Image image;

    //file read
    std::ifstream input_file(input_file_name);

    if(!input_file.is_open()) {
    
        cout << "file not existing!" << endl;
        return image;    
    }

    input_file.seekg(0, ios::end);
    int64_t _length = input_file.tellg();
    input_file.seekg(0, ios::beg);

    std::vector<char> _buffer (_length);

    input_file.read(&_buffer[0], _length);
    input_file.close();

    // pixel sort
    char str[64];

    int lines_to_read = 2;
    int line_number = 0;

    int64_t buff_index = 0;
    int str_index = 0;

    int red = 0;
    int green = 0;
    int blue = 0;

    while(true) {

        if (line_number >= lines_to_read) {
            break;
        }
        // string maker  
        str[str_index] = _buffer[buff_index];
        
        // go to next buffer index
        buff_index++;
        // go to next string index
        str_index++;

        // finish string
        if(_buffer[buff_index -1] == '\n') {
            str[str_index -1] = '\0';
            
            if(line_number == 0) {
                
            // get resolution string, x and y and resize vec.pixels
            } else if (line_number == 1) {
                image.resolution = str;

                sscanf(str, "%d %d", &image.x, &image.y);
                lines_to_read = image.x * image.y + 3;
                
                image.pixels.resize(image.x * image.y);
            
            // get color_max_value string, COLOR_MAX_VALUE
            } else if (line_number == 2) {
                image.max_color_value = str;

                sscanf(str, "%d", &image.MAX_COLOR_VALUE);

                MAX_COLOR_VALUE = image.MAX_COLOR_VALUE;

            // add pixel to vec.pixels
            } else {
                sscanf(str, "%d %d %d", &red, &green, &blue);

                image.pixels[line_number - 3] = Pixel<uint8_t>(red, green, blue);
            }
            // got to next vec.pixels index
            line_number++;

            // reset string
            str_index = 0;
        }
    }
    return image;
}


void FileWizard::fileWrite(std::stringstream& ss, Image& image) {

    std::ofstream out_file;

    out_file.open("output1.ppm");

        if(out_file.is_open()) {

        out_file << "P3\n" + image.resolution + '\n' + image.max_color_value + '\n';

        out_file << ss.str();

    }
    out_file.close();
}