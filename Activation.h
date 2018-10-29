#ifndef PEURAL_ACTIVATION_H
#define PEURAL_ACTIVATION_H


#include "Neuron.h"

class Activation {

public:
    static double relu(Neuron neuron);

    static double softmax(Neuron neuron);

private:
    Activation();
};


#endif
