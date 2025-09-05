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

#define TILE_HEIGHT = 9;
#define TILE_WIDTH = 16;

int TILE_MAP[9][16] = {
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
};

void test(char *text) {
  DrawText(text, GetScreenWidth() / 2, GetScreenHeight() / 2, 100, RED);
}

int main(void) {
  InitWindow(800, 450, "Tradebinder");
  SetTargetFPS(60);

  Entity player = {
      // .position = {.x = GetScreenWidth() / 2.0f,
      //              .y = GetScreenHeight() - (GetScreenHeight() / 4.0f)},
      .position = {.x = 0, .y = 0},
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

    for (int y = 0; y < 9; y++) {
      for (int x = 0; x < 16; x++) {
        int tile_height = 50;
        int tile_width = 50;
        int tile = TILE_MAP[y][x];
        if (tile == 1) {
          DrawRectangle(x * tile_width, y * tile_height, tile_width,
                        tile_height, WHITE);
        }
      }
    }

    DrawCircle(player.position.x + 25, player.position.y + 25, 20, BLUE);

    ClearBackground(BLACK);

    EndDrawing();
  }

  CloseWindow();
  return 0;
}
