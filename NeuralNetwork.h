#ifndef PEURAL_NEURALNETWORK_H
#define PEURAL_NEURALNETWORK_H

#include <vector>
#include "NeuralLayer.h"

class NeuralNetwork {

public:
    std::vector<NeuralLayer> layers;

    void addNeuralLayer(int layer_size, Neuron *neruons, int (*activation)(int));
};


#endif
