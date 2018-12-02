//
// Created by michael on 4/3/18.
//

#ifndef IMAGE_IMAGEIO_H
#define IMAGE_IMAGEIO_H

#include "ImageGrayscale8Bit.h"
using namespace std;
#include <string>
#include <sstream>
#include <vector>


class ImageIO{
public:
    static ImageGrayscale8Bit readBinaryPGMFile(string filePath);
    static void writeBinaryPGMFile(string filePath, const ImageGrayscale8Bit &img);

    static ImageGrayscale8Bit readASCIIPGMFile(string filePath);
    static void writeASCIIPGMFile(string filePath, const ImageGrayscale8Bit &img);

    static vector<ImageGrayscale8Bit> readMINSTCSV(string filepath);
};



#endif //IMAGE_IMAGEIO_H