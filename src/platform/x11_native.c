#include <stdint.h>
#include <string.h>
#include <sys/select.h>
#include "../config.h"
#include "../input.h"
#include "../natives.h"
#include "../window.h"
/* vulkan_xlib.h must be included after Xlib.h */
#include <vulkan/vulkan.h>
#include <vulkan/vulkan_xlib.h>

const int keysym_to_key(KeySym sym);

static void set_protocols(window* win)
{
	Atom wm_protocols = XInternAtom(win->pf.display, "WM_PROTOCOLS", False);
	Atom wm_delete = XInternAtom(win->pf.display, "WM_DELETE_WINDOW", False);

	/* make sure to allow accepting the window managers delete message */
	XChangeProperty(win->pf.display, win->pf.handle, wm_protocols, XA_ATOM, 32, PropModeReplace,
			(const unsigned char*)&wm_delete, 1);
}

void native_create_window(window* win)
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
	set_protocols(win);
}

void native_destroy_window(window* win)
{
	if (win->pf.handle)
	{
		XDestroyWindow(win->pf.display, win->pf.handle);
		win->pf.handle = (Window)0;
	}

	XCloseDisplay(win->pf.display);
}

void native_show_window(window* win)
{
	XMapWindow(win->pf.display, win->pf.handle);
	XFlush(win->pf.display);
}

void native_hide_window(window* win)
{
	XUnmapWindow(win->pf.display, win->pf.handle);
	XFlush(win->pf.display);
}

void native_set_window_title(window* win, const char* title)
{
	XmbSetWMProperties(win->pf.display, win->pf.handle, 
		title, title, NULL, 0, NULL, NULL, NULL);
}

void native_set_window_size(window* win, int width, int height)
{
	XResizeWindow(win->pf.display, win->pf.handle, width, height);
	XFlush(win->pf.display);
}

void native_get_cursor_pos(window* win, int* x, int* y)
{
	Window root, child;
	int rootx, rooty;
	int childx, childy;
	unsigned int mask;
	XQueryPointer(win->pf.display, win->pf.handle, &root, &child, &rootx, &rooty, &childx, &childy, &mask);

	if (x)
		*x = childx;
	if (y)
		*y = childy;
}

void native_set_cursor_pos(window* win, int x, int y)
{
	XWarpPointer(win->pf.display, None, win->pf.handle, 0, 0, 0, 0, x, y);
	XFlush(win->pf.display);
}

void native_get_required_instance_exts(char** exts)
{
	exts[0] = "VK_KHR_surface";
	exts[1] = "VK_KHR_xlib_surface";
}

VkResult native_create_vulkan_surface(VkInstance instance, window* win, const VkAllocationCallbacks* allocator, VkSurfaceKHR* surface)
{
	VkResult res;
	VkXlibSurfaceCreateInfoKHR create_info;
	PFN_vkCreateXlibSurfaceKHR vkCreateXlibSurfaceKHR;

	vkCreateXlibSurfaceKHR = (PFN_vkCreateXlibSurfaceKHR)
		vkGetInstanceProcAddr(instance, "vkCreateXlibSurfaceKHR");
	if (!vkCreateXlibSurfaceKHR)
	{
		/* missing VK_KHR_xlib_surface extension */
	}

	memset(&create_info, 0, sizeof(create_info));
	create_info.sType = VK_STRUCTURE_TYPE_XLIB_SURFACE_CREATE_INFO_KHR;
	create_info.dpy = win->pf.display;
	create_info.window = win->pf.handle;

	res = vkCreateXlibSurfaceKHR(instance, &create_info, allocator, surface);
	if (res)
	{
		/* failed to create surface */
	}

	return res;
}

