#include <iostream>
#include "Neuron.h"

Neuron::Neuron(int input_size) : input_size(input_size) {
    weights = new double[input_size];
    bias = 0;
}

double Neuron::forward(double *input) {
    double sum = 0;
    for (int i = 0; i < input_size; i++) {
        sum += weights[i] * input[i];
    }
    return 0;
}
