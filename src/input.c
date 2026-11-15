#include "input.h"

#include <gb/gb.h>
#include <stdint.h>

uint8_t joypadCurrent = 0;
uint8_t joypadPrevious = 0;

void update_input(void) {
    joypadPrevious = joypadCurrent;
    joypadCurrent = joypad();
}

bool no_direction_pressed(void) {
    return !(joypadCurrent & (J_UP | J_DOWN | J_LEFT | J_RIGHT));
}

bool up_pressed(void) {
    return joypadCurrent & J_UP;
}

bool down_pressed(void) {
    return joypadCurrent & J_DOWN;
}

bool left_pressed(void) {
    return joypadCurrent & J_LEFT;
}

bool right_pressed(void) {
    return joypadCurrent & J_RIGHT;
}

bool b_pressed(void) {
    return joypadCurrent & J_B;
}

bool a_pressed(void) {
    return joypadCurrent & J_A;
}