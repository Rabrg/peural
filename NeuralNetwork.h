#ifndef PEURAL_NEURALNETWORK_H
#define PEURAL_NEURALNETWORK_H

#include <vector>
#include "NeuralLayer.h"

class NeuralNetwork {

public:
    std::vector<NeuralLayer> layers;

    NeuralNetwork addNeuralLayer(int layer_size, Neuron *neurons, int (*activation)(Neuron));
};


#endif
