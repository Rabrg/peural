#ifndef PEURAL_ACTIVATION_H
#define PEURAL_ACTIVATION_H


#include "Neuron.h"

class Activation {

public:
    static int relu(Neuron neuron);

    static int softmax(Neuron neuron);

private:
    Activation();
};


#endif
