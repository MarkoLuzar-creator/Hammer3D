#include "application.h"

#include "game_types.h"

#include "platform/platform.h"

#include "core/logger.h"
#include "core/event.h"
#include "core/memory.h"
#include "core/input.h"
#include "core/clock.h"

typedef struct
{
    game* game_inst;
    platform_state platform;
    clock clock;
    b8 is_running;
    b8 is_suspended;
    u16 width;
    u16 heigth;
    f64 last_time;
} application_state;

static application_state app_state;

b8 application_on_event(u16 code, void* sender, void* listener_inst, event_context context);
b8 application_on_key(u16 code, void* sender, void* listener_inst, event_context context);

b8 application_create(game* game_inst)
{

    app_state.game_inst = game_inst;
    app_state.is_running = TRUE;
    app_state.is_suspended = FALSE;

    memory_initialize();
    logger_initialize();
    input_initialize();
    event_initialize();

    event_register(EVENT_CODE_APPLICATION_QUIT, 0, application_on_event);
    event_register(EVENT_CODE_KEY_PRESSED, 0, application_on_key);
    event_register(EVENT_CODE_BUTTON_RELEASED, 0, application_on_key);

    if(!platform_startup(&app_state.platform, game_inst->app_config.name, game_inst->app_config.start_pos_x, game_inst->app_config.start_pos_y, game_inst->app_config.start_width, game_inst->app_config.start_heigth)) 
    {
        return FALSE;
    }

    if (!app_state.game_inst->initialize(app_state.game_inst))
    {
        CHEAP_FATAL("Game failed to initialize");
        return FALSE;
    }

    app_state.game_inst->on_resize(app_state.game_inst, app_state.width, app_state.heigth);

    return TRUE;
}


b8 application_run()
{
    clock_start(&app_state.clock);
    clock_update(&app_state.clock);
    app_state.last_time = app_state.clock.elapsed_time;
    f64 running_time = 0;
    u8 frame_count = 0;
    f64 target_fps = 1.0f / 60;

    while(app_state.is_running)
    {
        if(!platform_pump_messages(&app_state.platform))
        {
            app_state.is_running = FALSE;
        }

        if (!app_state.is_suspended)
        {
            clock_update(&app_state.clock);
            f64 current_time = app_state.clock.elapsed_time;
            f64 delta = (current_time - app_state.last_time);
            f64 frame_start_time = platform_get_absolute_time();

            if(!app_state.game_inst->update(app_state.game_inst, (f32)delta))
            {
                CHEAP_FATAL("Game update failed shutting down!");
                app_state.is_running = FALSE;
                break;
            }
            
            if(!app_state.game_inst->render(app_state.game_inst, (f32)0))
            {
                CHEAP_FATAL("Game render failed shutting down!");
                app_state.is_running = FALSE;
                break;
            }

            f64 frame_end_time = platform_get_absolute_time();
            f64 frame_elapsed_time = frame_end_time - frame_start_time;
            running_time += frame_elapsed_time;
            f64 remaining_secods = target_fps - frame_elapsed_time;

            if (remaining_secods > 0)
            {
                u64 remaining_ms = (remaining_secods * 1000);
                b8 limit_frames = FALSE;
                if (remaining_ms > 0 && limit_frames)
                {
                    platform_sleep(remaining_ms - 1);
                }
                frame_count++;
            }

            input_update(delta);
            
        }
    }

    event_unregister(EVENT_CODE_APPLICATION_QUIT, 0, application_on_event);
    event_unregister(EVENT_CODE_KEY_PRESSED, 0, application_on_key);
    event_unregister(EVENT_CODE_BUTTON_RELEASED, 0, application_on_key);


    event_shutdown();
    input_shutdown();
    logger_shutdown();
    memory_shutdown();
    platform_shutdown(&app_state.platform);

    app_state.is_running = FALSE;

    return TRUE;
}

b8 application_on_event(u16 code, void* sender, void* listener_inst, event_context context)
{
    switch(code)
    {
        case EVENT_CODE_APPLICATION_QUIT: 
        {
            CHEAP_INFO("aplication quit event");
            app_state.is_running = FALSE;
            return TRUE;
        }
    }
    return FALSE;
}

b8 application_on_key(u16 code, void* sender, void* listener_inst, event_context context)
{
    if (code == EVENT_CODE_KEY_PRESSED)
    {
        u16 key_code = context.data.u16[0];
        if (key_code == KEY_ESCAPE)
        {
            event_context data = {};
            event_fire(EVENT_CODE_APPLICATION_QUIT, 0, data);
            return TRUE;
        } 
        else if(key_code == KEY_A)
        {
            CHEAP_DEBUG("a pressed");
        }
        else
        {
            CHEAP_DEBUG("'%c' key pressed in window: ", key_code);
        }
    }
    else if (code == EVENT_CODE_KEY_RELEASED)
    {
        u16 key_code = context.data.u16[0];
        if (key_code == KEY_B)
        {
            CHEAP_DEBUG("b key released");
        }
        else 
        {
            CHEAP_DEBUG("'%c' key released in window: ", key_code);
        }
    }
    return FALSE;
}