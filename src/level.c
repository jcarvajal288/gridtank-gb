#include "level.h"

#include "../res/testlevel.h"
#include "../res/tileset.h"

void draw_level(void) {
    set_bkg_data(0, tileset_TILE_COUNT, tileset_tiles);
    set_bkg_tiles(0, 0, 20, 18, testlevel_map);
}

bool is_tile_clear(Point8 tile) {
    if (tile.x <= 0 || tile.x > 160) {
        return false;
    } else if (tile.y <= 0 || tile.y > 144) {
        return false;
    }
    return true;
}