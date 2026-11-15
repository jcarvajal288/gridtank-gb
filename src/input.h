#ifndef GT_INPUT_H
#define GT_INPUT_H

#include <stdbool.h>

void update_input(void);

bool no_direction_pressed(void);

bool up_pressed(void);
bool up_just_pressed(void);

bool down_pressed(void);
bool down_just_pressed(void);

bool left_pressed(void);
bool left_just_pressed(void);

bool right_pressed(void);
bool right_just_pressed(void);

bool b_pressed(void);
bool b_just_pressed(void);

bool a_pressed(void);
bool a_just_pressed(void);

#endif