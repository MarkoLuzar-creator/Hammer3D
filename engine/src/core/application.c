#include "application.h"

#include "game_types.h"

#include "platform/platform.h"

#include "core/memory.h"

#include "core/logger.h"

#include "core/event.h"

#include "core/input.h"

typedef struct application_state
{
    game* game_inst;
    platform_state platform;
    b8 is_running;
    b8 is_suspended;
    u16 width;
    u16 height;
    f64 last_time;
} application_state;

static b8 initialized = FALSE;
static application_state app_state;

b8 application_create(game* game_inst)
{
    if(initialized)
    {
        MOJERROR("application_create called more than once!");
        return FALSE;
    }

    initialize_memory();
    initialize_logging();
    initialize_input();
    
    
    app_state.game_inst = game_inst;
    app_state.is_running = TRUE;
    app_state.is_suspended = FALSE;

    MOJFATAL("A test message! %f", 3.24f);
    MOJWARING("A test message! %f", 3.24f);
    MOJERROR("A test message! %f", 3.24f);
    MOJINFO("A test message! %f", 3.24f);
    MOJTRACE("A test message! %f", 3.24f);
    MOJDEBUG("A test message! %f", 3.24f);

    if (!initialize_event())
    {
        MOJERROR("Event system failed initialization");
        return FALSE;
    }

    if(!platform_startup(&app_state.platform, game_inst->app_config.name, game_inst->app_config.start_pos_x, game_inst->app_config.start_pos_y, game_inst->app_config.start_width, game_inst->app_config.start_height)) 
    {
        return FALSE;
    }

    if (!app_state.game_inst->initialize(app_state.game_inst))
    {
        MOJFATAL("Game failed to initialize!");
        return FALSE;
    }

    app_state.game_inst->on_resize(app_state.game_inst, app_state.width, app_state.height);

    initialized = TRUE;

    return TRUE;
}


b8 application_run()
{
    MOJINFO(get_memory_usage_str());
    
    while(app_state.is_running)
    {
        if(!platform_pump_messages(&app_state.platform))
        {
            app_state.is_running = FALSE;
        }

        if (!app_state.is_suspended)
        {
            if(!app_state.game_inst->update(app_state.game_inst, 0))
            {
                MOJFATAL("Game update failed shutting down!");
                app_state.is_running = FALSE;
                break;
            }
            
            if(!app_state.game_inst->render(app_state.game_inst, (f32)0))
            {
                MOJFATAL("Game render failed shutting down!");
                app_state.is_running = FALSE;
                break;
            }

            input_update(0);
        }
    }

    shutdown_event();

    shutdown_input();

    shutdown_memory();

    shutdown_logging();
    

    app_state.is_running = FALSE;

    platform_shutdown(&app_state.platform);

    return TRUE;
}