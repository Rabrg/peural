cmake_minimum_required(VERSION 3.10)
project(peural)

include_directories(/usr/include/mpi/)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fopenmp")

set(CMAKE_C_COMPILER mpicc)
set(CMAKE_CXX_COMPILER mpicxx)

#this is for michaels mac
#set(CMAKE_C_COMPILER gcc-8)
#set(CMAKE_CXX_COMPILER g++-8)

set(CMAKE_CXX_STANDARD 14)

add_executable(peural main.cpp Neuron.cpp Neuron.h NeuralLayer.cpp NeuralLayer.h NeuralNetwork.cpp NeuralNetwork.h Activation.cpp Activation.h)
add_executable(mnist minstdriver.cpp ImageIO.cpp ImageGrayscale8Bit.cpp Util.cpp)