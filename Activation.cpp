#include "Activation.h"
#include <cmath>

double Activation::relu(double i) {
    return std::fmax(i, 0.0);
}

double Activation::softmax(double i) {
    return exp(i);
}
