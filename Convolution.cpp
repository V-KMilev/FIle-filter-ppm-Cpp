
#include <iostream>
#include <sstream>
#include <vector>
#include <omp.h>

#include "Convolution.h"

using namespace std;

Convolution::Convolution(Image &image) : image(image) {}

Pixel<uint8_t> Convolution::pixelFilter(const std::vector<std::vector<int>> &_kernel, int pixel_X, int pixel_Y, int kernel_center, int type) {

    Pixel<int> f_pixel;

    int div = 0;

    // #pragma omp parallel for
    for (int row = -kernel_center; row <= kernel_center; row++) {
        for (int column = -kernel_center; column <= kernel_center; column++) {

            if(pixel_Y + row >= image.y || pixel_Y + row < 0
                || pixel_X + column >= image.x || pixel_X + column < 0) {
                continue;
            }

            const int offset = (pixel_Y + row) * image.x + (pixel_X + column);
            
            div += _kernel[kernel_center + column][kernel_center + row];
            
            Pixel<int> f_pixel_INT(
                image.pixels[offset].red, 
                image.pixels[offset].green, 
                image.pixels[offset].blue
            );

            f_pixel += (f_pixel_INT * _kernel[kernel_center + column][kernel_center + row]);
        }
    }

    if (type == f_Sharpen_3x3 || type == f_Sobel_0 || type == f_Sobel_1 ) { 
        f_pixel.fix(); 
        return Pixel<uint8_t>(f_pixel.red, f_pixel.green, f_pixel.blue);
    }
    else {
        f_pixel /= div;
        return Pixel<uint8_t>(f_pixel.red, f_pixel.green, f_pixel.blue);
    }
}

Pixel<uint8_t> Convolution::boxPixelFilter(int scale_X, int scale_Y, int pixel_X, int pixel_Y) {

    Pixel<int> f_pixel;

    int start_X = (pixel_X - scale_X / 2) >= 0 ? (pixel_X - scale_X / 2) : 0;
    int start_Y = (pixel_Y - scale_Y / 2) >= 0 ? (pixel_Y - scale_Y / 2) : 0;

    int end_X = (pixel_X + scale_X / 2) < image.x ? (pixel_X + scale_X / 2) : image.x - 1;
    int end_Y = (pixel_Y + scale_Y / 2) < image.y ? (pixel_Y + scale_Y / 2) : image.y - 1;

    // #pragma omp parallel for
    for (int row = start_Y; row <= end_Y; row++) {
        for (int column = start_X; column <= end_X; column++) {

            const int offset = row * image.x + column;

            Pixel<int> f_pixel_INT(
                image.pixels[offset].red,
                image.pixels[offset].green,
                image.pixels[offset].blue
            );
            
            f_pixel += f_pixel_INT;
        }
    }

    f_pixel /= ((end_X - start_X + 1) * (end_Y - start_Y + 1));
    
    return Pixel<uint8_t>(f_pixel.red, f_pixel.green, f_pixel.blue); 
}

std::vector<std::vector<int>> Convolution::getFilter(std::vector<std::vector<int>>& _kernel, int type, bool& isBox) {

    if(type == f_o_identity) {
        _kernel = identity;

    } else if(type == f_Gaussian_Blur_3x3 ) {
        _kernel = gaussianBlur3x3;

    } else if(type == f_Sharpen_3x3) {
        _kernel = sharpen3x3;
        
    } else if(type == f_Gaussian_Blur_5x5) {
        _kernel = gaussianBlur5x5;

    } else if(type == f_Sobel_0) {
        _kernel = sobel_0;
    
    } else if(type == f_Sobel_1) {
        _kernel = sobel_1;
    
    }else {
        isBox = true;
    }

    return _kernel;
}

std::stringstream Convolution::getFilteredMatrix(int type, int scale_X, int scale_Y) {

    std::vector<std::vector<int>> _kernel;

    Pixel<uint8_t> f_pixel;

    std::stringstream ss;

    bool isBox = false;

    getFilter(_kernel, type, isBox);

    int kernel_size = (int) _kernel.size();
    int kernel_center = kernel_size / 2;

    // #pragma omp parallel for
    for (int row = 0; row < image.y; row++) {
        for (int column = 0; column < image.x; column++) {
            if(isBox) {
                f_pixel = boxPixelFilter(scale_X, scale_Y, column, row);
            } else {
                f_pixel = pixelFilter(_kernel, column, row, kernel_center, type); 
            }

            ss << int(f_pixel.red) << ' ' << int(f_pixel.green) << ' ' << int(f_pixel.blue) << '\n';
        }
    }

    return ss;
}
