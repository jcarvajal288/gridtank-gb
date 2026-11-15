#include "level.h"

#include "../res/testlevel.h"
#include "../res/tileset.h"
#include <gbdk/emu_debug.h>

#include "constants.h"

#define SCREEN_TILE_WIDTH 20
#define HARDWARE_TILE_SIZE 8
#define CLEAR_TILESET_TILE 0x02

void draw_level(void) {
    set_bkg_data(0, tileset_TILE_COUNT, tileset_tiles);
    set_bkg_tiles(0, 0, 20, 18, testlevel_map);
}

unsigned char get_tile_index(uint8_t x, uint8_t y) {
    return testlevel_map[x + (y * SCREEN_TILE_WIDTH)];
}

bool is_tile_clear(Point8 tile) {
    if (tile.x <= 0 || tile.x > 160) {
        return false;
    } else if (tile.y <= 0 || tile.y > 144) {
        return false;
    }
    uint8_t grid_x = tile.x / HARDWARE_TILE_SIZE - 1;
    uint8_t grid_y = tile.y / HARDWARE_TILE_SIZE - 1;
    unsigned char tile_index = get_tile_index(grid_x, grid_y);
    return tile_index == CLEAR_TILESET_TILE;
}