#include "main.hpp"
#include "neuron.hpp"
#include "raylib.h"
#include <cstdlib>
#include <ctime>

int main(void) {
  std::srand(std::time(nullptr));
  const int screenWidth = WIDTH;
  const int screenHeight = HEIGHT;

  InitWindow(screenWidth, screenHeight, "Ai");

  SetTargetFPS(FRAMERATE);

  // 2
  // 7
  // 7
  // 7
  // 7
  // 4
  NeuralNetwork network(2, 1, 2, 4);

  while (!WindowShouldClose()) {
    BeginDrawing();

    ClearBackground(BLACK);

    network.Draw();
    for (int x = 0; x < WIDTH; x += 10) {
      for (int y = 0; y < HEIGHT; y += 10) {
        network.starting[0]->value = (float)x / WIDTH * 10;
        network.starting[1]->value = (float)y / HEIGHT * 10;

        network.starting[0]->Update();
        network.starting[1]->Update();

        if (network.ending[0]->value < network.ending[1]->value) {
          DrawPixel(x, y, RED);
        }
        if (network.ending[0]->value > network.ending[1]->value) {
          DrawPixel(x, y, GREEN);
        }

        if (x < y) {
          DrawPixel(x, y, RED);
        } else {
          DrawPixel(x, y, GREEN);
        }
      }
    }

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
