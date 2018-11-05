#include <iostream>
#include "NeuralLayer.h"
#include "Activation.h"
#include <iostream>

NeuralLayer::NeuralLayer(int input_size, int layer_size, double (*activation)(double)) : input_size(input_size),
                                                                                         layer_size(layer_size),
                                                                                         activation(activation) {
    neurons = new Neuron *[layer_size];
    for (int i = 0; i < layer_size; i++) {
        neurons[i] = new Neuron(input_size);
    }
}

double *NeuralLayer::forward(double *input) {
    auto output = new double[layer_size];

    for (int i = 0; i < layer_size; i++) {
        Neuron *neuron = neurons[i];
        double value = neuron->forward(input);
        value += neuron->bias;

        output[i] = activation(value);
    }

    if (activation == Activation::softmax) {
        double sum = 0;
        for (int i = 0; i < layer_size; i++)
            sum += output[i];
        for (int i = 0; i < layer_size; i++)
            output[i] /= sum;
    }
    return output;
}
