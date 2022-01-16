#include "vram.h"

#include <gbdk/platform.h>
#include "player.h"
#include "cube.h"
#include "bkg.h"
#include "area1.h"

inline void setup_background()
{
    // Fill the screen background with a single tile pattern
    set_bkg_data(0, 256, bkg_tiles); // set tile #1 to the pattern[]
    set_bkg_tiles(0, 0, 32, 32, area1_data);

    // show bkg and sprites
    SHOW_BKG;
}

// Load the first page of vram with cube.png
inline void setup_vram_pg0()
{
    // Set tiles
    set_sprite_data(0, 16 * 16, cube_tiles);
}

// Assign the right tiles to the right sprites
inline void setup_sprites()
{
    setup_vram_pg0();

    // Player tiles [0-3]
    init_player();

    // Show our work
    SPRITES_8x8;
    SHOW_SPRITES;
}