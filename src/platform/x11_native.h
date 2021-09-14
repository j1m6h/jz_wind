#ifndef X11_WINDOW_H
#define X11_WINDOW_H

#include "../config.h"

struct x11_window
{
	Display* display;
	Window handle;
};
#endif