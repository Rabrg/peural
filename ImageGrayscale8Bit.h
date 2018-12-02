#ifndef IMAGE_IMAGEGRAYSCALE8BIT_H
#define IMAGE_IMAGEGRAYSCALE8BIT_H

#include <string>

class ImageGrayscale8Bit{
private:
    unsigned char* pixels;
    int height;
    int width;

public:
    ImageGrayscale8Bit(int width, int height);
    ImageGrayscale8Bit(const ImageGrayscale8Bit &other);
    ~ImageGrayscale8Bit();

    //properties
    int getWidth() const;
    int getHeight() const;
    int size() const;

    //pixel getter and setters
    unsigned char getIntensity(int x, int y) const;
    unsigned char getIntensity(int index) const;
    void setIntensity(int x, int y, unsigned char intensity);
    void setIntensity(int index, unsigned char intensity);

    //operations
    void negativeOperation();
    void equalizeHistogramOperation();
    void otsuMethodOperation();
    void thresholdOperation(unsigned char threshold);

    //helpers
    unsigned char otsuMethod();

    std::string toString();

    bool operator==(const ImageGrayscale8Bit &other) const;
    ImageGrayscale8Bit& operator=(const ImageGrayscale8Bit &other) const;
    bool operator!=(const ImageGrayscale8Bit &other) const;
};
#endif //IMAGE_IMAGEGRAYSCALE8BIT_H
