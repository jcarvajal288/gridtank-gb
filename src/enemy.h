#ifndef GT_ENEMY_H
#define GT_ENEMY_H

#include "enemy_tank.h"
#include "enemy_turret.h"

typedef enum {
    TANK,
    TURRET,
} EnemyType;

typedef union {
    EnemyTank enemy_tank;
    EnemyTurret enemy_turret;
} EnemyUnion;

typedef struct {
    EnemyType type;
    EnemyUnion data;
} Enemy;

void add_turret(uint8_t, uint8_t, CardinalDirection*);
void add_tank(uint8_t, uint8_t);
void update_enemies(uint8_t);
uint8_t draw_enemies(uint8_t);

void check_for_shot_at_tank(void);

#endif