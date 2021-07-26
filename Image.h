#pragma once

#include <vector>
#include <string>

#include "Pixel.h"

class Image {
    public:
        Image();

        std::string resolution;                                     // std::string(x + " " + y)
        std::string max_color_value;                                // std::string(COLOR_MAX_VALUE)
        
        int x;                                                      // int Width
        int y;                                                      // int Height
        
        int MAX_COLOR_VALUE;                                        // int COLOR_MAX_VLAUE

        std::vector<Pixel<uint8_t>> pixels;                         // Pixels: Pixel(uint8_t red, uint8_t green, uint8_t blue)
};