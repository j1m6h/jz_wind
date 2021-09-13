#include "x11_window.h"
#include "../input.h"
#include "../window.h"

const int keysym_to_key(KeySym sym);

void platform_create_window(window* win)
{
	win->pf.display = XOpenDisplay((char*)0);

	int screen = DefaultScreen(win->pf.display);
	win->pf.handle = XCreateSimpleWindow(win->pf.display, RootWindow(win->pf.display, screen), 20, 20, win->width, win->height, 0, 0, 0);
	XStoreName(win->pf.display, win->pf.handle, win->title);

	/* the types of events we want to receive */
	long event_mask = EnterWindowMask | LeaveWindowMask | ExposureMask |
        	KeyPressMask | KeyReleaseMask |
        	ButtonPressMask | ButtonReleaseMask | ButtonMotionMask | PointerMotionMask |
        	StructureNotifyMask | SubstructureNotifyMask;

	XSelectInput(win->pf.display, win->pf.handle, event_mask);
}

void platform_set_window_title(window* win, const char* title)
{
	XmbSetWMProperties(win->pf.display, win->pf.handle, 
		title, title, NULL, 0, NULL, NULL, NULL);
}

void platform_show_window(window* win)
{
	XMapWindow(win->pf.display, win->pf.handle);
}

void platform_hide_window(window* win)
{
	XUnmapWindow(win->pf.display, win->pf.handle);
}

static void process_event(window* win, XEvent* xevent)
{
	int keycode = 0;
	if (xevent->type == KeyPress || xevent->type == KeyRelease)
		keycode = xevent->xkey.keycode;

	switch (xevent->type)
	{
		case KeyPress:
		{
			KeySym sym = XLookupKeysym(&xevent->xkey, 1);
			const int key = keysym_to_key(sym);
			input_key(win, key, ACTION_PRESSED);
			break;
		}
		case KeyRelease:
		{
			KeySym sym = XLookupKeysym(&xevent->xkey, 1);
			const int key = keysym_to_key(sym);

			/* by default key repeat events are not a thing in X, if a key is held it will arrive as "KeyPress/KeyRelease" pair
			all we want is KeyPress, so we will filter out the repeated KeyRelease events */
			if (XEventsQueued(win->pf.display, 1))
			{
				XEvent next;
				XPeekEvent(win->pf.display, &next);

				if (next.type == KeyPress && next.xkey.window == xevent->xkey.window && next.xkey.keycode == keycode)
				{
					/* if the timestamps of the KeyPress/KeyRelease events don't match */
					if ((next.xkey.time - xevent->xkey.time) < 20)
					{
						return;
					}
				}
			}

			input_key(win, key, ACTION_RELEASED);
			break;
		}
		case ButtonPress:
		{
			if (xevent->xbutton.button == Button1)
				input_mouse_click(win, MOUSE_BTN_LEFT, ACTION_PRESSED);
			else if (xevent->xbutton.button == Button2)
				input_mouse_click(win, MOUSE_BTN_MIDDLE, ACTION_PRESSED);
			else if (xevent->xbutton.button == Button3)
				input_mouse_click(win, MOUSE_BTN_RIGHT, ACTION_PRESSED);
			break;
		}
		case ButtonRelease:
		{
			if (xevent->xbutton.button == Button1)
				input_mouse_click(win, MOUSE_BTN_LEFT, ACTION_RELEASED);
			else if (xevent->xbutton.button == Button2)
				input_mouse_click(win, MOUSE_BTN_MIDDLE, ACTION_RELEASED);
			else if (xevent->xbutton.button == Button3)
				input_mouse_click(win, MOUSE_BTN_RIGHT, ACTION_RELEASED);
			break;
		}
		default:
		{
			break;
		}
	}
}

void platform_poll_events(window* win)
{
	XPending(win->pf.display);
	while (QLength(win->pf.display))
	{
		XEvent event;
		XNextEvent(win->pf.display, &event);
		process_event(win, &event);
	}

	XFlush(win->pf.display);
}

/* much more simple compared to GLFW's method createKeyTables */
const int keysym_to_key(KeySym sym)
{
	switch (sym)
	{
		case XK_A: return KEY_A;
		case XK_B: return KEY_B;
		case XK_C: return KEY_C;
		case XK_D: return KEY_D;
		case XK_E: return KEY_E;
		case XK_F: return KEY_F;
		case XK_G: return KEY_G;
		case XK_H: return KEY_H;
		case XK_I: return KEY_I;
		case XK_J: return KEY_J;
		case XK_K: return KEY_K;
		case XK_L: return KEY_L;
		case XK_M: return KEY_M;
		case XK_N: return KEY_N;
		case XK_O: return KEY_O;
		case XK_P: return KEY_P;
		case XK_Q: return KEY_Q;
		case XK_R: return KEY_R;
		case XK_S: return KEY_S;
		case XK_T: return KEY_T;
		case XK_U: return KEY_U;
		case XK_V: return KEY_V;
		case XK_W: return KEY_W;
		case XK_X: return KEY_X;
		case XK_Y: return KEY_Y;
		case XK_Z: return KEY_Z;
	}

	return KEY_UNKNOWN;
}
