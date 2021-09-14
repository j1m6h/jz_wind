#include <malloc.h>
#include "natives.h"
#include "window.h"

window* create_window(const char* title, int width, int height)
{
	window* win = calloc(1, sizeof(window));
	win->width = width;
	win->height = height;
	native_create_window(win);
	set_window_title(win, title);
	win->is_open = JZ_TRUE;
    	return win;
}

void destroy_window(window* win)
{
    	free(win);
}

void set_window_title(window* win, const char* title)
{
	native_set_window_title(win, title);
}

void show_window(window* win)
{
	native_show_window(win);
}

void hide_window(window* win)
{
	native_hide_window(win);
}

void get_window_size(window* win, int* width, int* height)
{
	*width = win->width;
	*height = win->height;
}

int window_is_open(window* win)
{
	return win->is_open;
}

void poll_events(window* win)
{
	native_poll_events(win);
}
