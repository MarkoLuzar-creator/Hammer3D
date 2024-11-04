#pragma once

#include "defines.h"

typedef struct
{
    u16 start_pos_x;
    u16 start_pos_y;
    u16 start_width;
    u16 start_heigth;
    const char* name;
} application_config;

struct game;

CHEAP_API b8 application_create(struct game* game_inst);
CHEAP_API b8 application_run();