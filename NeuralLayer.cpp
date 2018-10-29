//
// Created by Ryan on 10/29/2018.
//

#include "NeuralLayer.h"

NeuralLayer::NeuralLayer(int layer_size, Neuron *neruons, int (*activation)(int)) : layer_size(layer_size),
                                                                                    neruons(neruons),
                                                                                    activation(activation) {}
