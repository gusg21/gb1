#include "math.h"

#include "tilemap.h"

tilemap_t tilemap_create(int width, int height, Texture2D tex, int tile_size)
{
    tilemap_t map = {0};

    map.width = width;
    map.height = height;
    map.data = MemAlloc(sizeof(int) * width * height);
    map.tex = tex;
    map.tile_size = tile_size;

    return map;
}

void tilemap_set(tilemap_t this, int x, int y, int value)
{
    if (x >= this.width || y >= this.height)
        return;

    this.data[y * this.width + x] = value;
}

int tilemap_get(tilemap_t this, int x, int y)
{
    if (x >= this.width || y >= this.height)
        return -1;

    return this.data[y * this.width + x];
}

Rectangle tilemap_get_rect(tilemap_t this, int id)
{
    return (Rectangle){
        (id % tilemap_tex_tiles_wide(this)) * this.tile_size,
        ((int)(id / tilemap_tex_tiles_wide(this))) * this.tile_size,
        this.tile_size, this.tile_size};
}

int tilemap_tex_tiles_wide(tilemap_t this)
{
    return (int)(this.tex.width / this.tile_size);
}

void tilemap_draw_tile(tilemap_t this, int id, int x, int y, float scale)
{
    DrawTexturePro(
        this.tex,
        tilemap_get_rect(this, id),
        (Rectangle){x, y, this.tile_size * scale, this.tile_size * scale},
        (Vector2){0, 0}, 0.f, WHITE);
}

void tilemap_draw(tilemap_t this, int x, int y)
{
    for (int row = 0; row < this.height; row++)
    {
        for (int col = 0; col < this.width; col++)
        {
            int id = tilemap_get(this, col, row);
            tilemap_draw_tile(this, id, col * this.tile_size + x, row * this.tile_size + y, 1.f);
            // DrawTextureRec(
            //     this.tex,
            //     tilemap_get_rect(this, id),
            //     (Vector2){col * this.tile_size + x, row * this.tile_size + y},
            //     WHITE);
        }
    }
}