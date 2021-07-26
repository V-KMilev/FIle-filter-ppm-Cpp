#pragma once

#include <vector>

#include "Pixel.h"
#include "Image.h"

class Convolution {
    public:
        Convolution(Image &image);

        std::stringstream getFilteredMatrix(int type, int scale_X, int scale_Y);
        
    private:
        Pixel<uint8_t> pixelFilter(const std::vector<std::vector<int>> &_kernel, int pixel_X, int pixel_Y, int kernel_center, int type);

        Pixel<uint8_t> boxPixelFilter(int scale_X, int scale_Y, int pixel_X, int pixel_Y);

        std::vector<std::vector<int>>  getFilter(std::vector<std::vector<int>>& _kernel, int type, bool& isBox);

        const std::vector<std::vector<int>> identity {
            {0, 0, 0},
            {0, 1, 0},
            {0, 0, 0}
        };


        const std::vector<std::vector<int>> gaussianBlur3x3 {
            {1, 2, 1},
            {2, 4, 2},
            {1, 2, 2}
        };

        const std::vector<std::vector<int>> sharpen3x3 {
            {0, -1, 0},
            {-1, 5, -1},
            {0, -1, 0}
        };

        const std::vector<std::vector<int>> sobel_0 {
            {1, 2, 1},
            {0, 0, 0},
            {-1, -2, -1}
        };

        const std::vector<std::vector<int>> sobel_1 {
            {1, 0, -1},
            {2, 0, -2},
            {1, 0, -1}
        };

        const std::vector<std::vector<int>> gaussianBlur5x5 {
            {1, 4, 6, 4, 1},
            {4, 16, 24, 16, 4},
            {6, 24, 36, 24, 6},
            {4, 16, 24, 16, 4},
            {1, 4, 6, 4, 1}
        };

        private:
            Image &image;
};

enum filters {
    f_o_identity = 0,
    f_Gaussian_Blur_3x3 = 1,
    f_Sharpen_3x3 = 2,
    f_Gaussian_Blur_5x5 = 3,
    f_Sobel_0 = 4,
    f_Sobel_1 = 5

};