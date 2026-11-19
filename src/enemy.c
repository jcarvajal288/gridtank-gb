#include "enemy.h"

#define MAX_ENEMIES 2

static Enemy enemies[MAX_ENEMIES];
static uint8_t num_enemies = 0;

void add_turret(uint8_t x, uint8_t y) {
    if (num_enemies >= MAX_ENEMIES) {
        return;
    }

    EnemyTurret turret = {
        .position = { .x = x * TILE_SIZE, .y = y * TILE_SIZE},
        .orientation = NORTH
    };

    enemies[num_enemies++].enemy_turret = turret;
}


void update_enemies(Point8* player_position) {
    for(uint8_t i = 0; i < num_enemies; i++) {
        update_turret(&enemies[i].enemy_turret, player_position);
    }
}


uint8_t draw_enemies(uint8_t sprite_index) {
    for(uint8_t i = 0; i < num_enemies; i++) {
        sprite_index = draw_turret(&enemies[i].enemy_turret, sprite_index);
    }
    return sprite_index;
}