#ifndef WINDOW_H
#define WINDOW_H

#include "window_impl.h"
#include "../inc/jz_wind.h"

struct window
{
	char title[256];
	int width;
	int height;
	int is_open;
	platform pf;

	/* callbacks */
	struct {
		keyboard_callback key;
		mouse_callback mouse_btn;
		window_close_callback close;
	} callbacks;
};
#endif
