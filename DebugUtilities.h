//
// Created by michael on 4/27/2018.
//

#ifndef IMAGE_DEBUGUTILITIES_H
#define IMAGE_DEBUGUTILITIES_H

#include <string>
/**
 * This class if for static debugging methods.
 */
class DebugUtilities{
public:
    static bool writeHistogramDataToCSVFile(ImageGrayscale8Bit img, std::string filePath);
};
#endif //IMAGE_DEBUGUTILITIES_H
