#include "raylib.h"
#include <assert.h>
#include <stdbool.h>
#include <stdint.h>

#define VIRTUAL_WIDTH 800
#define VIRTUAL_HEIGHT 450
#define TILE_WIDTH 50
#define TILE_HEIGHT 50
#define TILE_COUNT_X 16
#define TILE_COUNT_Y 9

typedef struct {
  Vector2 position;
  Vector2 velocity;
  int height;
  int width;
  char *inventory;
} Entity;

typedef struct {
  int count_x;
  int count_y;

  int upper_left_x;
  int upper_left_y;
  int tile_width;
  int tile_height;
} TileMap;

int TILE_MAP[TILE_COUNT_Y][TILE_COUNT_X] = {
    {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
};

bool is_tilemap_point_empty(TileMap *tile_map, int test_x, int test_y) {
  int player_tile_x = (int)(test_x / tile_map->tile_width);
  int player_tile_y = (int)(test_y / tile_map->tile_height);

  if (player_tile_x >= 0 && player_tile_x < tile_map->count_x &&
      player_tile_y >= 0 && player_tile_y < tile_map->count_y) {
    int tilemap = TILE_MAP[player_tile_y][player_tile_x];
    return tilemap == 0;
  }

  return false;
}

void test(char *text) {
  DrawText(text, GetScreenWidth() / 2, GetScreenHeight() / 2, 100, RED);
}

int main(void) {
  InitWindow(800, 450, "Tradebinder");
  SetTargetFPS(60);

  Entity player = {
      // .position = {.x = GetScreenWidth() / 2.0f,
      //              .y = GetScreenHeight() - (GetScreenHeight() / 4.0f)},
      .position = {.x = 50, .y = 50},
      .velocity = {.x = 0, .y = 0},
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
    player.velocity.y = 0;
    player.velocity.x = 0;
    if (IsKeyDown(KEY_W)) {
      player.velocity.y = -1.0f;
    }
    if (IsKeyDown(KEY_S)) {
      player.velocity.y = 1.0f;
    }
    if (IsKeyDown(KEY_A)) {
      player.velocity.x = -1.0f;
    }
    if (IsKeyDown(KEY_D)) {
      player.velocity.x = 1.0f;
    }
    player.velocity.x *= 150.0f;
    player.velocity.y *= 150.0f;

    // ---------------- //
    // ---- Update ---- //
    // ---------------- //
    float new_player_x = player.position.x + player.velocity.x * dt;
    float new_player_y = player.position.y + player.velocity.y * dt;

    TileMap tile_map = {.count_x = TILE_COUNT_X,
                        .count_y = TILE_COUNT_Y,
                        .tile_width = TILE_WIDTH,
                        .tile_height = TILE_HEIGHT};

    if (is_tilemap_point_empty(&tile_map, new_player_x, new_player_y) &&
        is_tilemap_point_empty(&tile_map, new_player_x + player.width,
                               new_player_y + player.height) &&
        is_tilemap_point_empty(&tile_map, new_player_x,
                               new_player_y + player.height) &&
        is_tilemap_point_empty(&tile_map, new_player_x + player.width,
                               new_player_y)) {
      player.position.x = new_player_x;
      player.position.y = new_player_y;
    }

    // ---------------- //
    // ----- Draw ----- //
    // ---------------- //
    BeginDrawing();
    ClearBackground(BLACK);

    for (int y = 0; y < TILE_COUNT_Y; y++) {
      for (int x = 0; x < TILE_COUNT_X; x++) {
        int tile = TILE_MAP[y][x];
        if (tile == 1) {
          DrawRectangle(x * TILE_WIDTH, y * TILE_HEIGHT, TILE_WIDTH,
                        TILE_HEIGHT, WHITE);
        }
      }
    }

    DrawRectangle(player.position.x, player.position.y, player.width,
                  player.height, BLUE);

    EndDrawing();
  }

  CloseWindow();
  return 0;
}
