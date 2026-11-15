#include <gb/gb.h>
#include <gbdk/emu_debug.h>

#include "level.h"
#include "input.h"
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

    while(1) {
        update_input();
        update_tank();
        vsync();
    }
}