#include "core/application.h"

#include "game_types.h"

#include "core/logger.h"

#include "core/memory.h"

extern b8 create_game(game* out_game);

int main()
{

    initialize_memory();

    game game_inst;
    if (!create_game(&game_inst))
    {
        MOJFATAL("Could not create game!");
        return -1;
    }

    if (!game_inst.render || !game_inst.update || !game_inst.initialize || !game_inst.on_resize || !game_inst.update)
    {
        MOJFATAL("The game's function pointers must be assigned!");
        return -2;
    }

    if(!application_create(&game_inst))
    {
        MOJINFO("Application failed to create!");
        return 1;
    }

    if(!application_run())
    {
        MOJINFO("Application did not shutdown gracefully!");
        return 2;
    }
    
    return 0;
}