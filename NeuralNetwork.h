#ifndef PEURAL_NEURALNETWORK_H
#define PEURAL_NEURALNETWORK_H

#include <vector>
#include "NeuralLayer.h"

class NeuralNetwork {

public:
    std::vector<NeuralLayer> layers;

    NeuralNetwork addNeuralLayer(int layer_size, int (*activation)(Neuron));

    NeuralNetwork addNeuralLayer(int input_size, int layer_size, int (*activation)(Neuron));
};


#endif
