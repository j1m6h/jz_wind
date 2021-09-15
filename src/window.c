#include <string.h>
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

int window_is_open(window* win)
{
	return win->is_open;
}

void destroy_window(window* win)
{
	/* clear callbacks */
	memset(&win->callbacks, 0, sizeof(win->callbacks));
	/* destroy native window */
	native_destroy_window(win);
	/* destroy logical user window */
    	free(win);
}

void show_window(window* win)
{
	native_show_window(win);
}

void hide_window(window* win)
{
	native_hide_window(win);
}

void set_window_title(window* win, const char* title)
{
	native_set_window_title(win, title);
}

void get_window_size(window* win, int* width, int* height)
{
	*width = win->width;
	*height = win->height;
}

void set_window_size(window* win, int width, int height)
{
	native_set_window_size(win, width, height);
}

void poll_events(window* win)
{
	native_poll_events(win);
}

void wait_events(window* win)
{
	native_wait_events(win);
}
