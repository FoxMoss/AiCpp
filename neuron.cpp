#include "neuron.hpp"
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
  for (auto neuron : next) {
    neuron.second->Update();
  }
}

void EndingNeuron::Update() {
  value = 0;
  for (auto neuron : past) {
    value += neuron.originator->value * neuron.weight;
  }
  value += bias;
  printf("hey\n");
}
