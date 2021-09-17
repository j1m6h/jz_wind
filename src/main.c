#define JZ_INC_VK
#include "../inc/jz_wind.h"
#include <stdio.h>

void key_func(window* win, int key, int action)
{
	if (key == KEY_A && action == ACTION_PRESSED)
	{
		printf("A Key pressed");
		set_cursor_pos(win, 60, 100);
	}
	else if (key == KEY_A && action == ACTION_RELEASED)
	{
		printf("A Key released");
	}
}

void mouse_func(window* win, int btn, int action)
{
	if (btn == MOUSE_BTN_LEFT && action == ACTION_PRESSED)
	{
		int x, y;
		get_cursor_pos(win, &x, &y);
		printf("%i, %d", x, y);
		set_window_title(win, "Pressed");
	}
	else if (btn == MOUSE_BTN_LEFT && action == ACTION_RELEASED)
	{
		set_window_title(win, "Release");
	}
}

int main()
{
	window* win = create_window("Joszva V 0.0.1", 600, 400);
	show_window(win);
	set_keyboard_callback(win, key_func);
	set_mouse_callback(win, mouse_func);

	VkResult result;
	VkInstance instance;
	uint32_t count = 0;
	const char** exts;
	VkInstanceCreateInfo create_info;
	PFN_vkCreateInstance my_create;

	my_create = (PFN_vkCreateInstance)
		vkGetInstanceProcAddr(instance, "vkCreateInstance");

	create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	create_info.pApplicationInfo = NULL;
	create_info.pNext = NULL;
	create_info.flags = 0;
	
	exts = get_required_instance_exts(&count);
	set_window_title(win, exts[1]);

	create_info.enabledExtensionCount = count;
	create_info.ppEnabledExtensionNames = exts;
	create_info.enabledLayerCount = 0;

	result = my_create(&create_info, NULL, &instance);
	if (result == VK_SUCCESS)
	{
	}

	while (window_is_open(win))
	{
		wait_events(win);
	}

	destroy_window(win);
}
