#ifndef PLAYER_H
#define PLAYER_H

#include <gbdk/platform.h>

inline void init_player();
inline void update_player_gfx(uint8_t frames, bool moving);
inline void update_player(uint8_t frames, uint8_t joypad);

#endif // PLAYER_H