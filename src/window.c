#include <malloc.h>

#include "vec2.h"
#include "window.h"

window* create_window(const char* title, int width, int height)
{
	window* win = calloc(1, sizeof(window));
	win->width = width;
	win->height = height;
	platform_create_window(win);
	set_window_title(win, title);
	win->is_open = true;
    	return win;
}

void destroy_window(window* win)
{
    	free(win);
}

void set_window_title(window* win, const char* title)
{
    	platform_set_window_title(win, title);
}

void show_window(window* win)
{
	platform_show_window(win);
}

void hide_window(window* win)
{
	platform_hide_window(win);
}

void get_window_size(window* win, int* width, int* height)
{
	*width = win->width;
	*height = win->height;
}

bool window_is_open(window* win)
{
	return win->is_open;
}

void poll_events(window* win)
{
	platform_poll_events(win);
}
