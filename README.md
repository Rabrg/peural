# parrallel processing project

Example usage:
```cpp
    // The dimensions of the neural network
    const int INPUT_SIZE = 4;
    const int HIDDEN_LAYER_1_SIZE = 12;
    const int HIDDEN_LAYER_2_SIZE = 6;
    const int OUTPUT_SIZE = 3;

    // Constructing the neural network
    auto *network = new NeuralNetwork();
    network->addNeuralLayer(INPUT_SIZE, HIDDEN_LAYER_1_SIZE, Activation::relu);
    network->addNeuralLayer(HIDDEN_LAYER_2_SIZE, Activation::relu);
    network->addNeuralLayer(OUTPUT_SIZE, Activation::softmax);

    // TODO: Load weights

    // Evaluating the neural network with a set of inputs
    auto *evaluationInput = new double[INPUT_SIZE] { 1.5, 1.2, 5.3, 7.3 };
    network->evaluate(evaluationInput);
```