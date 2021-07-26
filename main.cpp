#include <iostream>
#include <sstream>
#include <ctime>

#include "Convolution.h"
#include "FileWizard.h"
#include "Image.h"

using namespace std;

int main(int argc, char** argv) {

    const char* input_file = "input.ppm";

    clock_t startTimeFR = clock();
    cout << "runing..." << endl;

    FileWizard test01_f;
    Image image = test01_f.fileLoaderP3(input_file);

    clock_t endTimeFR = clock();

    clock_t startTimeK = clock();

    //------------g------------
    // 0 -> identity
    // 1 -> gaussian Blur 3x3
    // 2 -> sharpen 3x3
    // 3 -> gaussian Blur 5x5
    // 4 -> sobel |
    // 5 -> sobel -
    // else -> box (x , y)
    //-------------------------

    Convolution test01_k(image);
    std::stringstream ss = test01_k.getFilteredMatrix(0, 37, 37);

    clock_t endTimeK = clock();
    
    clock_t startTimeFW = clock();

    test01_f.fileWrite(ss, image);

    clock_t endTimeFW = clock();

    clock_t clockTicksTakenFR = endTimeFR - startTimeFR;
    double timeInSecondsFR = clockTicksTakenFR / (double) CLOCKS_PER_SEC;

    clock_t clockTicksTakenK = endTimeK - startTimeK;
    double timeInSecondsK = clockTicksTakenK / (double) CLOCKS_PER_SEC;

    clock_t clockTicksTakenFW = endTimeFW - startTimeFW;
    double timeInSecondsFW = clockTicksTakenFW / (double) CLOCKS_PER_SEC;

    cout << "finished: " << endl << "T: " << timeInSecondsFR + timeInSecondsK + timeInSecondsFW << " FR: " <<  timeInSecondsFR
    << " C: " << timeInSecondsK << " FW: " << timeInSecondsFW << endl;
    
    return 0;
}