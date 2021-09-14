#include "input.h"
#include "natives.h"
#include "window.h"

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
