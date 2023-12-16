#pragma once
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <map>
#include <random>
#include <raylib.h>
#include <vector>

class Neuron {
public:
  float value;
  float bias;
  Vector2 position;

  Neuron() {
    bias = (float)std::rand() / (float)RAND_MAX;
    position = {};
  };
  Neuron(Neuron const &) {}
  virtual ~Neuron() = default;

  virtual void Update(){};
  virtual void AddChild(Neuron *neuron) {}

private:
};

typedef struct {
  Neuron *originator;
  float weight;
} NeuralConnection;

class StartingNeuron : public Neuron {
public:
  StartingNeuron() : Neuron() { next = {}; }
  ~StartingNeuron() {}

  void AddChild(Neuron *neuron) override { next[(intptr_t)neuron] = neuron; }

  void Update() override;

private:
  std::map<int, Neuron *> next;
};

class HiddenNeuron : public Neuron {
public:
  HiddenNeuron(std::vector<StartingNeuron *> old) : Neuron() {
    next = {};
    for (auto oldNeuron : old) {
      past.push_back({oldNeuron, (float)std::rand() / (float)RAND_MAX});
    }
  }
  HiddenNeuron(std::vector<HiddenNeuron *> old) : Neuron() {
    next = {};
    for (auto oldNeuron : old) {
      past.push_back({oldNeuron, (float)std::rand() / (float)RAND_MAX});
    }
  }

  void AddChild(Neuron *neuron) override {
    next[(intptr_t)neuron] = neuron;

    for (auto lastNeuron : past) {
      lastNeuron.originator->AddChild(this);
    }
  }

  ~HiddenNeuron() {}

  std::vector<NeuralConnection> past;

  std::map<int, Neuron *> next;
  void Update() override;

private:
};

class EndingNeuron : public Neuron {
public:
  EndingNeuron(std::vector<HiddenNeuron *> old) : Neuron() {
    for (auto oldNeuron : old) {
      past.push_back({oldNeuron, (float)std::rand() / (float)RAND_MAX});
    }
  }

  void AddChild(Neuron *neuron) override {}
  ~EndingNeuron() {}

  std::vector<NeuralConnection> past;

  void Update() override;

private:
};

class NeuralNetwork {
public:
  NeuralNetwork(int input, int hiddenSize, int hiddenAmmount, int output);
  ~NeuralNetwork() {}
  void Draw();
  std::vector<StartingNeuron *> starting;
  std::vector<EndingNeuron *> ending;

private:
  std::vector<std::vector<HiddenNeuron *>> hidden;
};
