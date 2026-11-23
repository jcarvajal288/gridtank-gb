#ifndef GT_LEVEL_H
#define GT_LEVEL_H

#include <stdbool.h>

#include "point.h"

void draw_level(void);
bool is_tile_clear_xy(uint8_t, uint8_t);
bool is_tile_clear(Point8);

#endif