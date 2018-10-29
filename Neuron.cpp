#include "Neuron.h"

Neuron::Neuron(int input_size) : input_size(input_size) {
    weights = new double[input_size];
    bias = 0;
}
