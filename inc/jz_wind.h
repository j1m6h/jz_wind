#ifndef JZ_WIND_H
#define JZ_WIND_H

#ifdef JZ_INC_VK
#include <stdint.h>
#include <vulkan/vulkan.h>
#endif

#define JZ_TRUE 1
#define JZ_FALSE 0

typedef struct window window;

typedef void (*keyboard_callback)(window* win, int key, int action);
typedef void (*mouse_callback)(window* win, int btn, int action);
typedef void (*cursor_pos_callback)(window* win, int x, int y);
typedef void (*cursor_enter_callback)(window* win, int enter);
typedef void (*window_size_callback)(window* win, int x, int y, int width, int height);
typedef void (*window_close_callback)(window* win);

/* actions, used to detect key and mouse btn state */
enum actions
{
	ACTION_PRESSED,
	ACTION_RELEASED
}; 

/* mouse btns */
enum mouse
{
	MOUSE_BTN_LEFT,
	MOUSE_BTN_MIDDLE,
	MOUSE_BTN_RIGHT
};

/* keyboard keys */
enum keyboard
{
	KEY_A, KEY_B, KEY_C, KEY_D, KEY_E, KEY_F, KEY_G, KEY_H, KEY_I,
	KEY_J, KEY_K, KEY_L, KEY_M, KEY_N, KEY_O, KEY_P, KEY_Q, KEY_R,
	KEY_S, KEY_T, KEY_U, KEY_V, KEY_W, KEY_X, KEY_Y, KEY_Z, KEY_0,
	KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7, KEY_8, KEY_9,
	KEY_NUMPAD0, KEY_NUMPAD1, KEY_NUMPAD2, KEY_NUMPAD3, KEY_NUMPAD4,
	KEY_NUMPAD5, KEY_NUMPAD6, KEY_NUMPAD7, KEY_NUMPAD8, KEY_NUMPAD9,
	KEY_F1, KEY_F2, KEY_F3, KEY_F4, KEY_F5, KEY_F6, KEY_F7, KEY_F8,
	KEY_F9, KEY_F10, KEY_F11, KEY_F12, KEY_LSHIFT, KEY_LCTRL, KEY_LALT,
	KEY_LSYSTEM, KEY_RSHIFT, KEY_RCTRL, KEY_RALT, KEY_RSYSTEM, KEY_TAB,
	KEY_CAPSLOCK, KEY_ESCAPE, KEY_NUMLOCK, KEY_DIVIDE, KEY_MULTIPLY,
	KEY_SUBTRACT, KEY_ADD, KEY_ENTER, KEY_DECIMAL, KEY_UP, KEY_DOWN,
	KEY_LEFT, KEY_RIGHT, KEY_INSERT, KEY_DELETE, KEY_SCROLLLOCK,
	KEY_HOME, KEY_END, KEY_PAUSE, KEY_PAGEUP, KEY_PAGEDOWN, KEY_PERIOD,
	KEY_COMMA, KEY_QUOTE, KEY_BACKSPACE, KEY_LBRACKET, KEY_RBRACKET,
	KEY_SLASH, KEY_BACKSLASH, KEY_SEMICOLON, KEY_HYPHEN, KEY_EQUAL,
	KEY_MENU, KEY_TILDE, KEY_UNKNOWN
}; 

window* create_window(const char* title, int width, int height);
int window_is_open(window* win);
void destroy_window(window* win);
void show_window(window* win);
void hide_window(window* win);
void set_window_title(window* win, const char* title);
void get_window_size(window* win, int* width, int* height);
void set_window_size(window* win, int width, int height);

void poll_events(window* win);
void wait_events(window* win);

void get_cursor_pos(window* win, int* x, int* y);
void set_cursor_pos(window* win, int x, int y);

#ifdef JZ_INC_VK
const char** get_required_instance_exts(uint32_t* count);
VkResult create_vulkan_surface(VkInstance instance, window* win, 
	const VkAllocationCallbacks* allocator, VkSurfaceKHR* surface);
#endif

/* set event callbacks */
keyboard_callback set_keyboard_callback(window* win, keyboard_callback callback);
mouse_callback set_mouse_callback(window* win, mouse_callback callback);
cursor_pos_callback set_cursor_pos_callback(window* win, int x, int y);
cursor_enter_callback set_cursor_enter_callback(window* win, int enter);
window_size_callback set_window_size_callback(window* win, int x, int y, int width, int height);
window_close_callback set_window_close_callback(window* win);
#endif
