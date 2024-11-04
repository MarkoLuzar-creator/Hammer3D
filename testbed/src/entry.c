#include "game.h"

#include <entry.h>
#include <core/memory.h>

b8 create_game(game* out_game)
{
    application_config app_config;
    app_config.start_pos_x = 0;
    app_config.start_pos_y = 0;
    app_config.start_width = 1280;
    app_config.start_heigth = 720;
    app_config.name = "test";

    out_game->app_config = app_config;
    out_game->render = game_render;
    out_game->update = game_update;
    out_game->initialize = game_initialize;
    out_game->on_resize = game_on_resize;
    out_game->state = allocate_memory(sizeof(game_state), MEMORY_TAG_GAME);

    return TRUE;
}