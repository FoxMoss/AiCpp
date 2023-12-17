#include "neuron.hpp"
#include <cstdio>
#include <utility>

float NeuralNetwork::Train() {
  std::vector<std::pair<NeuralConnection *, float>> connectionDeltas;
  std::vector<std::pair<Neuron *, float>> biasDeltas;
  float originalEval = Evaluate();

  for (int length = 0; length < hidden.size(); length++) {
    std::vector<HiddenNeuron *> layer = hidden[length];
    for (int neuron = 0; neuron < layer.size(); neuron++) {
      for (auto &connection : layer[neuron]->past) {
        connection.weight += PRECISION;
        float postEval = Evaluate();
        connection.weight -= PRECISION;

        float deltaCost = postEval - originalEval;
        connectionDeltas.push_back({&connection, deltaCost / PRECISION});
      }
      layer[neuron]->bias += PRECISION;
      float postEval = Evaluate();
      layer[neuron]->bias -= PRECISION;

      float deltaCost = postEval - originalEval;
      biasDeltas.push_back({layer[neuron], deltaCost / PRECISION});
    }
  }

  for (auto connectionDelta : connectionDeltas) {
    connectionDelta.first->weight += -connectionDelta.second * LEARN_RATE;
  }
  for (auto biasDelta : biasDeltas) {
    biasDelta.first->bias += -biasDelta.second * LEARN_RATE;
  }

  float finalEval = Evaluate();
  printf("Post train cost: %f\n", finalEval);

  return finalEval;
}
