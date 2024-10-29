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

MAPI b8 application_create(struct game *game_inst);

MAPI b8 application_run();