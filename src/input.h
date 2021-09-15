#ifndef INPUT_H
#define INPUT_H

typedef struct window window;

void input_key(window* win, int key, int action);
void input_mouse_click(window* win, int btn, int action);
void input_window_close_req(window* win);
#endif
