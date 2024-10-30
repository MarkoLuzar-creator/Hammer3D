#pragma once

#include "defines.h"

struct game;

typedef struct application_config
{
    u16 start_pos_x;
    u16 start_pos_y;
    u16 start_width;
    u16 start_height;
    char *name;
} application_config;

MOJAPI b8 application_create(struct game* game_inst);

MOJAPI b8 application_run();