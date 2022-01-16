#ifndef TILEMAP_H
#define TILEMAP_H

#include "raylib.h"

typedef struct tilemap
{
    // The number of tiles this map is wide
    int width;
    // The number of tiles this map is high
    int height;

    // The data in the tilemap. Use width and height for the size of this data.
    int *data;

    // The texture for the tileset
    Texture2D tex;
    // The tile size for the tileset
    int tile_size;
} tilemap_t;

// Create a new tilemap
tilemap_t tilemap_create(int width, int height, Texture2D tex, int tile_size);

// Set a tile in a tilemap
void tilemap_set(tilemap_t this, int x, int y, int id);
// Get a tie in a tilemap
int tilemap_get(tilemap_t this, int x, int y);
// Get the rectangle in the source texture for a given tile
Rectangle tilemap_get_rect(tilemap_t this, int id);
// Get the number of tiles wide the tileset for this map is
int tilemap_tex_tiles_wide(tilemap_t this);
// Draw a single tile to the screen
void tilemap_draw_tile(tilemap_t this, int id, int x, int y, float scale);
// Draw the tilemap to the screen
void tilemap_draw(tilemap_t this, int x, int y);

#endif // TILEMAP_H