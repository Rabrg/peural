#include <iostream>
#include "NeuralLayer.h"
#include "Activation.h"
#include <iostream>

NeuralLayer::NeuralLayer(int input_size, int layer_size, double (*activation)(double)) : input_size(input_size),
                                                                                         layer_size(layer_size),
                                                                                         activation(activation) {
    neurons = new Neuron *[input_size];
    for (int i = 0; i < input_size; i++) {
        neurons[i] = new Neuron(layer_size);
    }
}

double *NeuralLayer::forward(double *input) {
    std::cout << "starting forward neural layer input: " << input_size << " layer_size: " << layer_size << std::endl;
    auto output = new double[layer_size];

    for (int i = 0; i < layer_size; i++) {
        std::cout << "neuron: " << i << " started" << std::endl;

        Neuron *neuron = neurons[i];
        double value = neuron->forward(input);
        value += neuron->bias;

        output[i] = activation(value);
        std::cout << "neuron: " << i << " completed" << std::endl;
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
