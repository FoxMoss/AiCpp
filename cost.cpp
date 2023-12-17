#include "neuron.hpp"
#include <cstdio>
#include <vector>

float NeuralNetwork::Evaluate() {
  float score = 0;

  float costs = 0;
  int costsLength = 0;

  for (float x = 0; x < 1; x += 0.05) {
    for (float y = 0; y < 1; y += 0.05) {
      starting[0]->value = x;
      starting[1]->value = y;

      starting[1]->updated = true;
      starting[0]->Update();

      if (x > y) {
        costs += PointCost({x, y}, {1, 0});
        costsLength++;
      } else {
        costs += PointCost({x, y}, {0, 1});
        costsLength++;
      }
    }
  }

  score = costs / costsLength;

  // printf("Score: %f\n", score);
  return score;
}

float NeuralNetwork::PointCost(std::vector<float> inputs,
                               std::vector<float> expectedOutputs) {
  if (inputs.size() != starting.size() ||
      expectedOutputs.size() != ending.size()) {
    printf("Data point did not line up with network");
    return -1;
  }

  for (int neuron = 0; neuron < starting.size(); neuron++) {
    starting[neuron]->value = inputs[neuron];
  }

  starting[0]->Update();

  float cost = 0;

  for (int neuron = 0; neuron < ending.size(); neuron++) {
    cost += NeuronCost(ending[neuron]->value, expectedOutputs[neuron]);
  }

  return cost;
}
float NeuralNetwork::NeuronCost(float gotValue, float expectedValue) {
  float error = gotValue - expectedValue;
  return error * error;
}
