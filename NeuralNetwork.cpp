#include "NeuralNetwork.h"
#include <iostream>
#include <fstream>

void NeuralNetwork::addNeuralLayer(int layer_size, double (*activation)(double)) {
    layers.push_back(*new NeuralLayer(layers.back().layer_size, layer_size, activation));
}

void NeuralNetwork::addNeuralLayer(int input_size, int layer_size, double (*activation)(double)) {
    layers.push_back(*new NeuralLayer(input_size, layer_size, activation));
}

double *NeuralNetwork::evaluate(double *input) {
    double *value = input;
    for (auto &layer: layers) {
        value = layer.forward(value);
    }
    return value;
}

void NeuralNetwork::loadParameters(const std::string path) {
    std::ifstream in;
    in.open(path);

    int layer_count;
    in >> layer_count;

    for (int layer_index = 0; layer_index < layer_count; layer_index++) {
        int input_size, hidden_size;
        in >> input_size >> hidden_size;

        auto **layer_weights = new double *[input_size];
        for (int i = 0; i < input_size; ++i)
            layer_weights[i] = new double[hidden_size];

        auto *layer_biases = new double[hidden_size];

        for (int i = 0; i < input_size; i++) {
            for (int j = 0; j < hidden_size; j++) {
                in >> layer_weights[i][j];
            }
        }

        for (int j = 0; j < hidden_size; j++) {
            in >> layer_biases[j];
        }

        for (int i = 0; i < hidden_size; i++) {
            auto neuron = layers[layer_index].neurons[i];
            for (int j = 0; j < input_size; j++) {
                double weight = layer_weights[j][i];
//                std::cout << weight << std::endl;
                neuron->weights[j] = weight;
            }
            neuron->bias = layer_biases[i];
        }
    }
    in.close();
}

void NeuralNetwork::printParams() {
    for (int i = 0; i < layers.size(); i++) {
        auto layer = layers[i];
        int layer_size = layer.layer_size;
        int input_size = layer.input_size;
        for (int j = 0; j < layer_size; j++) {
            auto neuron = layer.neurons[j];
            for (int k = 0; k < input_size; k++) {
                std::cout << neuron->weights[k] << " ";
            }
            std::cout << std::endl;
            std::cout << neuron->bias << std::endl;
        }
    }
}
