#include "memory.h"

#include "core/logger.h"

#include "platform/platform.h"

#include  <string.h>

#include <stdio.h>

struct memory_stats
{
    u64 total_allocated;
    u64 tagged_allocations[MEMORY_TAG_MAX_TAGS];
};

static const char* memory_tag_string[MEMORY_TAG_MAX_TAGS] = {
    "UNKNOWN",
    "ARRAY",
    "DARRAY",
    "DICT",
    "RING_QUEUE",
    "BST",
    "STRING",
    "APPLICATION",
    "JOB",
    "EXTURE",
    "MATERIAL_INSTANCE",
    "RENDERER",
    "GAME",
    "TRANSFORM",
    "ENTITY",
    "ENTITY_NODE",
    "SCENE",
};

static struct memory_stats stats;

void initialize_memory()
{
    platform_zero_memory(&stats, sizeof(stats));
}

void shutdown_memory()
{

}

void* mallocate(u64 size, memory_tag tag)
{
    if (tag == MEMORY_TAG_UNKNOWN)
    {
        MOJWARING("mallocate called using MEMORY_TAG_UNKNOWN");
    }
    stats.total_allocated += size;
    stats.tagged_allocations[tag] += size;

    void* block = platform_allocate(size, FALSE);
    platform_zero_memory(block, size);
    return block;
}

void mfree(void* block, u64 size, memory_tag tag)
{
    if (tag == MEMORY_TAG_UNKNOWN)
    {
        MOJWARING("mallocate called using MEMORY_TAG_UNKNOWN");
    }
    stats.total_allocated -= size;
    stats.tagged_allocations[tag] -= size;
    platform_free(block, FALSE);
}

void* mzero_memory(void* block, u64 size)
{
    return platform_zero_memory(block, size);
}

void* mcopy_memory(void* dest, const void* source, u64 size)
{
    return platform_copy_memory(dest, source, size);
}

void* mset_memory(void* dest, i32 value, u64 size)
{
    return platform_set_memory(dest, value, size);
}

char* get_memory_usage_str()
{
    const u64 gib = 1024 * 1024 * 1024;
    const u64 mib = 1024 * 1024;
    const u64 kib = 1024;

    char buffer[8000] = "System memory use (tagged):\n";
    u64 offset = strlen(buffer);

    for (u32 i = 0; i < MEMORY_TAG_MAX_TAGS; ++i)
    {
        char unit[4] = "XiB";

        float ammount = 1.0f;

        if (stats.tagged_allocations[i] >= gib)
        {
            unit[0] = 'G';
            ammount = stats.tagged_allocations[i] / (float)gib;
        }
        else if (stats.tagged_allocations[i] >= mib)
        {
            unit[0] = 'M';
            ammount = stats.tagged_allocations[i] / (float)mib;
        }
        else if (stats.tagged_allocations[i] >= kib)
        {
            unit[0] = 'K';
            ammount = stats.tagged_allocations[i] / (float)kib;
        }
        else 
        {
            unit[0] = 'B';
            unit[1] = 0;
            ammount = (float)stats.tagged_allocations[i];
        }

        i32 length = snprintf(buffer + offset, 8000, "  %s: %.2f%s\n", memory_tag_string[i], ammount, unit);
        offset += length;
    }
    char* out_string = _strdup(buffer);

    return out_string;
}