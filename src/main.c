#include <gb/gb.h>
#include <gb/metasprites.h>
#include <gbdk/emu_debug.h>

#include "enemy.h"
#include "level.h"
#include "input.h"
#include "tank.h"


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
    sprite_index = draw_enemies(sprite_index);
    hide_sprites_range(sprite_index, MAX_HARDWARE_SPRITES);
}

void main(void) {
    init_gfx();

    draw_level();
    init_tank();
    init_turret();

    add_turret(5, 5);
    add_turret(4, 1);

    while(1) {
        update_input();
        update_tank();
        if (!no_direction_pressed()) {
            update_enemies(get_tank_position());
        }
        draw();
        vsync();
    }
}