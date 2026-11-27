#ifndef GT_ENEMY_TANK_H
#define GT_ENEMY_TANK_H

#include <stdint.h>

#include "constants.h"
#include "point.h"


typedef struct {
    Point8 position;
    CardinalDirection body_orientation;
    CardinalDirection turret_orientation;
    CardinalDirection movement_direction;
    CardinalDirection pattern[NUM_GAME_TICKS];
    Point8 movement_destination;
    uint8_t animation_frame_counter;
} EnemyTank;


void init_enemy_tank(void);
uint8_t draw_enemy_tank(EnemyTank*, uint8_t);
void update_enemy_tank(EnemyTank*, uint8_t);

#endif