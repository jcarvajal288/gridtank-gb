#include <gb/gb.h>
#include "../res/testlevel.h"
#include "../res/tileset.h"

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

    set_bkg_data(0, tileset_TILE_COUNT, tileset_tiles);
    set_bkg_tiles(0, 0, 20, 18, testlevel_map);
}