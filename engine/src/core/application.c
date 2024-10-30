#include "application.h"

#include "game_types.h"

#include "platform/platform.h"

#include "core/memory.h"

#include "core/logger.h"

#include "core/event.h"

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
        MERROR("application_create called more than once!");
        return FALSE;
    }

    initialize_logging();
    
    app_state.game_inst = game_inst;
    app_state.is_running = TRUE;
    app_state.is_suspended = FALSE;

    MFATAL("A test message! %f", 3.24f);
    MWARNING("A test message! %f", 3.24f);
    MERROR("A test message! %f", 3.24f);
    MINFO("A test message! %f", 3.24f);
    MTRACE("A test message! %f", 3.24f);
    MDEBUG("A test message! %f", 3.24f);

    if (!event_initialize())
    {
        MERROR("Event system failed initialization");
        return FALSE;
    }

    if(!platform_startup(&app_state.platform, game_inst->app_config.name, game_inst->app_config.start_pos_x, game_inst->app_config.start_pos_y, game_inst->app_config.start_width, game_inst->app_config.start_height)) 
    {
        return FALSE;
    }

    if (!app_state.game_inst->initialize(app_state.game_inst))
    {
        MFATAL("Game failed to initialize!");
        return FALSE;
    }

    app_state.game_inst->on_resize(app_state.game_inst, app_state.width, app_state.height);

    initialized = TRUE;

    return TRUE;
}


b8 application_run()
{
    MINFO(get_memory_usage_str());
    
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
                MFATAL("Game update failed shutting down!");
                app_state.is_running = FALSE;
                break;
            }
            
            if(!app_state.game_inst->render(app_state.game_inst, (f32)0))
            {
                MFATAL("Game render failed shutting down!");
                app_state.is_running = FALSE;
                break;
            }
        }
    }

    event_shutdown();

    shutdown_logging();

    app_state.is_running = FALSE;

    platform_shutdown(&app_state.platform);

    return TRUE;
}