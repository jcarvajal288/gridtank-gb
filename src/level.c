#include "level.h"

#include "../res/testlevel.h"
#include "../res/tileset.h"

void draw_level(void) {
    set_bkg_data(0, tileset_TILE_COUNT, tileset_tiles);
    set_bkg_tiles(0, 0, 20, 18, testlevel_map);
}