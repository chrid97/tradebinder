#include "raylib.h"
#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>

#define VIRTUAL_WIDTH 800
#define VIRTUAL_HEIGHT 450

typedef struct {
  Vector2 position;
  Vector2 velocity;
  int height;
  int width;
  char *inventory;
} Entity;

void test(char *text) {
  DrawText(text, GetScreenWidth() / 2, GetScreenHeight() / 2, 100, RED);
}

int main(void) {
  InitWindow(800, 450, "Topspin");
  SetTargetFPS(60);

  Entity player = {
      .position = {.x = GetScreenWidth() / 2.0f,
                   .y = GetScreenHeight() - (GetScreenHeight() / 4.0f)},
      .height = 32,
      .width = 32};

  while (!WindowShouldClose()) {
    float dt = GetFrameTime();

    // Screen scaling
    int screen_width = GetScreenWidth();
    int screen_height = GetScreenHeight();
    float delta = GetFrameTime();
    float scale_x = (float)screen_width / VIRTUAL_WIDTH;
    float scale_y = (float)screen_height / VIRTUAL_HEIGHT;
    float scale = (scale_x < scale_y) ? scale_x : scale_y;

    // --------------- //
    // ---- Input ---- //
    // --------------- //
    if (IsKeyDown(KEY_W)) {
    }
    if (IsKeyDown(KEY_S)) {
    }
    if (IsKeyDown(KEY_A)) {
    }
    if (IsKeyDown(KEY_D)) {
    }

    // ---------------- //
    // ---- Update ---- //
    // ---------------- //

    // ---------------- //
    // ----- Draw ----- //
    // ---------------- //
    BeginDrawing();
    ClearBackground(BLACK);

    EndDrawing();
  }

  CloseWindow();
  return 0;
}
