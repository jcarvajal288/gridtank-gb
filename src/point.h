#ifndef LABYRINTH_POINT_H
#define LABYRINTH_POINT_H

#include <stdint.h>

#include "constants.h"

typedef struct {
    uint8_t x;
    uint8_t y;
} Point8;

CardinalDirection nearest_cardinal_to(Point8*, Point8*);

#endif