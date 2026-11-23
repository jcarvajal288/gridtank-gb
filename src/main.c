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

    init_tank();
    init_turret();
    init_enemy_tank();
}

void create_enemies(void) {
    CardinalDirection pattern1[NUM_GAME_TICKS] = {
        NORTH,
        NORTH,
        EAST,
        EAST,
        SOUTH,
        SOUTH,
        WEST,
        WEST
    };
    add_turret(5, 5, pattern1);

    CardinalDirection pattern2[NUM_GAME_TICKS] = {
        EAST,
        EAST,
        EAST,
        EAST,
        SOUTH,
        SOUTH,
        SOUTH,
        SOUTH,
    };
    add_turret(4, 1, pattern2);

    add_tank(8, 3);
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
    create_enemies();

    uint8_t frame_counter = 0;
    uint8_t current_tick = 0;
    while(1) {
        update_input();
        update_tank(frame_counter);

        frame_counter++;
        if (frame_counter >= GAME_TICK_FRAME_LENGTH) {
            update_enemies(current_tick++);
            current_tick %= NUM_GAME_TICKS;
            frame_counter = 0;
        }

        check_for_shot_at_tank();

        draw();
        vsync();
    }
}