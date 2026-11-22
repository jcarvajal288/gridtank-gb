#ifndef GT_CONSTANTS_H
#define GT_CONSTANTS_H

#define TILE_SIZE 16
#define NUM_GAME_TICKS 8
#define GAME_TICK_FRAME_LENGTH 60
#define HARDWARE_TILE_SIZE_EXP 3 // refers to 2^3 = 8 which is the background tile size

typedef enum {
    NORTH,
    SOUTH,
    EAST,
    WEST
} CardinalDirection;

#endif
