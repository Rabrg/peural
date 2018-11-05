#ifndef PEURAL_ACTIVATION_H
#define PEURAL_ACTIVATION_H


#include "Neuron.h"

class Activation {

public:
    static double relu(double i);

    static double softmax(double u);

private:
    Activation();
};


#endif
