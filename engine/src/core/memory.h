#pragma once

#include "defines.h"

typedef enum
{
    MEMORY_TAG_UNKNOWN,
    MEMORY_TAG_ARRAY,
    MEMORY_TAG_DARRAY,
    MEMORY_TAG_DICT,
    MEMORY_TAG_RING_QUEUE,
    MEMORY_TAG_BST,
    MEMORY_TAG_STRING,
    MEMORY_TAG_APPLICATION,
    MEMORY_TAG_JOB,
    MEMORY_TAG_TEXTURE,
    MEMORY_TAG_MATERIAL_INSTANCE,
    MEMORY_TAG_RENDERER,
    MEMORY_TAG_GAME,
    MEMORY_TAG_TRANSFORM,
    MEMORY_TAG_ENTITY,
    MEMORY_TAG_ENTITY_NODE,
    MEMORY_TAG_SCENE,
    MEMORY_TAG_MAX_TAGS
} memory_tags;

HAPI void memory_initialize();
HAPI void memory_shutdown();

HAPI void* allocate_memory(u64 size, memory_tags tag);
HAPI void* zero_memory(void* block, u64 size);
HAPI void* copy_memory(void* dest, const void* source, u64 size);
HAPI void* set_memory(void* dest, i32 value, u64 size);
HAPI void free_memory(void* block, u64 size, memory_tags tag);

HAPI void print_memory_usage();