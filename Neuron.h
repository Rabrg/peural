#ifndef PEURAL_NEURON_H
#define PEURAL_NEURON_H


class Neuron {

public:
    int input_size;
    int *weights;
    int bias;

    Neuron(int input_size, int *weights, int bias);
};


#endif
