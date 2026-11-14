#include "tank.h"

#include <gb/gb.h>

#include "../res/tank_body.h"

#include "constants.h"
#include "point.h"

Point8 global_position;


void init_tank(void) {
    global_position.x = 5 * TILE_SIZE;
    global_position.y = 7 * TILE_SIZE;
    OBP0_REG = DMG_PALETTE(DMG_DARK_GRAY, DMG_WHITE, DMG_LITE_GRAY, DMG_BLACK);
    set_sprite_data(0, tank_body_TILE_COUNT, tank_body_tiles);
    move_metasprite_ex(tank_body_metasprites[0], 0, 0, 0, global_position.x, global_position.y + 8);
}
