#pragma once

#include "core/application.h"
#include "core/logger.h"
#include "game_types.h"

extern b8 create_game(game* out_game);

int main()
{
    game game_inst;

    if (!create_game(&game_inst))
    {
        CHEAP_FATAL("Could not create game!");
        return 1;
    }

    if (!game_inst.render || !game_inst.update || !game_inst.initialize || !game_inst.on_resize || !game_inst.update)
    {
        CHEAP_FATAL("The game's function pointers must be assigned!");
        return 1;
    }

    if(!application_create(&game_inst))
    {
        CHEAP_INFO("Application failed to create!");
        return 1;
    }

    if(!application_run())
    {
        CHEAP_INFO("Application did not shutdown sucessfully!");
        return 1;
    }
    
    return 0;
}