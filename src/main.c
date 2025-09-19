#include "main.h"
#include "raylib.h"
#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>

#define VIRTUAL_WIDTH 800
#define VIRTUAL_HEIGHT 450
#define TILE_WIDTH 50
#define TILE_HEIGHT 50
#define TILE_MAP_COUNT_X 16
#define TILE_MAP_COUNT_Y 9

#define CARD_HEIGHT 150
#define CARD_WIDTH 100

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
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
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
  result.tile_x = floorf(x / world->tile_width);
  result.tile_y = floorf(y / world->tile_height);

  result.x = x - result.tile_x * world->tile_width;
  result.y = y - result.tile_y * world->tile_height;

  if (result.tile_x < 0) {
    result.tile_x += world->count_x;
    result.tile_map_x--;
  }
  if (result.tile_y < 0) {
    result.tile_y += world->count_y;
    result.tile_map_y--;
  }

  if (result.tile_x >= world->count_x) {
    result.tile_x -= world->count_x;
    result.tile_map_x++;
  }

  if (result.tile_y >= world->count_y) {
    result.tile_y -= world->count_y;
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
      .player_tile_map_x = 1,
      .player_tile_map_y = 1,
      // maybe it would be cool if the first time you boot the game your
      // inventory is open ?
      .is_inventory_open = false,
  };

  // it would be nice if i could just place him on a tile
  Entity guy = {.height = TILE_HEIGHT,
                .width = TILE_WIDTH,
                .position = {.x = 4 * TILE_WIDTH, .y = 3 * TILE_HEIGHT}};

  TileMap tile_maps[2][2];
  TileMap tile_map11 = {
      .tiles = (int *)tiles_1_1,
  };
  TileMap tile_map10 = {
      .tiles = (int *)tiles_1_0,
  };
  TileMap tile_map00 = {
      .tiles = (int *)tiles_0_0,
  };
  TileMap tile_map01 = {
      .tiles = (int *)tiles_0_1,
  };

  tile_maps[0][0] = tile_map00;
  tile_maps[0][1] = tile_map10;
  tile_maps[1][1] = tile_map11;
  tile_maps[1][0] = tile_map01;

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
    if (IsKeyPressed(KEY_TAB)) {
      game_state.is_inventory_open = !game_state.is_inventory_open;
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
                   .tile_maps = (TileMap *)tile_maps};

    TileMap *tile_map = get_tile_map(&world, game_state.player_tile_map_x,
                                     game_state.player_tile_map_y);
    assert(tile_map);

    float new_player_x = player.position.x + player.velocity.x * dt;
    float new_player_y = player.position.y + player.velocity.y * dt;

    // i guess this is weird because all i use is tile_map_y and x and I dont
    // even do any collision detection
    raw_position guy_pos = {.tile_map_x = 1,
                            .tile_map_y = 0,
                            .x = guy.position.x,
                            .y = guy.position.y};

    raw_position player_pos = {.tile_map_x = game_state.player_tile_map_x,
                               .tile_map_y = game_state.player_tile_map_y,
                               .x = new_player_x,
                               .y = new_player_y};

    raw_position player_left = {.tile_map_x = game_state.player_tile_map_x,
                                .tile_map_y = game_state.player_tile_map_y,
                                .x = new_player_x,
                                .y = new_player_y + player.height};

    raw_position player_right = {.tile_map_x = game_state.player_tile_map_x,
                                 .tile_map_y = game_state.player_tile_map_y,
                                 .x = new_player_x + player.width,
                                 .y = new_player_y + player.height};

    Rectangle player_rect = {
        .x = player.position.x,
        .y = player.position.y,
        .width = player.width,
        .height = player.height,
    };

    Rectangle guy_rect = {
        .x = guy.position.x,
        .y = guy.position.y,
        .width = guy.width,
        .height = guy.height,
    };

    bool bottom_left = is_world_point_empty(&world, player_left);
    bool bottom_right = is_world_point_empty(&world, player_right);
    if (bottom_left && bottom_right &&
        CheckCollisionRecs(player_rect, player_rect)) {
      canonical_position can_pos = get_normalized_position(&world, player_pos);

      game_state.player_tile_map_x = can_pos.tile_map_x;
      game_state.player_tile_map_y = can_pos.tile_map_y;

      player.position.x =
          world.upper_left_x + world.tile_width * can_pos.tile_x + can_pos.x;

      player.position.y =
          world.upper_left_y + world.tile_width * can_pos.tile_y + can_pos.y;
      // player.position.x = new_player_x;
      // player.position.y = new_player_y;
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

    if (game_state.player_tile_map_x == 1 &&
        game_state.player_tile_map_y == 0) {
      DrawRectangle(guy_pos.x, guy_pos.y, guy.width, guy.height, RED);
    }

    DrawRectangle(player.position.x, player.position.y, player.width,
                  player.height, BLUE);

    if (CheckCollisionRecs(player_rect, guy_rect)) {
      int box_height = 100;
      DrawRectangle(0, screen_height - box_height, screen_width, 200, BLACK);
      DrawRectangleLines(0, screen_height - box_height, screen_width, 200,
                         WHITE);
      DrawText("Hey do you want to trade?", 0, screen_height - box_height,
               50 * scale, WHITE);
    }

    // (TODO) When invetory is open game state should be frozen
    if (game_state.is_inventory_open) {
      int padding = 20;
      DrawRectangle(10, 10, screen_width - padding, screen_height - padding,
                    BROWN);

      for (int y = 10; y < screen_width - padding; y++) {
        for (int x = 10; x < screen_height - padding; x++) {
          DrawRectangleLines(x, y, CARD_WIDTH, CARD_HEIGHT, WHITE);
        }
      }
    }

    EndDrawing();
  }

  CloseWindow();
  return 0;
}
