#include "tank.h"

#include <gb/gb.h>
#include <gbdk/emu_debug.h>

#include "../res/tank_body.h"

#include "constants.h"
#include "input.h"
#include "level.h"
#include "point.h"

#define TANK_SPEED 1
#define ANIMATION_FRAME_COUNT 4

typedef enum {
    IDLE,
    MOVING,
    TURNING
} State;
State state = IDLE;

Point8 global_position;
CardinalDirection orientation;
CardinalDirection movement_direction;
Point8 movement_destination;
uint8_t animation_frame_counter;


void draw_tank_sprite(void) {
    switch(orientation) {
        case NORTH:
            move_metasprite_ex(tank_body_metasprites[animation_frame_counter], 0, 0, 0, global_position.x, global_position.y + 8);
            break;
        case EAST:
            move_metasprite_ex(tank_body_metasprites[animation_frame_counter + 4], 0, 0, 0, global_position.x, global_position.y + 8);
            break;
        case SOUTH:
            move_metasprite_flipy(tank_body_metasprites[animation_frame_counter], 0, 0, 0, global_position.x, global_position.y + 8);
            break;
        case WEST:
            move_metasprite_flipx(tank_body_metasprites[animation_frame_counter + 4], 0, 0, 0, global_position.x, global_position.y + 8);
            break;
    }
}

void init_tank(void) {
    state = IDLE;
    orientation = NORTH;
    animation_frame_counter = 0;
    global_position.x = 5 * TILE_SIZE;
    global_position.y = 7 * TILE_SIZE;
    movement_destination = global_position;
    OBP0_REG = DMG_PALETTE(DMG_DARK_GRAY, DMG_WHITE, DMG_LITE_GRAY, DMG_BLACK);
    set_sprite_data(0, tank_body_TILE_COUNT, tank_body_tiles);
    draw_tank_sprite();
}


void start_move_forward(void) {
    switch(orientation) {
        case NORTH:
            movement_destination.x = global_position.x;
            movement_destination.y = global_position.y - TILE_SIZE;
            movement_direction = NORTH;
            break;
        case SOUTH:
            movement_destination.x = global_position.x;
            movement_destination.y = global_position.y + TILE_SIZE;
            movement_direction = SOUTH;
            break;
        case EAST:
            movement_destination.x = global_position.x + TILE_SIZE;
            movement_destination.y = global_position.y;
            movement_direction = EAST;
            break;
        case WEST:
            movement_destination.x = global_position.x - TILE_SIZE;
            movement_destination.y = global_position.y;
            movement_direction = WEST;
            break;
    }
}


void start_move_backward(void) {
    switch(orientation) {
        case NORTH:
            movement_destination.x = global_position.x;
            movement_destination.y = global_position.y + TILE_SIZE;
            movement_direction = SOUTH;
            break;
        case SOUTH:
            movement_destination.x = global_position.x;
            movement_destination.y = global_position.y - TILE_SIZE;
            movement_direction = NORTH;
            break;
        case EAST:
            movement_destination.x = global_position.x - TILE_SIZE;
            movement_destination.y = global_position.y;
            movement_direction = WEST;
            break;
        case WEST:
            movement_destination.x = global_position.x + TILE_SIZE;
            movement_destination.y = global_position.y;
            movement_direction = EAST;
            break;
    }
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
    if (up_pressed()) {
        start_move_forward();
        if (is_tile_clear(movement_destination)) {
            return MOVING;
        } else {
            movement_destination = global_position;
            return IDLE;
        }
    } else if (down_pressed()) {
        start_move_backward();
        if (is_tile_clear(movement_destination)) {
            return MOVING;
        } else {
            movement_destination = global_position;
            return IDLE;
        }
    } else if (right_pressed()) {
        rotate_body_right();
        return TURNING;
    } else if (left_pressed()) {
        rotate_body_left();
        return TURNING;
    }
    // if (global_position.x != movement_destination.x || global_position.y != movement_destination.y) {
    //     return MOVING;
    // }
    return IDLE;
}


State handle_moving_state(void) {
    if (movement_destination.y < global_position.y) { // move north
        global_position.y -= TANK_SPEED;
        if (global_position.y <= movement_destination.y) {
            global_position.y = movement_destination.y;
            return IDLE;
        }
    } else if (movement_destination.y > global_position.y) { // move south
        global_position.y += TANK_SPEED;
        if (global_position.y >= movement_destination.y) {
            global_position.y = movement_destination.y;
            return IDLE;
        }
    } else if (movement_destination.x > global_position.x) { // move east
        global_position.x += TANK_SPEED;
        if (global_position.x >= movement_destination.x) {
            global_position.x = movement_destination.x;
            return IDLE;
        }
    } else if (movement_destination.x < global_position.x) { // move west
        global_position.x -= TANK_SPEED;
        if (global_position.x <= movement_destination.x) {
            global_position.x = movement_destination.x;
            return IDLE;
        }
    }
    if (orientation == movement_direction) {
        animation_frame_counter++;
    } else {
        animation_frame_counter--;
    }
    animation_frame_counter %= ANIMATION_FRAME_COUNT;
    return MOVING;
}


void update_tank(void) {
    if (state == IDLE) {
        state = handle_idle_state();
    } else if (state == MOVING) {
        state = handle_moving_state();
    } else if (state == TURNING && no_direction_pressed()) {
        state = IDLE;
    }
    draw_tank_sprite();
}

