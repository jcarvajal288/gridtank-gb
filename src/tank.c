#include "tank.h"

#include <gb/gb.h>

#include "../res/tank_body.h"

#include "constants.h"
#include "input.h"
#include "point.h"

typedef enum {
    IDLE,
    TURNING
} State;
State state = IDLE;

Point8 global_position;
CardinalDirection orientation;

void draw_tank_sprite(void) {
    switch(orientation) {
        case NORTH:
            move_metasprite_ex(tank_body_metasprites[0], 0, 0, 0, global_position.x, global_position.y + 8);
            break;
        case EAST:
            move_metasprite_ex(tank_body_metasprites[4], 0, 0, 0, global_position.x, global_position.y + 8);
            break;
        case SOUTH:
            move_metasprite_flipy(tank_body_metasprites[0], 0, 0, 0, global_position.x, global_position.y + 8);
            break;
        case WEST:
            move_metasprite_flipx(tank_body_metasprites[4], 0, 0, 0, global_position.x, global_position.y + 8);
            break;
    }
}

void init_tank(void) {
    state = IDLE;
    orientation = NORTH;
    global_position.x = 5 * TILE_SIZE;
    global_position.y = 7 * TILE_SIZE;
    OBP0_REG = DMG_PALETTE(DMG_DARK_GRAY, DMG_WHITE, DMG_LITE_GRAY, DMG_BLACK);
    set_sprite_data(0, tank_body_TILE_COUNT, tank_body_tiles);
    draw_tank_sprite(0);
}


void rotate_body_right(void) {
    switch(orientation) {
        case NORTH:
            orientation = EAST;
            break;
        case EAST:
            orientation = SOUTH;
            break;
        case SOUTH:
            orientation = WEST;
            break;
        case WEST:
            orientation = NORTH;
            break;
    }
    draw_tank_sprite();
}


void rotate_body_left(void) {
    switch(orientation) {
        case NORTH:
            orientation = WEST;
            break;
        case WEST:
            orientation = SOUTH;
            break;
        case SOUTH:
            orientation = EAST;
            break;
        case EAST:
            orientation = NORTH;
            break;
    }
    draw_tank_sprite();
}


State handle_idle_state(void) {
    if (right_pressed()) {
        rotate_body_right();
        return TURNING;
    } else if (left_pressed()) {
        rotate_body_left();
        return TURNING;
    }
}


void update_tank(void) {
    if (state == IDLE) {
        state = handle_idle_state();
    } else if (state == TURNING && no_direction_pressed()) {
        state = IDLE;
    }
}

