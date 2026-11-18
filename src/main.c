#include <gb/gb.h>
#include <gb/metasprites.h>
#include <gbdk/emu_debug.h>

#include "level.h"
#include "input.h"
#include "tank.h"
#include "enemy_turret.h"

void init_gfx(void) {
    BGP_REG = 0xE4;
    DISPLAY_ON;
    SHOW_BKG;
    SHOW_SPRITES;
    SPRITES_8x16;
    HIDE_WIN;
}

void draw(void) {
    uint8_t sprite_index = 0;
    sprite_index = draw_tank(sprite_index);
    sprite_index = draw_turret(sprite_index);
    hide_sprites_range(sprite_index, MAX_HARDWARE_SPRITES);
}

void main(void) {
    init_gfx();

    draw_level();
    init_tank();
    init_turret();

    while(1) {
        update_input();
        update_tank();
        if (!no_direction_pressed()) {
            update_turret(get_tank_position());
        }
        draw();
        vsync();
    }
}