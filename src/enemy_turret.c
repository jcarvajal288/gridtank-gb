#include "enemy_turret.h"

#include <gb/gb.h>

#include "../res/enemy_turret_sprite.h"

#include "constants.h"
#include "point.h"

#define ENEMY_TILE_START_INDEX 40

static Point8 global_position;
static CardinalDirection orientation;


void init_turret(void) {
    global_position.x = 5 * TILE_SIZE;
    global_position.y = 5 * TILE_SIZE;
    orientation = NORTH;
    OBP0_REG = DMG_PALETTE(DMG_DARK_GRAY, DMG_WHITE, DMG_LITE_GRAY, DMG_BLACK);
    set_sprite_data(ENEMY_TILE_START_INDEX, enemy_turret_TILE_COUNT, enemy_turret_tiles);
}


uint8_t draw_turret(uint8_t sprite_index) {
    sprite_index += move_metasprite_ex(enemy_turret_metasprites[0], ENEMY_TILE_START_INDEX, 0, sprite_index, global_position.x, global_position.y + 8);
    return sprite_index;
}

