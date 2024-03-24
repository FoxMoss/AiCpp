#include "neuron.hpp"
#include "raylib.h"
#include <cstdio>
#include <string>
#include <vector>

NeuralNetwork::NeuralNetwork(int input, int hiddenLength, int hiddenAmmount,
                             int output) {
  starting = {};
  hidden = {};
  ending = {};
  for (int neuron = 0; neuron < input; neuron++) {
    starting.push_back(new StartingNeuron());
  }

  for (int length = 0; length < hiddenLength; length++) {
    hidden.push_back({});
    for (int neuron = 0; neuron < hiddenAmmount; neuron++) {
      if (length == 0) {
        hidden[length].push_back(new HiddenNeuron(starting));
      } else {
        hidden[length].push_back(new HiddenNeuron(hidden[length - 1]));
      }
    }
  }

  for (int neuron = 0; neuron < output; neuron++) {
    ending.push_back(new EndingNeuron(hidden[hiddenLength - 1]));

    for (int hiddenNeuron = 0; hiddenNeuron < hiddenAmmount; hiddenNeuron++) {
      hidden[hiddenLength - 1][hiddenNeuron]->AddChild(ending[neuron]);
    }
  }
}

void NeuralNetwork::Draw() {
  int x = 100;
  for (int neuron = 0; neuron < starting.size(); neuron++) {
    DrawCircle(x, 50 + neuron * 20, 5, GREEN);
    starting[neuron]->position = {(float)x, 50 + (float)neuron * 20};

    DrawText(std::to_string(starting[neuron]->value).c_str(), x,
             50 + neuron * 20, 10, WHITE);
  }

  x += 100;

  for (int length = 0; length < hidden.size(); length++) {
    std::vector<HiddenNeuron *> layer = hidden[length];
    for (int neuron = 0; neuron < layer.size(); neuron++) {
      DrawCircle(x, 50 + neuron * 20, 5, WHITE);
      layer[neuron]->position = {(float)x, 50 + (float)neuron * 20};

      DrawText(std::to_string(layer[neuron]->value).c_str(), x,
               50 + neuron * 20, 10, WHITE);

      for (auto connection : layer[neuron]->past) {
        if (connection.weight > 0.5) {
          DrawLineV(layer[neuron]->position, connection.originator->position,
                    WHITE);
        }
      }
    }
    x += 70;
  }

  x += 70;

  for (int neuron = 0; neuron < ending.size(); neuron++) {
    ending[neuron]->position = {(float)x, 50 + (float)neuron * 20};

    if (ending[0]->value < ending[1]->value) {
      if (neuron == 1) {
        DrawCircle(x, 50 + neuron * 20, 5, RED);
      }
    } else if (neuron == 0) {
      DrawCircle(x, 50 + neuron * 20, 5, RED);
    }

    DrawText(std::to_string(ending[neuron]->value).c_str(), x, 50 + neuron * 20,
             10, WHITE);

    for (auto connection : ending[neuron]->past) {
      if (connection.weight > 0.5) {
        DrawLineV(ending[neuron]->position, connection.originator->position,
                  WHITE);
      }
    }
  }
}
