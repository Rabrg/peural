#include "NeuralLayer.h"

NeuralLayer::NeuralLayer(int layer_size, Neuron *neruons, int (*activation)(Neuron)) : layer_size(layer_size),
                                                                                       neruons(neruons),
                                                                                       activation(activation) {}
