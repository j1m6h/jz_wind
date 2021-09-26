#include "input.h"
#include "natives.h"
#include "window.h"
#include "../inc/jz_wind.h"

/* swap provided pointers, particularily our callbacks */
#define SWAP_POINTERS(x, y)	\
	{		    	\
		void* t;    	\
		t = x;	    	\
		x = y;	    	\
		y = t;	    	\
	}

void input_key(window* win, int key, int action)
{
	if (win->callbacks.key)
		win->callbacks.key(win, key, action);
}

void input_mouse_click(window* win, int btn, int action)
{
	if (win->callbacks.mouse_btn)
		win->callbacks.mouse_btn(win, btn, action);
}

void input_cursor_pos(window* win, int x, int y)
{
	if (win->callbacks.cursor_pos)
		win->callbacks.cursor_pos(win, x, y);
}

void input_cursor_enter(window* win, int enter)
{
	if (win->callbacks.cursor_enter)
		win->callbacks.cursor_enter(win, enter);
}

void input_window_size(window* win, int x, int y, int width, int height)
{
	if (win->callbacks.win_size)
		win->callbacks.win_size(win, x, y, width, height);
}

void input_window_close_req(window* win)
{
	win->is_open = JZ_FALSE;
	if (win->callbacks.close)
		win->callbacks.close(win);
}

void get_cursor_pos(window* win, int* x, int* y)
{
	native_get_cursor_pos(win, x, y);
}

void set_cursor_pos(window* win, int x, int y)
{
	native_set_cursor_pos(win, x, y);
}

keyboard_callback set_keyboard_callback(window* win, keyboard_callback callback)
{
	SWAP_POINTERS(win->callbacks.key, callback);
	return callback;
}

mouse_callback set_mouse_callback(window* win, mouse_callback callback)
{
	SWAP_POINTERS(win->callbacks.mouse_btn, callback);
	return callback;
}
