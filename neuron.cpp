#include "neuron.hpp"
#include <algorithm>
#include <cmath>
#include <cstdio>

void StartingNeuron::Update() {
  updated = true;

  for (auto neuron : next) {
    neuron.second->Update();
  }

  Reset();
}
void HiddenNeuron::Update() {
  updated = true;

  for (auto neuron : past) {
    if (!neuron.originator->updated) {
      return;
    }
  }

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
  updated = true;

  for (auto neuron : past) {
    if (!neuron.originator->updated) {
      return;
    }
  }

  value = 0;
  for (auto neuron : past) {
    value += neuron.originator->value * neuron.weight;
  }
  // value += bias;
  // value = Activation(value);
}

float Neuron::Activation(float in) {
  // return (in > 0 ? 1 : 0);
  // return 1 / (1 + std::exp(-in));
  return std::fmax(0.0, in);
  // return in;
}

void StartingNeuron::Reset() {
  updated = false;
  for (auto neuron : next) {
    neuron.second->Reset();
  }
}

void HiddenNeuron::Reset() {
  updated = false;
  for (auto neuron : next) {
    neuron.second->Reset();
  }
}
void EndingNeuron::Reset() { updated = false; }
