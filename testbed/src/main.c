#include <core/logger.h>
#include <core/asserts.h>
#include <platform/platform.h>

int main()
{
    KFATAL("A test message! %f", 3.24f);
    KWARNING("A test message! %f", 3.24f);
    KERROR("A test message! %f", 3.24f);
    KINFO("A test message! %f", 3.24f);
    KTRACE("A test message! %f", 3.24f);
    KDEBUG("A test message! %f", 3.24f);

    platform_state state;
    if(platform_startup(&state, "Kohi Engine Testbed", 100, 100, 1280, 720)) 
    {
        while(TRUE)
        {
            platform_pump_messages(&state);
        }
    }
    platform_shutdown(&state);

    //KASSERT(0);
    return 0;
}