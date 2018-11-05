#ifndef PEURAL_NEURON_H
#define PEURAL_NEURON_H


class Neuron {

public:
    int input_size;
    double *weights;
    double bias;

    Neuron(int input_size);

    double forward(double *input);
};


#endif
