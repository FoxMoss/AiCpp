#include "neuron.hpp"
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <utility>
#include <vector>

float NeuralNetwork::Evaluate() {
  float score = 0;

  float costs = 0;
  int costsLength = 0;

  std::vector<std::pair<std::vector<float>, std::vector<float>>> dataPoints =
      {};

  for (float x = 0; x < 1; x += 0.05) {
    for (float y = 0; y < 1; y += 0.05) {
      std::vector<float> outputs = {};

      if (y > 0.5) {
        outputs = {1, 0};
      } else {
        outputs = {0, 1};
      }
      if (dataPoints.size() != 0) {
        dataPoints.insert(dataPoints.begin() +
                              (std::rand() % (dataPoints.size())),
                          {{x, y}, outputs});
      } else {
        dataPoints.push_back({{x, y}, outputs});
      }
    }
  }

  for (int itter = 0; itter < std::min((int)dataPoints.size(), 400);
       itter += 1) {
    int index = itter;
    float x = dataPoints[index].first[0];
    float y = dataPoints[index].first[1];

    starting[0]->value = x;
    starting[1]->value = y;

    starting[1]->updated = true;
    starting[0]->updated = true;

    if (y > x) {
      costs += PointCost({x, y}, {1, 0});
      costsLength++;
    } else {
      costs += PointCost({x, y}, {0, 1});
      costsLength++;
    }
  }

  score = costs / costsLength;

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
