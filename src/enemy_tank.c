#include "enemy_tank.h"

#include "../res/enemy_tank_body.h"
#include "../res/enemy_tank_turret.h"

#include <gb/gb.h>

#define ENEMY_TANK_START_INDEX 48
#define ENEMY_TANK_TURRET_START_INDEX ENEMY_TANK_START_INDEX + enemy_tank_body_TILE_COUNT

void init_enemy_tank(void) {
    OBP0_REG = DMG_PALETTE(DMG_DARK_GRAY, DMG_WHITE, DMG_LITE_GRAY, DMG_BLACK);
    set_sprite_data(ENEMY_TANK_START_INDEX, enemy_tank_body_TILE_COUNT, enemy_tank_body_tiles);
    set_sprite_data(ENEMY_TANK_TURRET_START_INDEX, enemy_tank_turret_TILE_COUNT, enemy_tank_turret_tiles);
}

uint8_t draw_enemy_tank(EnemyTank* tank, uint8_t sprite_index) {
    uint8_t x = tank->position.x;
    uint8_t y = tank->position.y + 8;
    switch(tank->turret_orientation) {
        case NORTH:
            sprite_index += move_metasprite_ex(enemy_tank_turret_metasprites[0], ENEMY_TANK_TURRET_START_INDEX, 0, sprite_index, tank->position.x, tank->position.y + 8);
            break;
        case EAST:
            sprite_index += move_metasprite_ex(enemy_tank_turret_metasprites[1], ENEMY_TANK_TURRET_START_INDEX, 0, sprite_index, tank->position.x, tank->position.y + 8);
            break;
        case SOUTH:
            sprite_index += move_metasprite_flipy(enemy_tank_turret_metasprites[0], ENEMY_TANK_TURRET_START_INDEX, 0, sprite_index, tank->position.x, tank->position.y + 8);
            break;
        case WEST:
            sprite_index += move_metasprite_flipx(enemy_tank_turret_metasprites[1], ENEMY_TANK_TURRET_START_INDEX, 0, sprite_index, tank->position.x, tank->position.y + 8);
            break;
    }
    switch(tank->body_orientation) {
        case NORTH:
            sprite_index += move_metasprite_ex(enemy_tank_body_metasprites[0], ENEMY_TANK_START_INDEX, 0, sprite_index, x, y);
            break;
        case EAST:
            sprite_index += move_metasprite_ex(enemy_tank_body_metasprites[4], ENEMY_TANK_START_INDEX, 0, sprite_index, x, y);
            break;
        case SOUTH:
            sprite_index += move_metasprite_flipy(enemy_tank_body_metasprites[0], ENEMY_TANK_START_INDEX, 0, sprite_index, x, y);
            break;
        case WEST:
            sprite_index += move_metasprite_flipx(enemy_tank_body_metasprites[4], ENEMY_TANK_START_INDEX, 0, sprite_index, x, y);
            break;
    }
    return sprite_index;
}

void update_enemy_tank(EnemyTank* tank, uint8_t current_tick) {

}