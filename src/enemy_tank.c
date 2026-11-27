#include "enemy_tank.h"

#include "../res/enemy_tank_body.h"
#include "../res/enemy_tank_turret.h"

#include <gb/gb.h>

#define ENEMY_TANK_SPEED 1
#define ENEMY_TANK_ANIMATION_FRAME_COUNT 4
#define ENEMY_TANK_ANIMATION_SPEED 2
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
            sprite_index += move_metasprite_ex(enemy_tank_body_metasprites[tank->animation_frame_counter], ENEMY_TANK_START_INDEX, 0, sprite_index, x, y);
            break;
        case EAST:
            sprite_index += move_metasprite_ex(enemy_tank_body_metasprites[tank->animation_frame_counter + 4], ENEMY_TANK_START_INDEX, 0, sprite_index, x, y);
            break;
        case SOUTH:
            sprite_index += move_metasprite_flipy(enemy_tank_body_metasprites[tank->animation_frame_counter], ENEMY_TANK_START_INDEX, 0, sprite_index, x, y);
            break;
        case WEST:
            sprite_index += move_metasprite_flipx(enemy_tank_body_metasprites[tank->animation_frame_counter + 4], ENEMY_TANK_START_INDEX, 0, sprite_index, x, y);
            break;
    }
    return sprite_index;
}

void enemy_tank_move_forward(EnemyTank* tank) {
    switch(tank->body_orientation) {
        case NORTH:
            tank->movement_destination.x = tank->position.x;
            tank->movement_destination.y = tank->position.y - TILE_SIZE;
            tank->movement_direction = NORTH;
            break;
        case SOUTH:
            tank->movement_destination.x = tank->position.x;
            tank->movement_destination.y = tank->position.y + TILE_SIZE;
            tank->movement_direction = SOUTH;
            break;
        case EAST:
            tank->movement_destination.x = tank->position.x + TILE_SIZE;
            tank->movement_destination.y = tank->position.y;
            tank->movement_direction = EAST;
            break;
        case WEST:
            tank->movement_destination.x = tank->position.x - TILE_SIZE;
            tank->movement_destination.y = tank->position.y;
            tank->movement_direction = WEST;
            break;
    }
}


void enemy_tank_move_backward(EnemyTank* tank) {
    switch(tank->body_orientation) {
        case NORTH:
            tank->movement_destination.x = tank->position.x;
            tank->movement_destination.y = tank->position.y + TILE_SIZE;
            tank->movement_direction = SOUTH;
            break;
        case SOUTH:
            tank->movement_destination.x = tank->position.x;
            tank->movement_destination.y = tank->position.y - TILE_SIZE;
            tank->movement_direction = NORTH;
            break;
        case EAST:
            tank->movement_destination.x = tank->position.x - TILE_SIZE;
            tank->movement_destination.y = tank->position.y;
            tank->movement_direction = WEST;
            break;
        case WEST:
            tank->movement_destination.x = tank->position.x + TILE_SIZE;
            tank->movement_destination.y = tank->position.y;
            tank->movement_direction = EAST;
            break;
    }
}


void enemy_tank_rotate_turret_right(EnemyTank* tank) {
    switch(tank->turret_orientation) {
        case NORTH:
            tank->turret_orientation = EAST;
            break;
        case EAST:
            tank->turret_orientation = SOUTH;
            break;
        case SOUTH:
            tank->turret_orientation = WEST;
            break;
        case WEST:
            tank->turret_orientation = NORTH;
            break;
    }
}

void enemy_tank_rotate_turret_left(EnemyTank* tank) {
    switch(tank->turret_orientation) {
        case NORTH:
            tank->turret_orientation = WEST;
            break;
        case WEST:
            tank->turret_orientation = SOUTH;
            break;
        case SOUTH:
            tank->turret_orientation = EAST;
            break;
        case EAST:
            tank->turret_orientation = NORTH;
            break;
    }
}


void enemy_tank_rotate_body_right(EnemyTank* tank) {
    switch(tank->body_orientation) {
        case NORTH:
            tank->body_orientation = EAST;
            break;
        case EAST:
            tank->body_orientation = SOUTH;
            break;
        case SOUTH:
            tank->body_orientation = WEST;
            break;
        case WEST:
            tank->body_orientation = NORTH;
            break;
    }
    enemy_tank_rotate_turret_right(tank);
}


void enemy_tank_rotate_body_left(EnemyTank* tank) {
    switch(tank->body_orientation) {
        case NORTH:
            tank->body_orientation = WEST;
            break;
        case WEST:
            tank->body_orientation = SOUTH;
            break;
        case SOUTH:
            tank->body_orientation = EAST;
            break;
        case EAST:
            tank->body_orientation = NORTH;
            break;
    }
    enemy_tank_rotate_turret_left(tank);
}


void move_enemy_tank(EnemyTank* tank, uint8_t frame_counter) {
    if (tank->movement_destination.y < tank->position.y) { // move north
        tank->position.y -= ENEMY_TANK_SPEED;
        if (tank->position.y <= tank->movement_destination.y) {
            tank->position.y = tank->movement_destination.y;
        }
    } else if (tank->movement_destination.y > tank->position.y) { // move south
        tank->position.y += ENEMY_TANK_SPEED;
        if (tank->position.y >= tank->movement_destination.y) {
            tank->position.y = tank->movement_destination.y;
        }
    } else if (tank->movement_destination.x > tank->position.x) { // move east
        tank->position.x += ENEMY_TANK_SPEED;
        if (tank->position.x >= tank->movement_destination.x) {
            tank->position.x = tank->movement_destination.x;
        }
    } else if (tank->movement_destination.x < tank->position.x) { // move west
        tank->position.x -= ENEMY_TANK_SPEED;
        if (tank->position.x <= tank->movement_destination.x) {
            tank->position.x = tank->movement_destination.x;
        }
    }
    if (frame_counter % ENEMY_TANK_ANIMATION_SPEED == 0) {
        if (tank->body_orientation == tank->movement_direction) {
            tank->animation_frame_counter--;
        } else {
            tank->animation_frame_counter++;
        }
    }
    tank->animation_frame_counter %= ENEMY_TANK_ANIMATION_FRAME_COUNT;
}


void update_enemy_tank(EnemyTank* tank, uint8_t current_tick, uint8_t frame_counter) {
    static uint8_t old_tick = 255;
    if (old_tick != current_tick) {
        switch(tank->pattern[current_tick % NUM_TANK_TICKS]) {
            case MOVE_FORWARD:
                enemy_tank_move_forward(tank);
                break;
            case MOVE_BACKWARD:
                enemy_tank_move_backward(tank);
                break;
            case ROTATE_LEFT:
                enemy_tank_rotate_body_left(tank);
                break;
            case ROTATE_RIGHT:
                enemy_tank_rotate_body_right(tank);
                break;
            case ROTATE_TURRET_LEFT:
                enemy_tank_rotate_turret_left(tank);
                break;
            case ROTATE_TURRET_RIGHT:
                enemy_tank_rotate_turret_right(tank);
                break;
        }
        old_tick = current_tick;
    }
    if (tank->position.x != tank->movement_destination.x || tank->position.y != tank->movement_destination.y) {
        move_enemy_tank(tank, frame_counter);
    }
}