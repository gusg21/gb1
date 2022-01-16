#include "player.h"

#include <gbdk/platform.h>

// Player frame x-offsets
#define PLAYER_UP 2
#define PLAYER_SIDE 1
#define PLAYER_DOWN 0

// Player shadow tile ID
#define PLAYER_SHADOW 3

uint8_t player_x = 64, player_y = 64;
bool player_flip_h = false;
uint8_t player_tile = PLAYER_DOWN;

inline void init_player()
{
    // sprite #0 (player)
    player_x = 64;
    player_y = 64;
    update_player_gfx(0, false);

    // sprite #1 (shadow)
    set_sprite_tile(1, PLAYER_SHADOW);
}

// place the player at a position
inline void update_player_gfx(uint8_t frames, bool moving)
{
    // Update tile
    if (moving)
        set_sprite_tile(0, player_tile + ((frames % 16 > 8) ? 16 : 0));
    else
        set_sprite_tile(0, player_tile + 32);
    
    // Flipping
    set_sprite_prop(0, player_flip_h ? S_FLIPX : 0);

    // Position
    move_sprite(0, 8 + player_x, 16 + player_y);
    if ((frames % 2) == 0)
        move_sprite(1, 8 + player_x, 16 + 1 + player_y);
    else
        move_sprite(1, 0, 0);
}

// update the player
inline void update_player(uint8_t frames, uint8_t joypad)
{
    bool moving = false;

    if (joypad & J_DOWN)
    {
        player_y++;
        player_tile = PLAYER_DOWN;
        player_flip_h = false;
        moving = true;
    }
    if (joypad & J_UP)
    {
        player_y--;
        player_tile = PLAYER_UP;
        player_flip_h = false;
        moving = true;
    }
    if (joypad & J_RIGHT)
    {
        player_x++;
        player_tile = PLAYER_SIDE;
        player_flip_h = true;
        moving = true;
    }
    if (joypad & J_LEFT)
    {
        player_x--;
        player_tile = PLAYER_SIDE;
        player_flip_h = false;
        moving = true;
    }

    update_player_gfx(frames, moving);
}