#ifndef PEURAL_NEURALNETWORK_H
#define PEURAL_NEURALNETWORK_H

#include <vector>
#include "NeuralLayer.h"

class NeuralNetwork {

public:
    std::vector<NeuralLayer> layers;

    void addNeuralLayer(int layer_size, double (*activation)(Neuron));

    void addNeuralLayer(int input_size, int layer_size, double (*activation)(Neuron));

    double* evaluate(double* input);
};


#endif
