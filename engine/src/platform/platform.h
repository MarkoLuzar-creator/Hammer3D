#pragma once

#include "defines.h"

typedef struct
{
    void* internal_state;
} platform_state;

b8 platform_startup(platform_state* plat_state, const char* application_name, u16 x, u16 y, u16 width, u16 heigth);
void platform_shutdown(platform_state* plat_state);

b8 platform_pump_messages(platform_state* plat_state);

void* platform_allocate(u64 size, b8 aligned);
void* platform_zero_memory(void* block, u64 size);
void* platform_copy_memory(void* dest, const void* source, u64 size);
void* platform_set_memory(void* dest, i32 value, u64 size);
void platform_free(void* block, b8 aligned);

void platform_console_write(const char* msg, u8 colour);
void platform_console_write_error(const char* msg, u8 colour);

f64 platform_get_absolute_time();
void platform_sleep(u64 ms);