#ifndef GT_ENEMY_TANK_H
#define GT_ENEMY_TANK_H

#include <stdint.h>

#include "constants.h"
#include "point.h"

typedef enum {
    MOVE_FORWARD,
    MOVE_BACKWARD,
    ROTATE_LEFT,
    ROTATE_RIGHT,
    ROTATE_TURRET_LEFT,
    ROTATE_TURRET_RIGHT
} TankDirection;


typedef struct {
    Point8 position;
    CardinalDirection body_orientation;
    CardinalDirection turret_orientation;
    CardinalDirection movement_direction;
    TankDirection pattern[16];
    Point8 movement_destination;
    uint8_t animation_frame_counter;
} EnemyTank;


void init_enemy_tank(void);
uint8_t draw_enemy_tank(EnemyTank*, uint8_t);
void et_move_forward(EnemyTank*);
void et_move_backward(EnemyTank*);
void et_rotate_body_right(EnemyTank*);
void et_rotate_body_left(EnemyTank*);
void et_rotate_turret_right(EnemyTank*);
void et_rotate_turret_left(EnemyTank*);
void update_enemy_tank(EnemyTank*, uint8_t);

#endif