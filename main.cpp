
#include <iostream>
#include "NeuralNetwork.h"
#include "Activation.h"
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <sys/time.h>


double input[4];

double fc1_weights[4][12] = {{5.0929511e-01,  -3.0172837e-01, -2.2357017e-02, 5.9731042e-01,  -1.0456806e-01,
                                                                                                               -5.3736037e-01, -1.3608459e-01, -9.1686711e-04, -5.5562276e-01, 3.2955125e-01,
                                                                                                                                                                                              -2.6553217e-01, -1.1610237e-01},
                             {1.4984435e-01,  -5.4846245e-01, -3.5532710e-01, 4.6415085e-01,  -2.0833399e-02
                                                                                              -
                                                                                              2.4433643e-01,   -4.7600347e-01, -3.1133786e-01, -3.7948981e-01, 8.5532910e-01,
                                                                                                                                                                               4.0550804e-01, -1.7621765e-01},
                             {2.7807575e-01,  -3.0888069e-01, 6.2640887e-01,  -2.5563601e-01, 7.5226516e-01,
                                                                                                               -3.1821758e-01, -5.2013546e-01, 7.2518283e-01,  4.1910881e-01,  -4.3115729e-01,
                                                                                                                                                                                              -1.4354758e-01, 6.2204814e-01},
                             {-5.0491863e-01, 2.9950029e-01,  3.5177970e-01,  -2.0253608e-01, 8.0625510e-01,
                                                                                                               5.8913630e-01,  -3.0924201e-02, 9.9984759e-01,  7.2954655e-02,  -3.8801673e-01,
                                                                                                                                                                                              1.8692620e-01,  1.0483487e+00}};

double fc1_bias[12] = {0.39067936, 0., -0.27959046, 0.3192086, -0.1695788, 0.,
                       0., -0.52781093, 0., 0.55035317, -0.13408968, -0.42141438};

double fc2_weights[12][6] = {{-0.02612523, 0.11411349,  0.7723868,   0.04718991,  -0.28230464, 0.0486067},
                             {0.04897541,  0.5093032,   -0.40925163, 0.23938668,  0.18138498,  0.21831745},
                             {-0.21716061, 0.37134218,  -0.46598437, 0.2902929,   -0.02804583, 0.8663456},
                             {0.6262601,   -0.54254407, 0.41600183,  0.41038904,  -0.3126608,  -0.42458832},
                             {0.13754006,  0.02052642,  -0.12427764, -0.30557203, 0.2916389,   0.91045994},
                             {-0.54458314, -0.5633166,  0.18898743,  0.56958854,  -0.4645583,  -0.10791126},
                             {-0.3144258,  -0.00254446, 0.27166915,  -0.5457181,  -0.16517395, -0.176417},
                             {-0.03632087, 0.4559201,   -0.6478921,  0.14673302,  -0.36646393, 0.82682896},
                             {0.14360803,  -0.20143,    -0.25837895, 0.26154977,  -0.05701905, 0.13749588},
                             {0.6882797,   -0.1120017,  1.3871204,   0.18649052,  0.11209279,  -0.49803},
                             {-0.04290314, -0.09604464, -0.25388423, 0.44339794,  -0.0576722,  -0.4115815},
                             {-0.3482072,  -0.51383615, -0.5918538,  0.2876789,   0.5527791,   0.8282614}};

double fc2_bias[6] = {0.46856505, -0.09392956, 0.66887, 0.09782694, 0., -0.2772889};

double output_weight[6][3] = {{8.7560958e-01,  4.7513786e-01,  -5.4133195e-01},
                              {-7.2714293e-01, -1.0581345e-03, -5.0447017e-01},
                              {1.4158480e+00,  7.5077271e-01,  -3.0135128e-01},
                              {-6.3749081e-01, 4.8761407e-01,  5.6499291e-02},
                              {1.3462436e-01,  -5.6505275e-01, -5.6812054e-01},
                              {-2.3274622e+00, -2.2532442e-01, 8.7870741e-01}};

double output[3] = {0.20044334, 0.22622249, -0.39760455};

/**
 * Parameters
 * -------------
 * threads - how many threads you want to run
 * iris or mnist - 1 or iris, 2 for mnist
 * num-evals - how many items do you want to classify
 */
int main(int arc, char *argv[]) {
    if (arc != 4) {
        std::cout << "we need 3 parameters passed see source code comment for descriptions" << std::endl;
        return 0;
    }
    int numThreads = std::stoi(argv[1]);
    int irisOrMnist = std::stoi(argv[2]);
    int numEvals = std::stoi(argv[3]);

    omp_set_num_threads(numThreads);
    // The dimensions of the neural network
    const int INPUT_SIZE = irisOrMnist == 1 ? 4 : 784;
    const int HIDDEN_LAYER_1_SIZE = irisOrMnist == 1 ? 12 : 392;
    const int HIDDEN_LAYER_2_SIZE = irisOrMnist == 1 ? 6 : 196;
    const int HIDDEN_LAYER_3_SIZE = 98;
    const int HIDDEN_LAYER_4_SIZE = 49;
    const int OUTPUT_SIZE = irisOrMnist == 1 ? 3 : 10;


    // Constructing the neural network
    auto *network = new NeuralNetwork();
    network->addNeuralLayer(INPUT_SIZE, HIDDEN_LAYER_1_SIZE, Activation::relu);
    network->addNeuralLayer(HIDDEN_LAYER_2_SIZE, Activation::relu);
    if(irisOrMnist == 2) {
        network->addNeuralLayer(HIDDEN_LAYER_3_SIZE, Activation::relu);
        network->addNeuralLayer(HIDDEN_LAYER_4_SIZE, Activation::relu);
    }
    network->addNeuralLayer(OUTPUT_SIZE, Activation::softmax);

    network->loadParameters("network.txt");

//    std::cout << "loaded params" << std::endl;
//
//    network->printParams();
    // Evaluating the neural network with a set of inputs

    auto *evaluationInput = new double[INPUT_SIZE];
    double start = omp_get_wtime();

    for (int i = 0; i < numEvals; i++) {
        auto *evaluationOutput = network->evaluate(evaluationInput);
    }


    double finish = omp_get_wtime();
    printf("Evalated %d Elapsed: %f\n", numEvals,(finish - start));

//    for (int i = 0; i < OUTPUT_SIZE; i++)
//        std::cout << output[i] << " ";
//
//    evaluationInput = new double[INPUT_SIZE] { 4.9, 3.0, 1.4, 0.2 };
//    output = network->evaluate(evaluationInput);
//    for (int i = 0; i < OUTPUT_SIZE; i++)
//        std::cout << output[i] << " ";
//
//    evaluationInput = new double[INPUT_SIZE] { 5.1, 3.5, 1.4, 0.2 };
//    output = network->evaluate(evaluationInput);
//    for (int i = 0; i < OUTPUT_SIZE; i++)
//        std::cout << output[i] << " ";
}
