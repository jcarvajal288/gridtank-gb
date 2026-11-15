#ifndef GT_INPUT_H
#define GT_INPUT_H

#include <stdbool.h>

#include "point.h"

void update_input(void);

bool no_direction_pressed(void);
bool up_pressed(void);
bool down_pressed(void);
bool left_pressed(void);
bool right_pressed(void);

bool b_pressed(void);
bool a_pressed(void);

#endif