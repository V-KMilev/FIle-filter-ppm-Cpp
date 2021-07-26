#pragma once

#include <inttypes.h> 
#include <cassert>

int getMaxColor();

template<class Value>
class Pixel {
    public:
        Value red = 0;
        Value green = 0;
        Value blue = 0;

        Pixel() {}

        Pixel(Value red, Value green, Value blue) {
            this -> red = red;
            this -> green = green;
            this -> blue = blue;
        }

        void fix() {
            red = colorFix(red);
            green = colorFix(green);
            blue = colorFix(blue);
        }

        Pixel<Value> operator * (const int value) {

            Pixel<Value> newPixel;

            newPixel.red =  this -> red * value;
            newPixel.green = this -> green * value;
            newPixel.blue = this -> blue * value;

            return newPixel; 
        }

        Pixel<Value>& operator /= (const int value) {

            this -> red /= value;
            this -> green /= value;
            this -> blue /= value;

            return *this; 
        }


        Pixel<Value>& operator += (const Pixel<Value> &pixel) {

            this -> red += pixel.red;
            this -> green += pixel.green;
            this -> blue += pixel.blue;

            return *this; 
        }

    private:
        Value colorFix(Value color) {
            
            int MAX_COLOR_VALUE = getMaxColor();

            assert(MAX_COLOR_VALUE>0);
            
            if (color > MAX_COLOR_VALUE) { color = MAX_COLOR_VALUE; }
            else if (color < 0) { color = 0; }
            
            return color;
        }
};