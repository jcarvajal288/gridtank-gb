#include "point.h"

CardinalDirection nearest_cardinal_to(Point8* start, Point8* end) {
    uint8_t dx = end->x - start->x;
    uint8_t dy = end->y - start->y;

    if (dy > dx) {
        if (dy > 0) {
            return NORTH;
        } else {
            return WEST;
        }
    } else if (dx > 0) {
        return EAST;
    } else {
        return SOUTH;
    }
}