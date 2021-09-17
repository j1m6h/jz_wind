#include "natives.h"
#include "../inc/jz_wind.h"

static char* exts[2];
const char** get_required_instance_exts(uint32_t* count)
{
	*count = 0;
	native_get_required_instance_exts(exts);
	return (const char**)exts;
}

VkResult create_vulkan_surface(VkInstance instance, window* win, 
	const VkAllocationCallbacks* allocator, VkSurfaceKHR* surface)
{
	return native_create_vulkan_surface(instance, win, allocator, surface);
}
