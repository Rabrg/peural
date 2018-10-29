//
// Created by Ryan on 10/29/2018.
//

#include "NeuralNetwork.h"

void NeuralNetwork::addNeuralLayer(int layer_size, Neuron *neurons, int (*activation)(int)) {
    layers.push_back(*new NeuralLayer(layer_size, neurons, activation));
}
