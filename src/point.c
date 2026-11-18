#include "point.h"
#include <gbdk/emu_debug.h>

CardinalDirection nearest_cardinal_to(Point8* start, Point8* end) {
    int8_t dx = end->x - start->x;
    int8_t dy = end->y - start->y;
    uint8_t adx = (dx > 0) ? dx : -dx;
    uint8_t ady = (dy > 0) ? dy : -dy;
    EMU_printf("######################\n");
    EMU_printf("(%d,%d); (%d,%d)\n", start->x, start->y, end->x, end->y);
    EMU_printf("dx,dy: %d,%d\n", dx, dy);

    if (dx > dy) {
        EMU_printf("dx > dy\n");
        if (ady > adx) {
            EMU_printf("ady > adx\n");
            EMU_printf("NORTH\n");
            return NORTH;
        } else {
            EMU_printf("ady <= adx\n");
            EMU_printf("EAST\n");
            return EAST;
        }
    } else if (ady > adx) {
        EMU_printf("ady > adx\n");
        EMU_printf("SOUTH\n");
        return SOUTH;
    } else {
        EMU_printf("ady <= adx\n");
        EMU_printf("dx <= 0\n");
        EMU_printf("WEST\n");
        return WEST;
    }
}