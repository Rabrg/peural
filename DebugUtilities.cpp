#include "DebugUtilities.h"
#include <fstream>
#include <iostream>

using namespace std;
/**
 * Writes the image histogram to a csv file
 * 0, sum of intensities at level 0
 * 1, sum of intensities at level 1
 * 2, sum of intensities at level 2
 * 3, sum of intensities at level 3
 * .
 * .
 * .
 * 255, sum of intensities at level 255
 *
 * @param img - the image
 * @param filePath - the path that you want to write to
 * @return true if successful.
 */
bool DebugUtilities::writeHistogramDataToCSVFile(ImageGrayscale8Bit img, string filePath) {
    int x;
    ofstream outputFile(filePath);
    if(!outputFile.is_open()){
        cout << "unable to open output file" << endl;
        return false;
    }
    //each index represents an intensity value.
    //the number stored at the index represents the how many pixels are that intensity
    unsigned int a[256];
    for(int i = 0; i < 256; i++)
        a[i] = 0;
    //build histogram
    for(int i = 0; i < img.size(); i++){
        unsigned char intensity = img.getIntensity(i);
        int val = a[intensity];
        val++;
        a[intensity] = val;
    }

    //write to csv file
    for(int i = 0; i < 256; i++) {
        outputFile << i << "," << a[i] << endl;
    }
    outputFile.close();
    return true;
}
