#include <gb/gb.h>

#include "level.h"
#include "tank.h"

void init_gfx(void) {
    BGP_REG = 0xE4;
    DISPLAY_ON;
    SHOW_BKG;
    SHOW_SPRITES;
    SPRITES_8x16;
    HIDE_WIN;
}

void main(void) {
    init_gfx();

    draw_level();
    init_tank();
}