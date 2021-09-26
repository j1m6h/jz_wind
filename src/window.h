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
		cursor_pos_callback cursor_pos;
		cursor_enter_callback cursor_enter;
		window_size_callback win_size;
		window_close_callback close;
	} callbacks;
};
#endif
