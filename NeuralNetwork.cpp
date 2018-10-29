#include "NeuralNetwork.h"

void NeuralNetwork::addNeuralLayer(int layer_size, double (*activation)(Neuron)) {
    layers.push_back(*new NeuralLayer(layers.back().layer_size, layer_size, activation));
}

void NeuralNetwork::addNeuralLayer(int input_size, int layer_size, double (*activation)(Neuron)) {
    layers.push_back(*new NeuralLayer(input_size, layer_size, activation));
}

double *NeuralNetwork::evaluate(double *input) {
    for (auto const &layer: layers) {

    }
}
