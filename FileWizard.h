#pragma once

#include <vector>

#include "Pixel.h"
#include "Image.h"
 
 class FileWizard {
    public:
        FileWizard();

        Image fileLoaderP3(const char* input_file_name);        

        Image fileLoaderP6(const char* input_file_name);
        
        void fileWrite(std::stringstream& ss, Image& image);
 };