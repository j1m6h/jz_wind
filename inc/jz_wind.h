#ifndef JZ_WIND_H
#define JZ_WIND_H

#include <stdbool.h>

typedef struct window window;
typedef void (*keyboard_callback)(window* win, int key, int action);
typedef void (*mouse_callback)(window* win, int btn, int action);

enum keyboard
{
	KEY_A, KEY_B, KEY_C, KEY_D, KEY_E, KEY_F, KEY_G, KEY_H, KEY_I,
	KEY_J, KEY_K, KEY_L, KEY_M, KEY_N, KEY_O, KEY_P, KEY_Q, KEY_R,
	KEY_S, KEY_T, KEY_U, KEY_V, KEY_W, KEY_X, KEY_Y, KEY_Z,
	KEY_UNKNOWN
};

enum mouse
{
	MOUSE_BTN_LEFT,
	MOUSE_BTN_MIDDLE,
	MOUSE_BTN_RIGHT
};

enum actions
{
	ACTION_PRESSED,
	ACTION_RELEASED
};

window* create_window(const char* title, int width, int height);
void destroy_window(window* win);
void set_window_title(window* win, const char* title);
void show_window(window* win);
void hide_window(window* win);
void get_window_size(window* win, int* width, int* height);
bool window_is_open(window* win);
void poll_events(window* win);
keyboard_callback set_keyboard_callback(window* win, keyboard_callback callback);
mouse_callback set_mouse_callback(window* win, mouse_callback callback);
#endif
