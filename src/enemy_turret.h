#ifndef GT_ENEMY_TURRET_H
#define GT_ENEMY_TURRET_H

#include <stdint.h>

#include "point.h"


void init_turret(void);
uint8_t draw_turret(uint8_t);
void update_turret(Point8*);

#endif