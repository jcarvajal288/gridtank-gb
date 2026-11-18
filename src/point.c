#include "point.h"
#include <gbdk/emu_debug.h>

CardinalDirection nearest_cardinal_to(Point8* start, Point8* end) {
    int8_t dx = end->x - start->x;
    int8_t dy = end->y - start->y;
    uint8_t adx = (dx > 0) ? dx : -dx;
    uint8_t ady = (dy > 0) ? dy : -dy;

    if (dx == dy) {
        if (dx > 0 && dy > 0) {
            return EAST;
        } else {
            return WEST;
        }
    } else if (dx > dy) {
        if (ady > adx) {
            return NORTH;
        } else {
            return EAST;
        }
    } else if (ady > adx) {
        return SOUTH;
    } else {
        return WEST;
    }
}