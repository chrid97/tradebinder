#include "main.h"
#include "raylib.h"
#include <assert.h>
#include <stdbool.h>
#include <stdint.h>

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

int tiles_1_0[TILE_MAP_COUNT_Y][TILE_MAP_COUNT_X] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1},
};
int tiles_1_1[TILE_MAP_COUNT_Y][TILE_MAP_COUNT_X] = {
    {0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};
int tiles_0_0[TILE_MAP_COUNT_Y][TILE_MAP_COUNT_X] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
};
int tiles_0_1[TILE_MAP_COUNT_Y][TILE_MAP_COUNT_X] = {
    {1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
};

TileMap *get_tile_map(World *world, int tile_map_x, int tile_map_y) {
  if (tile_map_x >= 0 && tile_map_x <= world->tile_map_count_x &&
      tile_map_y >= 0 && tile_map_y <= world->tile_map_count_y) {
    TileMap *tile_map_value =
        &world->tile_maps[tile_map_y * world->tile_map_count_x + tile_map_x];

    return tile_map_value;
  }
  return 0;
}

int GetTileValueUnchecked(TileMap *tile_map, int tile_x, int tile_y) {
  int tile_map_value = tile_map->tiles[tile_y * TILE_MAP_COUNT_X + tile_x];
  return tile_map_value;
}

bool is_tilemap_point_door(World *world, TileMap *tile_map, float test_x,
                           float test_y) {
  int player_tile_x = (int)(test_x / world->tile_width);
  int player_tile_y = (int)(test_y / world->tile_height);

  if (player_tile_x >= 0 && player_tile_x < world->count_x &&
      player_tile_y >= 0 && player_tile_y < world->count_y) {

    return GetTileValueUnchecked(tile_map, player_tile_x, player_tile_y) == 3;
  }

  return false;
}

bool is_tilemap_point_empty(World *world, TileMap *tile_map, float test_tile_x,
                            float test_tile_y) {
  if (tile_map) {
    if (test_tile_x >= 0 && test_tile_x < world->count_x && test_tile_y >= 0 &&
        test_tile_y < world->count_y) {
      return GetTileValueUnchecked(tile_map, test_tile_x, test_tile_y) == 0;
    }
  }
  return false;
}

canonical_position get_normalized_position(World *world,
                                           raw_position position) {
  canonical_position result;

  result.tile_map_x = position.tile_map_x;
  result.tile_map_y = position.tile_map_y;

  float x = position.x - world->upper_left_x;
  float y = position.y - world->upper_left_y;
  result.tile_x = (int)(x / world->tile_width);
  result.tile_y = (int)(y / world->tile_height);

  result.x = x - result.tile_x * world->tile_width;
  result.y = y - result.tile_y * world->tile_height;

  if (result.tile_x < 0) {
    result.tile_x = world->count_x + result.tile_x;
    result.tile_map_x--;
  }

  if (result.tile_map_y < 0) {
    result.tile_map_y = world->count_x + result.tile_y;
    result.tile_map_y--;
  }

  if (result.tile_map_x > world->count_x) {
    result.tile_map_x = result.tile_map_x - world->count_x;
    result.tile_map_x++;
  }

  if (result.tile_map_y > world->count_y) {
    result.tile_map_y = result.tile_map_y - world->count_y;
    result.tile_map_y++;
  }

  return result;
}

bool is_world_point_empty(World *world, raw_position test_position) {
  canonical_position can_pos = get_normalized_position(world, test_position);
  TileMap *tile_map =
      get_tile_map(world, can_pos.tile_map_x, can_pos.tile_map_y);
  return is_tilemap_point_empty(world, tile_map, can_pos.tile_x,
                                can_pos.tile_y);
}

int main(void) {
  InitWindow(800, 450, "Tradebinder");
  SetTargetFPS(60);

  GameState game_state = {
      .player_tile_map_x = 0,
      .player_tile_map_y = 0,
  };

  TileMap tile_maps[2][2];
  TileMap tile_map0 = {
      .tiles = (int *)tiles_1_1,
  };
  TileMap tile_map1 = {
      .tiles = (int *)tiles_1_0,
  };

  tile_maps[0][0] = tile_map0;
  tile_maps[1][0] = tile_map1;

  Entity player = {
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

    World world = {.count_x = TILE_MAP_COUNT_X,
                   .count_y = TILE_MAP_COUNT_Y,
                   .upper_left_x = 0,
                   .upper_left_y = 0,
                   .tile_width = TILE_WIDTH,
                   .tile_height = TILE_HEIGHT,
                   .tile_map_count_x = 2,
                   .tile_map_count_y = 2,
                   .tile_maps = *tile_maps};
    TileMap *tile_map = get_tile_map(&world, game_state.player_tile_map_x,
                                     game_state.player_tile_map_y);
    assert(tile_map);

    float new_player_x = player.position.x + player.velocity.x * dt;
    float new_player_y = player.position.y + player.velocity.y * dt;

    raw_position player_position = {.tile_map_x = game_state.player_tile_map_x,
                                    .tile_map_y = game_state.player_tile_map_y,
                                    .tile_x = new_player_x,
                                    .tile_y = new_player_y};

    raw_position player_left = player_position;
    player_left.y = new_player_y + player.height;
    raw_position player_right;
    player_right.x = new_player_y + player.width;
    player_right.y = new_player_y + player.height;

    bool bottom_left = is_world_point_empty(&world, player_left);
    bool bottom_right = is_world_point_empty(&world, player_right);
    if (bottom_left && bottom_right) {
      player.position.x = new_player_x;
      player.position.y = new_player_y;
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
