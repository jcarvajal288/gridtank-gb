#ifndef GT_ENEMY_TURRET_H
#define GT_ENEMY_TURRET_H

#include <stdint.h>

#include "point.h"


typedef struct {
    Point8 position;
    CardinalDirection orientation;
} EnemyTurret;


void init_turret(void);
uint8_t draw_turret(EnemyTurret*, uint8_t);
void update_turret(EnemyTurret*, Point8*);

#endif