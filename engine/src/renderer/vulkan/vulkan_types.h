#pragma once

#include "defines.h"

#include <vulkan/vulkan.h>

typedef struct
{
    VkInstance instance;
    VkAllocationCallbacks* allocator;
} vulkan_context;