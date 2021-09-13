#include "window.h"
#include "../inc/jz_wind.h"

/* swap provided pointers, particularily our callbacks */
#define SWAP_POINTERS(x, y) \
	{		    \
		void* t;    \
		t = x;	    \
		x = y;	    \
		y = t;	    \
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
