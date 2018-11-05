#ifndef PEURAL_NEURALLAYER_H
#define PEURAL_NEURALLAYER_H

#include "Neuron.h"

class NeuralLayer {

public:
    int input_size;
    int layer_size;
    Neuron **neurons;

    double (*activation)(double);

    NeuralLayer(int input_size, int layer_size, double (*activation)(double));

    double* forward(double* input);
};


#endif
