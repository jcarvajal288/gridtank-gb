#ifndef GT_TANK_H
#define GT_TANK_H

#include <stdint.h>

#include "point.h"

void init_tank(void);
uint8_t draw_tank(uint8_t);
void update_tank(uint8_t);
Point8* get_tank_position(void);
void destroy_tank(void);

#endif