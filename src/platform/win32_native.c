#include "../natives.h"
#include "../window.h"
#include "../../inc/jz_wind.h"

#include <vulkan/vulkan.h>
#include <vulkan/vulkan_win32.h>

static window* _win;
static LRESULT CALLBACK win_proc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

void native_create_window(window* win)
{
	_win = win;
	WNDCLASSEX class_ex;

	class_ex.cbClsExtra = 0;
	class_ex.cbSize = sizeof(WNDCLASSEX);
	class_ex.cbWndExtra = 0;
	class_ex.hbrBackground = (HBRUSH)CreateSolidBrush(WHITE_BRUSH);
    	class_ex.hCursor = 0;
    	class_ex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    	class_ex.hIconSm = class_ex.hIcon;
    	class_ex.hInstance = GetModuleHandle(NULL);
    	class_ex.lpfnWndProc = &win_proc;
    	class_ex.lpszClassName = (LPCSTR)"Joszva_Window";
    	class_ex.lpszMenuName = NULL;
    	class_ex.style = 0;
    	if (!RegisterClassEx(&class_ex))
	{
		return;
	}

	win->pf.handle = CreateWindowEx(0, "Joszva_Window", "Joszva_Window", 
		WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFUALT, CW_USEDEFAULT, 
		CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, GetModuleHandle(NULL), NULL);

	UpdateWindow(win->pf.handle);
}

void native_destroy_window(window* win)
{
	DestroyWindow(win->pf.handle);
	free(_win);
	_win = (window*)0;
}

void native_show_window(window* win)
{
	ShowWindow(win->pf.handle, SW_SHOW);
	UpdateWindow(win->pf.handle);
}

void native_hide_window(window* win)
{
	ShowWindow(win->pf.handle, SW_HIDE);
	UpdateWindow(win->pf.handle);
}

void native_set_window_title(window* win, const char* title)
{
	SetWindowText(win->pf.handle, title);
	win->pf.title = title;
}

void native_set_window_size(window* win, int width, int height)
{
}

void native_poll_events(window* win)
{
	MSG msg;

	while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

void native_wait_events(window* win)
{
}

void native_get_cursor_pos(window* win, int* x, int* y)
{
}

void native_set_cursor_pos(window* win, int x, int y)
{
}

void native_get_required_instance_exts(char** exts)
{
}

VkResult native_create_vulkan_surface(VkInstance instance, window* win, 
	const VkAllocationCallbacks* allocator, VkSurfaceKHR* surface)
{
}

static LRESULT CALLBACK win_proc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch (msg)
	{
		case WM_LBUTTONDOWN:
		{
			input_mouse_click(_win, MOUSE_BTN_LEFT, ACTION_PRESSED);
			break;
		}
		case WM_LBUTTONUP:
		{
			input_mouse_click(_win, MOUSE_BTN_LEFT, ACTION_RELEASED);
			break;
		}
	}

	return DefWindowProc(hwnd, msg, wparam, lparam);
}
