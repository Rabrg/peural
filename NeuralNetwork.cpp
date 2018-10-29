#include "NeuralNetwork.h"

NeuralNetwork NeuralNetwork::addNeuralLayer(int layer_size, Neuron *neurons, int (*activation)(Neuron)) {
    layers.push_back(*new NeuralLayer(layer_size, neurons, activation));
    return *this;
}
