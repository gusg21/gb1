#include <stdint.h>

// #define __TARGET_gb
#include <gbdk/platform.h>

#include "vram.h"
#include "player.h"

// Inaccurate 8-bit frame count
uint8_t frames = 0;

// sprite coords
int8_t scroll_y = 0;

// main function
void main(void)
{
    // init palettes
    BGP_REG = OBP0_REG = 0xE4;
    OBP1_REG = 0xE0;

    // Setup background
    setup_background();    

    // Setup sprites
    setup_sprites();

    while (1)
    {
        uint8_t joypad_state = joypad();

        update_player(frames, joypad_state);

        // wait for VBlank to slow down everything and reduce cpu use when idle
        wait_vbl_done();

        frames++;
    }
}
