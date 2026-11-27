#include "enemy.h"

#include <gbdk/emu_debug.h>
#include <stdbool.h>

#include "level.h"
#include "tank.h"

#define MAX_ENEMIES 3

static Enemy enemies[MAX_ENEMIES];
static uint8_t num_enemies = 0;

void add_turret(uint8_t x, uint8_t y, CardinalDirection* pattern) {
    if (num_enemies >= MAX_ENEMIES) {
        return;
    }

    EnemyTurret turret = {
        .position = { .x = x * TILE_SIZE, .y = y * TILE_SIZE},
        .orientation = NORTH
    };

    if (pattern) {
        for (uint8_t i = 0; i < NUM_TURRET_TICKS; i++) {
            turret.pattern[i] = pattern[i];
        }
    }

    uint8_t i = num_enemies++;
    enemies[i].type = TURRET;
    enemies[i].data.enemy_turret = turret;
}

void add_tank(uint8_t x, uint8_t y, TankDirection* pattern) {
    if (num_enemies >= MAX_ENEMIES) {
        return;
    }

    EnemyTank tank = {
        .position = { .x = x * TILE_SIZE, .y = y * TILE_SIZE},
        .body_orientation = NORTH,
        .turret_orientation = NORTH,
        .animation_frame_counter = 0
    };

    if (pattern) {
        for (uint8_t i = 0; i < NUM_TANK_TICKS; i++) {
            tank.pattern[i] = pattern[i];
        }
    }

    uint8_t i = num_enemies++;
    enemies[i].type = TANK;
    enemies[i].data.enemy_tank = tank;
}


void update_enemies(uint8_t current_tick) {
    for(Enemy *enemy = enemies, *end = enemies + num_enemies; enemy < end; enemy++) { 
        if (enemy->type == TURRET) {
            update_turret(&enemy->data.enemy_turret, current_tick);
        } else if (enemy->type == TANK) {
            update_enemy_tank(&enemy->data.enemy_tank, current_tick);
        }
    }
}


uint8_t draw_enemies(uint8_t sprite_index) {
    for(Enemy *enemy = enemies, *end = enemies + num_enemies; enemy < end; enemy++) { 
        if (enemy->type == TURRET) {
            sprite_index = draw_turret(&enemy->data.enemy_turret, sprite_index);
        } else if (enemy->type == TANK) {
            sprite_index = draw_enemy_tank(&enemy->data.enemy_tank, sprite_index);
        }
    }
    return sprite_index;
}


// only works correctly for horizontal or vertical lines
bool line_clear(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2) {
    if (x1 == x2)  {
        if (y1 < y2) {
            for (uint8_t y = y1; y < y2; y++) {
                if (!is_tile_clear_xy(x1, y)) return false;
            }
        } else {
            for (uint8_t y = y2; y < y1; y++) {
                if (!is_tile_clear_xy(x1, y)) return false;
            }
        }
    } else if (y1 == y2) {
        if (x1 < x2) {
            for (uint8_t x = x1; x < x2; x++) {
                if (!is_tile_clear_xy(x, y1)) return false;
            }
        } else {
            for (uint8_t x = x2; x < x1; x++) {
                if (!is_tile_clear_xy(x, y1)) return false;
            }
        }
    }
    return true;
}


void check_for_shot_at_tank(void) {
    Point8* tank_position = get_tank_position();
    uint8_t tank_tile_x = tank_position->x >> HARDWARE_TILE_SIZE_EXP;
    uint8_t tank_tile_y = tank_position->y >> HARDWARE_TILE_SIZE_EXP;
    for(Enemy *enemy = enemies, *end = enemies + num_enemies; enemy < end; enemy++) {
        if (enemy->type != TURRET) continue; // TODO: handle tank
        uint8_t enemy_tile_x = enemy->data.enemy_turret.position.x >> HARDWARE_TILE_SIZE_EXP;
        uint8_t enemy_tile_y = enemy->data.enemy_turret.position.y >> HARDWARE_TILE_SIZE_EXP;
        uint8_t enemy_orientation = enemy->data.enemy_turret.orientation;
        
        bool tank_in_line_of_sight = false;
        if (tank_tile_x == enemy_tile_x) {
            if (tank_tile_y < enemy_tile_y && enemy_orientation == NORTH) {
                tank_in_line_of_sight = true;
            } else if (tank_tile_y > enemy_tile_y && enemy_orientation == SOUTH) {
                tank_in_line_of_sight = true;
            }
        } else if (tank_tile_y == enemy_tile_y) {
            if (tank_tile_x < enemy_tile_x && enemy_orientation == WEST) {
                tank_in_line_of_sight = true;
            } else if (tank_tile_x > enemy_tile_x && enemy_orientation == EAST) {
                tank_in_line_of_sight = true;
            }
        }
        if (tank_in_line_of_sight && line_clear(tank_tile_x, tank_tile_y, enemy_tile_x, enemy_tile_y)) {
            destroy_tank();
        }
    }
}