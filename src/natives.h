#ifndef NATIVES_H
#define NATIVES_H

typedef struct window window;

void native_create_window(window* win);
void native_destroy_window(window* win);
void native_show_window(window* win);
void native_hide_window(window* win);
void native_set_window_title(window* win, const char* title);
void native_set_window_size(window* win, int width, int height);

void native_poll_events(window* win);
void native_wait_events(window* win);

void native_get_cursor_pos(window* win, int* x, int* y);
void native_set_cursor_pos(window* win, int x, int y);
#endif
