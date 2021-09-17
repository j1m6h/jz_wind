#ifndef NATIVES_H
#define NATIVES_H

#include <stdint.h>
#include <vulkan/vulkan.h>

typedef struct window window;

void native_create_window(window* win);
void native_destroy_window(window* win);
void native_show_window(window* win);
void native_hide_window(window* win);
void native_set_window_title(window* win, const char* title);
void native_set_window_size(window* win, int width, int height);

void native_poll_events(window* win);
void native_wait_events(window* win);

void native_get_cursor_pos(window* win, int* x, int* y);
void native_set_cursor_pos(window* win, int x, int y);

void native_get_required_instance_exts(char** exts);
VkResult native_create_vulkan_surface(VkInstance, window* win,
	const VkAllocationCallbacks* allocator, VkSurfaceKHR* surface);
#endif
