#include "neuron.hpp"
#include <cmath>
#include <cstdio>

void StartingNeuron::Update() {
  for (auto neuron : next) {
    neuron.second->Update();
  }
}
void HiddenNeuron::Update() {
  value = 0;
  for (auto neuron : past) {
    value += neuron.originator->value * neuron.weight;
  }
  value += bias;
  value = Activation(value);

  for (auto neuron : next) {
    neuron.second->Update();
  }
}

void EndingNeuron::Update() {
  value = 0;
  for (auto neuron : past) {
    value += neuron.originator->value * neuron.weight;
  }
  // value += bias;
  // value = Activation(value);
}

float Neuron::Activation(float in) {
  // return (in > 0 ? 1 : 0);
  return 1 / (1 + std::exp(-in));
  // return in;
}
