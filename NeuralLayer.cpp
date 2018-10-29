#include "NeuralLayer.h"

NeuralLayer::NeuralLayer(int input_size, int layer_size, double (*activation)(Neuron)) : input_size(input_size),
                                                                                      layer_size(layer_size),
                                                                                      activation(activation) {
    neurons = new Neuron *[layer_size];
}
