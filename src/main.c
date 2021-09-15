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

	int width, height;
	get_window_size(win, &width, &height);
	printf("Window Width : %i\nWindow Height : %i\n", width, height);

	while (window_is_open(win))
	{
		wait_events(win);
	}

	destroy_window(win);
}
