typedef struct {

  int *tiles;
} TileMap;

typedef struct {
  int tile_map_x;
  int tile_map_y;

  float x;
  float y;

} WorldPosition;

typedef struct {
  int count_x;
  int count_y;

  int upper_left_x;
  int upper_left_y;
  int tile_width;
  int tile_height;

  int tile_map_count_x;
  int tile_map_count_y;

  TileMap *tile_maps;
} World;

typedef struct {
  int tile_map_x;
  int tile_map_y;

  int tile_x;
  int tile_y;

  int x;
  int y;
} canonical_position;

typedef struct {
  int tile_map_x;
  int tile_map_y;

  int tile_x;
  int tile_y;

  int x;
  int y;
} raw_position;

typedef struct {
  int player_tile_map_x;
  int player_tile_map_y;
} GameState;
