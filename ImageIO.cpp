
#include "ImageIO.h"
#include "Util.h"
#include <iostream>
#include <fstream>

/**
 * Reads a binary pgm file into an 8 bit image
 *Magic number is p5 which indicates binary 8 bit grayscale image @see https://en.wikipedia.org/wiki/Netpbm_format
 *
 * @return image that was read
 */
ImageGrayscale8Bit ImageIO::readBinaryPGMFile(string filePath) {
    ifstream file(filePath.c_str(), ios::binary);
    if(! file.is_open())
    {
        cout << filePath << " could not be open." <<  endl;
        exit(0);
    }

    string magicNum;
    long width = 0;
    long height = 0;
    long maxPixelIntensity = 0;

    file >> magicNum;
    file >> width;
    file >> height;
    file >> maxPixelIntensity;

    if(magicNum != "P5")
    {
        cout << "Invalid pgm file";
        cout << "magic: " << magicNum <<  endl;
        cout << "width: " << width <<  endl;
        cout << "height: " << height <<  endl;
        cout << "max: " << maxPixelIntensity << endl;
        exit(0);
    }
    ImageGrayscale8Bit image(width,height);
    int size = width * height;

    char c;
    getline(file,magicNum); //consume new line character

    bool error;

    for(int i = 0; i < size; i++){

        //read byte by byte and set pixel
        file.read(&c,1);
        unsigned char intensityValue = (unsigned char) c;
        image.setIntensity(i,intensityValue);
        error = file.eof();
        if(error){
            cout << "reached end of file while reading binary PGM" << endl;
            exit(1);
        }
    }

    file.close();

    return image;
}

/**
 * This method will read the entire mnist dataset in csv form
 * https://pjreddie.com/projects/mnist-in-csv/
 * @param filepath - the path to the csv file
 * @return a vector of all the images
 */
vector<ImageGrayscale8Bit> ImageIO::readMINSTCSV(string filepath) {
    ifstream infile(filepath);

    if(!infile.is_open())
        cout << "cannot open file" << endl;
    string line;
    char delim = ',';

    vector<ImageGrayscale8Bit> images;
    images.reserve(60000); //set initial capacity to 60,000 elements
    int lineCounter = 0;
    while(getline(infile,line)){
        cout << "reading mnist " << lineCounter << endl;
        vector<string> tokens = Util::split(line, delim);
        ImageGrayscale8Bit image(28,28);
        for(int i = 0; i < tokens.size();i++){
            string token = tokens[i];

            if(i == 0) //label
            {
                continue;
            }
            //the rest are pixels.
            int integer = stoi(token);
            unsigned char intensity = (unsigned char) integer;
            image.setIntensity((i-1),intensity);
        }
        images.push_back(image);
        lineCounter++;
    }
    return images;

}

/**
 * Writes an 8 bit grayscale image to a binary 8bit pgm file.
 * Magic number is p5 which indicates binary 8 bit grayscale image @see https://en.wikipedia.org/wiki/Netpbm_format
 *
 * @param filePath - that your want to save file to. Include the extension
 * @param img - the image file
 */
void ImageIO::writeBinaryPGMFile(string filePath, const ImageGrayscale8Bit& img){
    ofstream file(filePath,ios::binary);
    file << "P5" << endl;
    file << img.getWidth() << " " << img.getHeight()<< endl;
    file << "255" << endl;

    int size = img.size();
    char* buff = new char[size];
    cout << endl;
    for(int i = 0; i < size; i++)
    {
        unsigned char uc = img.getIntensity(i);
        char c = (char)uc;
        buff[i] = c;
    }

    file.write(buff, size);
    file.close();

    delete[] buff;
}

/**
 * Reads an ASCII PGM file. magic number of P2
 * See https://en.wikipedia.org/wiki/Netpbm_format
 *
 * @param filePath
 * @return
 */
void ImageIO::writeASCIIPGMFile(string filePath, const ImageGrayscale8Bit &img) {
    ofstream file(filePath);
    file << "P2" << endl;
    file << img.getWidth() << " " << img.getHeight()<< endl;
    file << "255" << endl;

    int printNewLineCounter = 1;
    for(int i = 0; i < img.size(); i++)
    {
        unsigned int c = img.getIntensity(i);
        file << c;
        if(printNewLineCounter == img.getWidth()) {
            file << endl;
            printNewLineCounter = 1;
        }
        else {
            file << " ";
            printNewLineCounter++;
        }
    }
    file.close();
}

/**
 * Reads an ASCII PGM file. magic number of P2
 * See https://en.wikipedia.org/wiki/Netpbm_format
 *
 * @param filePath
 * @return
 */
ImageGrayscale8Bit ImageIO::readASCIIPGMFile(string filePath) {
    ifstream file(filePath.c_str(), ios::binary);
    if(! file.is_open())
    {
        cout << filePath << " could not be open." <<  endl;
        exit(0);
    }

    string magicNum;
    long width = 0;
    long height = 0;
    long maxPixelIntensity = 0;

    file >> magicNum;
    file >> width;
    file >> height;
    file >> maxPixelIntensity;

    if(magicNum != "P2")
    {
        cout << "Invalid pgm file";
        cout << "magic: " << magicNum <<  endl;
        cout << "width: " << width <<  endl;
        cout << "height: " << height <<  endl;
        cout << "max: " << maxPixelIntensity << endl;
        exit(0);
    }

    ImageGrayscale8Bit image(width,height);
    int size = width * height;

    for(int i = 0; i < size; i++)
    {
        unsigned int c;
        file >> c;
        unsigned char intensity = c;
        image.setIntensity(i,intensity);
    }
    file.close();
    return image;
}