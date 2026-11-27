#ifndef GT_ENEMY_TURRET_H
#define GT_ENEMY_TURRET_H

#include <stdint.h>

#include "constants.h"
#include "point.h"


typedef struct {
    Point8 position;
    CardinalDirection orientation;
    CardinalDirection pattern[NUM_TURRET_TICKS];
} EnemyTurret;


void init_turret(void);
uint8_t draw_turret(EnemyTurret*, uint8_t);
void update_turret(EnemyTurret*, uint8_t);

#endif