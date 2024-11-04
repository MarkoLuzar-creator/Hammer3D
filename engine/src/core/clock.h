#pragma once

#include "defines.h"

typedef struct
{
    f64 start_time;
    f64 elapsed_time;
} clock;

void clock_update(clock* clock);
void clock_start(clock* clock);
void clock_stop(clock* clock);