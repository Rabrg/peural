#include "NeuralNetwork.h"

void NeuralNetwork::addNeuralLayer(int layer_size, int (*activation)(Neuron)) {
    layers.push_back(*new NeuralLayer(layers.back().layer_size, layer_size, activation));
}

void NeuralNetwork::addNeuralLayer(int input_size, int layer_size, int (*activation)(Neuron)) {
    layers.push_back(*new NeuralLayer(input_size, layer_size, activation));
}