static void process_event(window* win, XEvent* xevent)
{
	int keycode = 0;
	if (xevent->type == KeyPress || xevent->type == KeyRelease)
		keycode = xevent->xkey.keycode;

	switch (xevent->type)
	{
		/* usually this is where we can communicate with the window manager
		 * if we want to handle a close event, this is where we would do so.
		 * X has no official support for handling window close events, that's
		 * the window managers job */ 
		case ClientMessage:
		{
			Atom wm_delete = XInternAtom(win->pf.display, "WM_DELETE_WINDOW", False);
			XSetWMProtocols(win->pf.display, win->pf.handle, &wm_delete, True);

			if (xevent->xclient.data.l[0] == wm_delete)
				input_window_close_req(win);
			break;
		}
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
			 * all we want is KeyPress, so we will filter out the repeated KeyRelease events */
			if (XEventsQueued(win->pf.display, 1))
			{
				XEvent next;
				XPeekEvent(win->pf.display, &next);

				if (next.type == KeyPress && next.xkey.window == xevent->xkey.window && next.xkey.keycode == keycode)
				{
					/* if the timestamps of the KeyPress/KeyRelease events don't match */
					if ((next.xkey.time - xevent->xkey.time) < 20)
						return;
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
		case MotionNotify:
		{
			const int x = xevent->xmotion.x;
			const int y = xevent->xmotion.y;
			input_cursor_pos(win, x, y);
			break;
		}
		case EnterNotify:
		{
			input_cursor_enter(win, 1);
			break;
		}
		case LeaveNotify:
		{
			input_cursor_enter(win, 0);
			break;
		}
		default:
		{
			break;
		}
	}
}

void native_poll_events(window* win)
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

static int wait_for_event(Display* display)
{
	fd_set fds;
	const int fd = ConnectionNumber(display);
	int count = fd + 1;

	for (;;)
	{
		FD_ZERO(&fds);
		FD_SET(fd, &fds);

		struct timeval tv;
		tv.tv_usec = 0;
		tv.tv_sec = 1;

		const int res = select(count, &fds, NULL, NULL, &tv);

		if (res > 0)
			return 1;
	}

	return 0;
}

void native_wait_events(window* win)
{
	while (!XPending(win->pf.display))
		wait_for_event(win->pf.display);

	native_poll_events(win);
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
		case XK_0: return KEY_0;
		case XK_1: return KEY_1;
		case XK_2: return KEY_2;
		case XK_3: return KEY_3;
		case XK_4: return KEY_4;
		case XK_5: return KEY_5;
		case XK_6: return KEY_6;
		case XK_7: return KEY_7;
		case XK_8: return KEY_8;
		case XK_9: return KEY_9;
		case XK_KP_0: return KEY_NUMPAD0;
		case XK_KP_1: return KEY_NUMPAD1;
		case XK_KP_2: return KEY_NUMPAD2;
		case XK_KP_3: return KEY_NUMPAD3;
		case XK_KP_4: return KEY_NUMPAD4;
		case XK_KP_5: return KEY_NUMPAD5;
		case XK_KP_6: return KEY_NUMPAD6;
		case XK_KP_7: return KEY_NUMPAD7;
		case XK_KP_8: return KEY_NUMPAD8;
		case XK_KP_9: return KEY_NUMPAD9;
		case XK_F1: return KEY_F1;
		case XK_F2: return KEY_F2;
		case XK_F3: return KEY_F3;
		case XK_F4: return KEY_F4;
		case XK_F5: return KEY_F5;
		case XK_F6: return KEY_F6;
	 	case XK_F7: return KEY_F7;
		case XK_F8: return KEY_F8;
		case XK_F9: return KEY_F9;
		case XK_F10: return KEY_F10;
		case XK_F11: return KEY_F11;
		case XK_F12: return KEY_F12;
		case XK_Shift_L: return KEY_LSHIFT;
		case XK_Control_L: return KEY_LCTRL;
		case XK_Alt_L: return KEY_LALT;
		case XK_Sys_Req: return KEY_LSYSTEM;
		case XK_Shift_R: return KEY_RSHIFT;
		case XK_Control_R: return KEY_RCTRL;
		case XK_Alt_R: return KEY_RALT;
		case XK_Tab: return KEY_TAB;
		case XK_Caps_Lock: return KEY_CAPSLOCK;
		case XK_Escape: return KEY_ESCAPE;
		case XK_Num_Lock: return KEY_NUMLOCK;
		case XK_KP_Divide: return KEY_DIVIDE;
		case XK_KP_Multiply: return KEY_MULTIPLY;
		case XK_KP_Subtract: return KEY_SUBTRACT;
		case XK_KP_Add: return KEY_ADD;
		case XK_KP_Enter: return KEY_ENTER;
		case XK_KP_Decimal: return KEY_DECIMAL;
		case XK_Up: return KEY_UP;
		case XK_Down: return KEY_DOWN;
		case XK_Left: return KEY_LEFT;
		case XK_Right: return KEY_RIGHT;
		case XK_Insert: return KEY_INSERT;
		case XK_Delete: return KEY_DELETE;
		case XK_Scroll_Lock: return KEY_SCROLLLOCK;
		case XK_Home: return KEY_HOME;
		case XK_End: return KEY_END;
		case XK_Pause: return KEY_PAUSE;
		case XK_Page_Up: return KEY_PAGEUP:
		case XK_Page_Down: return KEY_PAGEDOWN;
		case XK_period: return KEY_PERIOD;
		case XK_comma: return KEY_COMMA;
		case XK_apostraphe: return KEY_QUOTE;
		case XK_BackSpace: return KEY_BACKSPACE;
		case XK_bracketleft: return KEY_LBRACKET;
		case XK_bracketright: return KEY_RBRACKET;
		case XK_slash: return KEY_SLASH;
		case XK_backslash: return KEY_BACKSLASH;
		case XK_semicolon: return KEY_SEMICOLON;
		case XK_minus: return KEY_HYPHEN;
		case XK_plus: return KEY_EQUAL;
		case XK_Menu: return KEY_MENU;
		case XK_grave: return KEY_TILDE;
	}

	return KEY_UNKNOWN;
}
