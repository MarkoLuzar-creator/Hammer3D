#include "application.h"

#include "game_types.h"

#include "logger.h"

#include "platform/platform.h"

typedef struct 
{
    game *game_inst;
    b8 is_running;
    b8 is_suspended;
    platform_state platform;
    u16 width;
    u16 height;
    f64 last_time;
} application_state;

static b8 initialized = FALSE;
static application_state app_state;


b8 application_create(game *game_inst)
{
    if(initialized)
    {
        KERROR("application_create called more than once!");
        return FALSE;
    }

    app_state.game_inst = game_inst;

    initialize_logging();

    KFATAL("A test message! %f", 3.24f);
    KWARNING("A test message! %f", 3.24f);
    KERROR("A test message! %f", 3.24f);
    KINFO("A test message! %f", 3.24f);
    KTRACE("A test message! %f", 3.24f);
    KDEBUG("A test message! %f", 3.24f);

    app_state.is_running = TRUE;
    app_state.is_suspended = FALSE;

    if(!platform_startup(&app_state.platform, game_inst->app_config.name, game_inst->app_config.start_pos_x, game_inst->app_config.start_pos_y, game_inst->app_config.start_width, game_inst->app_config.start_height)) 
    {
        return FALSE;
    }

    if (!app_state.game_inst->initialize(app_state.game_inst))
    {
        KFATAL("Game failed to initialize!");
        return FALSE;
    }

    app_state.game_inst->on_resize(app_state.game_inst, app_state.width, app_state.height);

    initialized = TRUE;

    return TRUE;
}


b8 application_run()
{
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
                KFATAL("Game update failed shutting down!");
                app_state.is_running = FALSE;
                break;
            }
            
            if(!app_state.game_inst->render(app_state.game_inst, (f32)0))
            {
                KFATAL("Game render failed shutting down!");
                app_state.is_running = FALSE;
                break;
            }
        }
    }

    app_state.is_running = FALSE;

    platform_shutdown(&app_state.platform);

    return TRUE;
}