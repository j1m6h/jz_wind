#ifndef X11_WINDOW_H
#define X11_WINDOW_H

#include "../config.h"

struct x11_window
{
	Display* display;
	Window handle;
};

typedef struct window window;

void platform_create_window(window* win);
void platform_set_window_title(window* win, const char* title);
void platform_show_window(window* win);
void platform_hide_window(window* win);
void platform_poll_events(window* win);
#endif
