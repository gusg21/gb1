//
//  main.c
//  GBMapper
//
//  Created by Gus Goucher on 1/3/22.
//

#include <stdio.h>

#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "extras/raygui.h"

#include "tilemap.h"
#include "gb.h"

#define TILE_SIZE 8
#define MAP_SIZE 32
#define MAP_SCALE 3
#define HUD_HEIGHT 80
#define WINDOW_PADDING 10

int main(int argc, const char *argv[])
{
    if (argc < 3)
    {
        printf("Please supply tileset and output file to edit with.\n");
        return 0;
    }

    InitWindow(
        MAP_SIZE * TILE_SIZE * MAP_SCALE + WINDOW_PADDING * 2,
        MAP_SIZE * TILE_SIZE * MAP_SCALE + WINDOW_PADDING * 2 + HUD_HEIGHT,
        "GBMapper"
    );

    // Map data
    tilemap_t map = tilemap_create(MAP_SIZE, MAP_SIZE, LoadTexture(argv[1]), TILE_SIZE);

    // Selected tile id
    unsigned int selectedID = 1;

    // Render texture
    RenderTexture2D mapTex = LoadRenderTexture(
        map.width * map.tile_size,
        map.height * map.tile_size
    );

    bool gui_window_closed = false;
    while (!WindowShouldClose() && !gui_window_closed)
    {
        // Update Selected Tile
        if (IsKeyPressed(KEY_Z))
            selectedID --;
        if (IsKeyPressed(KEY_X))
            selectedID ++;
        selectedID %= 256;

        int tileX = (GetMouseX() - WINDOW_PADDING) / MAP_SCALE / TILE_SIZE;
        int tileY = (GetMouseY() - WINDOW_PADDING) / MAP_SCALE / TILE_SIZE;
        bool overMap = (
            tileX >= 0 && tileX < MAP_SIZE && tileY >= 0 && tileY < MAP_SIZE
        );

        // Place tiles
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && overMap)
        {
            tilemap_set(map, tileX, tileY, selectedID);
        }
        
        // Pick tile
        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT) && overMap)
        {
            selectedID = tilemap_get(map, tileX, tileY);
        }

        // Save map
        if (IsKeyPressed(KEY_S))
        {
            save_gb_map(map, argv[2]);
        }

        // Draw
        BeginDrawing();
        {
            // Background
            ClearBackground(BLACK);

            // World-space
            BeginTextureMode(mapTex);
            {
                tilemap_draw(map, 0, 0);
            }
            EndTextureMode();

            DrawTexturePro(
                mapTex.texture, 
                (Rectangle){0, 0, mapTex.texture.width, -mapTex.texture.height},
                (Rectangle){WINDOW_PADDING, WINDOW_PADDING, mapTex.texture.width * MAP_SCALE, mapTex.texture.height * MAP_SCALE}, 
                (Vector2){0, 0}, 
                0.f,
                WHITE
            );

            // HUD
            int hudY = WINDOW_PADDING * 2 + MAP_SIZE * TILE_SIZE * MAP_SCALE;

            // ID + selected info
            DrawText(TextFormat("ID: %d", selectedID), 10, hudY, 20, WHITE);
            tilemap_draw_tile(map, selectedID, 84, hudY + 1, 2.f);

            // Help info
            DrawText("Z--, X++, [S]ave", 10, hudY + 30, 20, WHITE);

            // Cursor
            if (overMap)
            {
                int tileOverId = tilemap_get(map, tileX, tileY);
                DrawRectangleLines(
                    tileX * TILE_SIZE * MAP_SCALE + WINDOW_PADDING - 1,
                    tileY * TILE_SIZE * MAP_SCALE + WINDOW_PADDING - 1,
                    TILE_SIZE * MAP_SCALE + 2, TILE_SIZE * MAP_SCALE + 2, WHITE
                );
                DrawText(
                    TextFormat("ID: %d", tileOverId), 
                    tileX * TILE_SIZE * MAP_SCALE + WINDOW_PADDING - 1,
                    (tileY + 1) * TILE_SIZE * MAP_SCALE + WINDOW_PADDING + 1,
                    10, WHITE
                );
            }
        }
        EndDrawing();
    }

    return 0;
}
