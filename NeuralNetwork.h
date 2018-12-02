#ifndef PEURAL_NEURALNETWORK_H
#define PEURAL_NEURALNETWORK_H

#include <vector>
#include <string>
#include "NeuralLayer.h"

class NeuralNetwork {

public:
    std::vector<NeuralLayer> layers;

    void addNeuralLayer(int layer_size, double (*activation)(double));

    void addNeuralLayer(int input_size, int layer_size, double (*activation)(double));

    double* evaluate(double* input);

    void loadParameters(const std::string path);

    void printParams();
};


#endif
