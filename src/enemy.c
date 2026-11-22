#include "enemy.h"

#include <gbdk/emu_debug.h>

#include "tank.h"

#define MAX_ENEMIES 2

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
        for (uint8_t i = 0; i < NUM_GAME_TICKS; i++) {
            turret.pattern[i] = pattern[i];
        }
    }

    enemies[num_enemies++].enemy_turret = turret;
}


void update_enemies(uint8_t current_tick) {
    for(uint8_t i = 0; i < num_enemies; i++) { // TODO: change to use advancing pointer
        update_turret(&enemies[i].enemy_turret, current_tick);
    }
}


uint8_t draw_enemies(uint8_t sprite_index) {
    for(uint8_t i = 0; i < num_enemies; i++) { // TODO: change to use advancing pointer
        sprite_index = draw_turret(&enemies[i].enemy_turret, sprite_index);
    }
    return sprite_index;
}


void check_for_shot_at_tank(void) {
    Point8* tank_position = get_tank_position();
    uint8_t tank_tile_x = tank_position->x >> HARDWARE_TILE_SIZE_EXP;
    uint8_t tank_tile_y = tank_position->y >> HARDWARE_TILE_SIZE_EXP;
    for(Enemy *enemy = enemies, *end = enemies + num_enemies; enemy < end; enemy++) {
        uint8_t enemy_tile_x = enemy->enemy_turret.position.x >> HARDWARE_TILE_SIZE_EXP;
        uint8_t enemy_tile_y = enemy->enemy_turret.position.y >> HARDWARE_TILE_SIZE_EXP;
        uint8_t enemy_orientation = enemy->enemy_turret.orientation;
        
        if (tank_tile_x == enemy_tile_x) {
            if (tank_tile_y < enemy_tile_y && enemy_orientation == NORTH) {
                EMU_printf("Fire NORTH\n");
            } else if (tank_tile_y > enemy_tile_y && enemy_orientation == SOUTH) {
                EMU_printf("Fire SOUTH\n");
            }
        } else if (tank_tile_y == enemy_tile_y) {
            if (tank_tile_x < enemy_tile_x && enemy_orientation == WEST) {
                EMU_printf("Fire WEST\n");
            } else if (tank_tile_x > enemy_tile_x && enemy_orientation == EAST) {
                EMU_printf("Fire EAST\n");
            }
        }
    }
}