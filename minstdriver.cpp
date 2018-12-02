
#include <iostream>
#include "ImageGrayscale8Bit.h"
#include "ImageIO.h"

using namespace std;

void printUsage(){
    cout << "Usage: ./mnist infile outfile" << endl;
    cout << endl;
    cout << "Example: ./mnistdriver mnist.csv" << endl << endl;
}
int main(int arc, char *argv[]){
    //make sure one argument is passed when running the program from command line
    //remember first argument is the name of the program
    if (arc != 3) {
        printUsage();
        return 0;
    }
    //at this point
    //argv[1] is the path to the input file
    string infile = argv[1];
    string outfile = argv[2];

    vector<ImageGrayscale8Bit> images = ImageIO::readMINSTCSV(infile);
    for(int i = 0; i < images.size(); i++){
        string fn = outfile + to_string(i) + ".pgm";
        cout << "writing " << fn << endl;
        ImageIO::writeBinaryPGMFile(fn,images[i]);
    }

};