#include "main.hpp"
#include "neuron.hpp"
#include "raylib.h"
#include <cstdio>
#include <cstdlib>
#include <ctime>

int main(void) {
  std::srand(std::time(nullptr));
  const int screenWidth = WIDTH;
  const int screenHeight = HEIGHT;

  InitWindow(screenWidth, screenHeight, "Ai");

  SetTargetFPS(FRAMERATE);

  NeuralNetwork network(2, 1, 2, 2);

  int drawingX = 0;
  int drawingY = 0;
  Image out = GenImageColor(WIDTH, HEIGHT, BLACK);

  for (int x = 0; x < WIDTH; x += 1) {
    for (int y = 0; y < HEIGHT; y += 1) {
    }
  }

  Texture2D texture = LoadTextureFromImage(out);

  while (!WindowShouldClose()) {
    bool drewGraph = false;
    BeginDrawing();

    ClearBackground(BLACK);

    network.Train();
    DrawTexture(texture, 0, 0, WHITE);

    for (int x = 0; x < WIDTH; x += 10) {
      for (int y = 0; y < HEIGHT; y += 10) {
        network.starting[0]->value = ((float)x / WIDTH) * 2 - 1;
        network.starting[1]->value = ((float)y / HEIGHT) * 2 - 1;

        network.starting[0]->Update();
        network.starting[1]->Update();

        if (drawingX == x && drawingY == y && !drewGraph) {

          network.Draw();
          drawingX += 10;
          drawingX %= WIDTH;
          drewGraph = true;
        }

        if (network.ending[0]->value > network.ending[1]->value) {
          ImageDrawPixel(&out, x, y, RED);
        }
        if (network.ending[0]->value < network.ending[1]->value) {
          ImageDrawPixel(&out, x, y, GREEN);
        }
        if (network.ending[0]->value == network.ending[1]->value) {
          ImageDrawPixel(&out, x, y, WHITE);
        }
      }
    }

    UpdateTexture(texture, out.data);

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
