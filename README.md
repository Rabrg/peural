# parrallel processing project

Example usage:
```cpp
    // The dimensions of the neural network
    const int INPUT_SIZE = 4;
    const int HIDDEN_LAYER_1_SIZE = 12;
    const int HIDDEN_LAYER_2_SIZE = 6;
    const int OUTPUT_SIZE = 3;

    // Constructing the neural network
    auto *network = new NeuralNetwork();
    network->addNeuralLayer(INPUT_SIZE, HIDDEN_LAYER_1_SIZE, Activation::relu);
    network->addNeuralLayer(HIDDEN_LAYER_2_SIZE, Activation::relu);
    network->addNeuralLayer(OUTPUT_SIZE, Activation::softmax);

    // TODO: Load weights

    // Evaluating the neural network with a set of inputs
    auto *evaluationInput = new double[INPUT_SIZE] { 1.5, 1.2, 5.3, 7.3 };
    network->evaluate(evaluationInput);
```

#### mnist

the mnist dataset is sourced from `https://pjreddie.com/projects/mnist-in-csv/`  originally it was realeased in a binary
format, but a nice lad  transferred it to a `csv` file format to make it easy to read

* `minstdriver.cpp` : is a simple program that illustrates how reading in the images.


you can look at it yourself and understand it but I will outline the key ideas

### follow these steps to use mnist

###### 1. import header files
 ```c++
#include "ImageGrayscale8Bit.h"
#include "ImageIO.h"
```

###### 2. read all images into a vector

```c++
    string infile = "mnist.csv"; //the path to the image csv file
    vector<ImageGrayscale8Bit> images = ImageIO::readMINSTCSV(infile);
```

###### 3. Do what you need to with the images
*here are some of the methods that will be useful for `ImageGrayscale8Bit`*

```c++
    //properties
    int getWidth() const;
    int getHeight() const;
    int size() const;

    //pixel getters
    unsigned char getIntensity(int x, int y) const;
    unsigned char getIntensity(int index) const;
```