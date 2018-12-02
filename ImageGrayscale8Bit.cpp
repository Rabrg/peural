#include "ImageGrayscale8Bit.h"
#include <sstream>
#include <iostream>
#include <iomanip>

using namespace std;
//constructors
ImageGrayscale8Bit::ImageGrayscale8Bit(int width, int height){
    this->width = width;
    this->height = height;
    int size = width * height;
    pixels = new unsigned char[size];

    for(int i = 0; i < size; i++)
        pixels[i] = 0;

}
ImageGrayscale8Bit::ImageGrayscale8Bit(const ImageGrayscale8Bit &other) {
    this->width = other.width;
    this->height = other.height;
    pixels = new unsigned char[this->size()];
    for(int i = 0; i < this->size(); i++)
        pixels[i] = other.getIntensity(i);
}
ImageGrayscale8Bit::~ImageGrayscale8Bit(){
    delete pixels;
    pixels = nullptr;
}


//setters
unsigned char ImageGrayscale8Bit::getIntensity(int x, int y) const{
    int index = (y * this->width) + x;
    return this->pixels[index];
}
unsigned char ImageGrayscale8Bit::getIntensity(int index) const {
    return this->pixels[index];
}
void ImageGrayscale8Bit::setIntensity(int x, int y, unsigned char intensity){
    int index = (y * this->width) + x;
    this->pixels[index] = intensity;
}
void ImageGrayscale8Bit::setIntensity(int index, unsigned char intensity){
    pixels[index] = intensity;
}


//getters
int ImageGrayscale8Bit::getWidth() const {
    return this->width;
}
int ImageGrayscale8Bit::getHeight() const {
    return this->height;
}
int ImageGrayscale8Bit::size() const {
    return width * height;
}


//operations

/**
 * Can be used to turn a film negative into a positive print.
 * n(i) = 255 - i where i is the current intensity of the pixel
 */
void ImageGrayscale8Bit::negativeOperation() {
    for(int i = 0; i < this->size(); i++)
        this->setIntensity(i, 255 - this->getIntensity(i));
}

/**
 * Equalizes the histogram on the image. Uses the transform
 * T(r) = (L-1) *  [the integral of Pr(w) dw from 0 to r]
 *
 * where r is the current intensity level
 *       L is the max intensity value in this case "256"
 *       Pr(w) is the new probability function
 *
 *       The results of this operation is equivalent gimps equalize function
 *
 */
void ImageGrayscale8Bit::equalizeHistogramOperation() {

    //build histogram
    unsigned int hist[256];
    double oldProbability[256];
    double newProbability[256];

    for(int i = 0; i < 256; i++)
        hist[i] = 0;
    for(int i = 0; i < this->size(); i++)
    {
        unsigned char intensity = this->getIntensity(i);
        int val = hist[intensity];
        val++;
        hist[intensity] = val;
    }

    //build probabilities for each histogram pixel
    for(int i = 0; i < 256; i++)
    {
        oldProbability[i] = hist[i] / (this->size() * 1.0);
        //calculate new probability's with T(r) = (L-1) * integral(0,r, p(w), dw) where p(w) is the new probability function
        unsigned int sum = 0;
        for(int j = 0; j <= i; j++){
            sum += hist[j];
        }
        newProbability[i] = sum / (this->size() * 1.0);
    }

    //quantize new probability's
    unsigned char intensityChangeMap[256];
    for(int i = 0; i < 256; i++)
    {
        //intelligently round newProbability
        double newIntensity =  (256-1) * newProbability[i];
        newIntensity += .5;

        int newIntensityRound = (int)(newIntensity);
        unsigned char finalIntensity = reinterpret_cast<int&>(newIntensityRound);

        //now every pixel with intensity "i" should be set to intensity "newIntensity"
        //but we should just add this to a map and then we can do the transformation in one iteration
        intensityChangeMap[i] = newIntensity;
    }

    //set the pixels
    for(int i = 0; i < this->size(); i++)
    {
        unsigned char pixIntensity = this->getIntensity(i);
        //find new value in "map"
        unsigned char newIntensity = intensityChangeMap[pixIntensity];
        this->setIntensity(i, newIntensity);
    }
}

