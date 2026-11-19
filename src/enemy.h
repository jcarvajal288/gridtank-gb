#ifndef GT_ENEMY_H
#define GT_ENEMY_H

#include "enemy_turret.h"

typedef union {
    EnemyTurret enemy_turret;
} Enemy;

void add_turret(uint8_t, uint8_t);
void update_enemies(Point8*);
uint8_t draw_enemies(uint8_t);

#endif