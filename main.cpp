#include "main.hpp"
#include "neuron.hpp"
#include "raylib.h"
#include <cstdio>
#include <cstdlib>
#include <ctime>

int main(void) {
  std::srand(101);
  const int screenWidth = WIDTH;
  const int screenHeight = HEIGHT;

  InitWindow(screenWidth, screenHeight, "Ai");

  SetTargetFPS(FRAMERATE);

  NeuralNetwork network(2, 3, 4, 2);

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
        float waitedX = ((float)x / WIDTH);
        float waitedY = ((float)y / HEIGHT);

        network.starting[0]->value = ((float)x / WIDTH);
        network.starting[1]->value = ((float)y / HEIGHT);

        network.starting[0]->Update();

        if (drawingX == x && drawingY == y && !drewGraph) {

          network.Draw();
          drawingX += 10;
          drawingX %= WIDTH;
          drewGraph = true;
        }

        if (network.ending[0]->value > network.ending[1]->value) {
          ImageDrawRectangle(&out, x, y, 10, 10, RED);
        }
        if (network.ending[0]->value < network.ending[1]->value) {
          ImageDrawRectangle(&out, x, y, 10, 10, GREEN);
        }
        if (network.ending[0]->value == network.ending[1]->value) {
          ImageDrawRectangle(&out, x, y, 10, 10, WHITE);
        }

        // if ((waitedX * waitedX) > (waitedY * waitedY) + 0.1) {
        //   ImageDrawRectangle(&out, x, y, 5, 5, RED);
        // } else {
        //   ImageDrawRectangle(&out, x, y, 5, 5, GREEN);
        // }
        if (Correct(waitedX, waitedY)) {
          ImageDrawRectangle(&out, x, y, 5, 5, RED);
        } else {
          ImageDrawRectangle(&out, x, y, 5, 5, GREEN);
        }
      }
    }

    UpdateTexture(texture, out.data);

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
