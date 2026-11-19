#include "enemy_turret.h"

#include <gb/gb.h>

#include "../res/enemy_turret_sprite.h"

#include "constants.h"
#include "point.h"

#define ENEMY_TILE_START_INDEX 40

void init_turret(void) {
    OBP0_REG = DMG_PALETTE(DMG_DARK_GRAY, DMG_WHITE, DMG_LITE_GRAY, DMG_BLACK);
    set_sprite_data(ENEMY_TILE_START_INDEX, enemy_turret_TILE_COUNT, enemy_turret_tiles);
}


uint8_t draw_turret(EnemyTurret* turret, uint8_t sprite_index) {
    uint8_t x = turret->position.x;
    uint8_t y = turret->position.y + 8;
    switch(turret->orientation) {
        case NORTH:
            sprite_index += move_metasprite_ex(enemy_turret_metasprites[0], ENEMY_TILE_START_INDEX, 0, sprite_index, x, y);
            break;
        case EAST:
            sprite_index += move_metasprite_ex(enemy_turret_metasprites[1], ENEMY_TILE_START_INDEX, 0, sprite_index, x, y);
            break;
        case SOUTH:
            sprite_index += move_metasprite_flipy(enemy_turret_metasprites[0], ENEMY_TILE_START_INDEX, 0, sprite_index, x, y);
            break;
        case WEST:
            sprite_index += move_metasprite_flipx(enemy_turret_metasprites[1], ENEMY_TILE_START_INDEX, 0, sprite_index, x, y);
            break;
    }
    return sprite_index;
}


void update_turret(EnemyTurret* turret, Point8* player_position) {
    turret->orientation = nearest_cardinal_to(&turret->position, player_position);
}