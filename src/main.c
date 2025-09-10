#include "raylib.h"
#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#define VIRTUAL_WIDTH 800
#define VIRTUAL_HEIGHT 450
#define TILE_WIDTH 50
#define TILE_HEIGHT 50
#define TILE_MAP_COUNT_X 16
#define TILE_MAP_COUNT_Y 9

void test(char *text) {
  DrawText(text, GetScreenWidth() / 2, GetScreenHeight() / 2, 100, RED);
}

typedef struct {
  Vector2 position;
  Vector2 velocity;
  float height;
  float width;
  char *inventory;
} Entity;

typedef struct {
  int count_x;
  int count_y;

  int upper_left_x;
  int upper_left_y;
  int tile_width;
  int tile_height;

  int *tiles;
} TileMap;

int tiles0[TILE_MAP_COUNT_Y][TILE_MAP_COUNT_X] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1},
};
int tiles1[TILE_MAP_COUNT_Y][TILE_MAP_COUNT_X] = {
    {0, 1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};
int tiles2[TILE_MAP_COUNT_Y][TILE_MAP_COUNT_X] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
};
int tiles3[TILE_MAP_COUNT_Y][TILE_MAP_COUNT_X] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
};

int GetTileValueUnchecked(TileMap *tile_map, int tile_x, int tile_y) {
  int tile_map_value = tile_map->tiles[tile_y * TILE_MAP_COUNT_X + tile_x];
  return tile_map_value;
}

bool is_tilemap_point_door(TileMap *tile_map, float test_x, float test_y) {
  int player_tile_x = (int)(test_x / tile_map->tile_width);
  int player_tile_y = (int)(test_y / tile_map->tile_height);

  if (player_tile_x >= 0 && player_tile_x < tile_map->count_x &&
      player_tile_y >= 0 && player_tile_y < tile_map->count_y) {

    return GetTileValueUnchecked(tile_map, player_tile_x, player_tile_y) == 3;
  }

  return false;
}

bool is_tilemap_point_empty(TileMap *tile_map, float test_x, float test_y) {
  int player_tile_x = (int)(test_x / tile_map->tile_width);
  int player_tile_y = (int)(test_y / tile_map->tile_height);

  if (player_tile_x >= 0 && player_tile_x < tile_map->count_x &&
      player_tile_y >= 0 && player_tile_y < tile_map->count_y) {

    return GetTileValueUnchecked(tile_map, player_tile_x, player_tile_y) == 0;
  }

  return false;
}

int main(void) {
  InitWindow(800, 450, "Tradebinder");
  SetTargetFPS(60);

  TileMap tile_maps[2];
  TileMap tile_map0 = {
      .count_x = TILE_MAP_COUNT_X,
      .count_y = TILE_MAP_COUNT_Y,
      .upper_left_x = -30,
      .upper_left_y = 0,
      .tile_width = TILE_WIDTH,
      .tile_height = TILE_HEIGHT,
      .tiles = (int *)tiles0,
  };
  TileMap tile_map1 = {
      .count_x = TILE_MAP_COUNT_X,
      .count_y = TILE_MAP_COUNT_Y,
      .upper_left_x = -30,
      .upper_left_y = 0,
      .tile_width = TILE_WIDTH,
      .tile_height = TILE_HEIGHT,
      .tiles = (int *)tiles1,
  };

  tile_maps[0] = tile_map0;
  tile_maps[1] = tile_map1;
  int map_index = 1;
  TileMap *tile_map = &tile_maps[map_index];

  Entity player = {
      // .position = {.x = GetScreenWidth() / 2.0f,
      //              .y = GetScreenHeight() - (GetScreenHeight() / 4.0f)},
      .position = {.x = GetScreenWidth() / 2.0f, .y = GetScreenHeight() / 2.0f},
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

    bool bottom_left = is_tilemap_point_empty(tile_map, new_player_x,
                                              new_player_y + player.height);
    bool bottom_right = is_tilemap_point_empty(
        tile_map, new_player_x + player.width, new_player_y + player.height);

    if (bottom_left && bottom_right) {
      player.position.x = new_player_x;
      player.position.y = new_player_y;
    }

    bool is_door = is_tilemap_point_door(tile_map, new_player_x + player.width,
                                         new_player_y + player.height);

    if (is_door) {
      if (map_index == 1) {
        map_index = 0;
        tile_map = &tile_maps[map_index];
        player.position.x = 7 * TILE_HEIGHT;
        player.position.y = screen_height - TILE_HEIGHT - player.height;
      } else if (map_index == 0) {
        map_index = 1;
        tile_map = &tile_maps[map_index];
        player.position.x = 7 * TILE_HEIGHT;
        player.position.y = player.height;
      }
    }

    // ---------------- //
    // ----- Draw ----- //
    // ---------------- //
    BeginDrawing();
    ClearBackground(BLACK);

    for (int y = 0; y < TILE_MAP_COUNT_Y; y++) {
      for (int x = 0; x < TILE_MAP_COUNT_X; x++) {
        int tile = GetTileValueUnchecked(tile_map, x, y);
        if (tile == 1) {
          DrawRectangle(x * TILE_WIDTH, y * TILE_HEIGHT, TILE_WIDTH,
                        TILE_HEIGHT, WHITE);
          DrawRectangleLines(x * TILE_WIDTH, y * TILE_HEIGHT, TILE_WIDTH,
                             TILE_HEIGHT, GRAY);
        }

        if (tile == 3) {
          DrawRectangle(x * TILE_WIDTH, y * TILE_HEIGHT, TILE_WIDTH,
                        TILE_HEIGHT, BROWN);
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
