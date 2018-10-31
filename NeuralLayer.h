#ifndef PEURAL_NEURALLAYER_H
#define PEURAL_NEURALLAYER_H

#include "Neuron.h"

class NeuralLayer {

public:
    int input_size;
    int layer_size;
    Neuron **neurons;

    double (*activation)(Neuron);

    NeuralLayer(int input_size, int layer_size, double (*activation)(Neuron));
};


#endif
