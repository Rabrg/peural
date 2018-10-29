#ifndef PEURAL_NEURALLAYER_H
#define PEURAL_NEURALLAYER_H

#include "Neuron.h"

class NeuralLayer {

public:
    int layer_size;
    Neuron *neruons;

    int (*activation)(int);

    NeuralLayer(int layer_size, Neuron *neruons, int (*activation)(int));
};


#endif