/**
 * Grabs best threshold value using otsu method, then performs the threshold
 */
void ImageGrayscale8Bit::otsuMethodOperation() {
    unsigned char t = this->otsuMethod();
    this->thresholdOperation(t);
}

/**
 * Picks the best threshold value by selecting the threshold value with the minimum weighted within class variance.
 * Works best with bimodal histograms
 * For detailed information on how it works read the readme or my paper at
 * https://github.com/Michael-Metz/image-processing
 * @return the threshold value
 */
unsigned char ImageGrayscale8Bit::otsuMethod() {
//build histogram
    unsigned int hist[256];
    double probability[256];

    for(int i = 0; i < 256; i++)
        hist[i] = 0;
    for(int i = 0; i < this->size(); i++)
    {
        unsigned char intensity = this->getIntensity(i);
        int val = hist[intensity];
        val++;
        hist[intensity] = val;
    }

    //build probabilities for each histogram intensity
    for(int i = 0; i < 256; i++)
        probability[i] = hist[i] / (this->size() * 1.0);

    //Now do otsu's method.
    double minVariance = 999999999999;
    int bestThreshold = 0;

    for(int t = 0; t < 256; t++)
    {
        double bgWeight, bgMean, bgVariance;
        double fgWeight, fgMean, fgVariance;

        bgWeight = bgMean = bgVariance = 0;
        fgWeight = fgMean = fgVariance = 0;

        //calculate weights for each class
        for(int i = 0; i <= t; i++)
            bgWeight += probability[i];
        for(int i = t+1; i < 256; i++)
            fgWeight += probability[i];


        //calculate the means for each class
        for(int i = 0; i <= t; i++)
            bgMean += (i * probability[i]) / bgWeight;
        for(int i = t+1; i < 256; i++)
            fgMean += (i * probability[i]) / fgWeight;


        //calculate the variances for each class
        for(int i = 0; i <= t; i++)
            bgVariance += ((i - bgMean) * (i - bgMean)) * (probability[i] / bgWeight);
        for(int i = t+1; i < 256; i++)
            fgVariance += ((i - fgMean) * (i - fgMean)) * (probability[i] / fgWeight);


        double weightedWithinClassVariance = (bgWeight * bgVariance) + (fgWeight * fgVariance);


        if(weightedWithinClassVariance < minVariance){
            minVariance = weightedWithinClassVariance;
            bestThreshold = t;
        }
    }
    return bestThreshold;
}

/**
 * Thresholds an image reducing to just two intentesity levels. pure white 255, and pure black 0
 *
 * f(x,y) = 0 if f(x,y) <= T   or  255 if T < f(x,y)
 * anything less than or equal to the threshold will become white
 * anything greater than the threshold will become black
 * @param threshold
 */
void ImageGrayscale8Bit::thresholdOperation(unsigned char threshold) {

    for(int i = 0; i < this->size(); i++)
    {
        if(this->getIntensity(i) <= threshold)
            this->setIntensity(i,0);
        else
            this->setIntensity(i,255);
    }
}
std::string ImageGrayscale8Bit::toString() {
    std::ostringstream oss;

    oss << "width: " << width;
    oss << "\nheight: " << height;
    return oss.str();
}

//operators

//TODO verify that these work...
//bool ImageGrayscale8Bit::operator==(const ImageGrayscale8Bit &other) const {
//    if(this->size() != other.size())
//        return false;
//    for (int i = 0; i < this->size(); ++i) {
//        if(this->getIntensity(i) != other.getIntensity(i))
//            return false;
//    }
//    return true;
//}
//bool ImageGrayscale8Bit::operator!=(const ImageGrayscale8Bit &other) const {
//    return !(this->operator==(other));
//}
////ImageGrayscale8Bit& ImageGrayscale8Bit::operator=(const ImageGrayscale8Bit &other) const {
////    if(this == &other)
////        return *this;
////    ImageGrayscale8Bit* img = new ImageGrayscale8Bit(other);
////    return *this;
////}

