#ifndef WINDOW_IMPL_H
#define WINDOW_IMPL_H

#include "config.h"

#ifdef JZ_SYS_UNIX
#include "platform/x11_window.h"
typedef struct x11_window platform;
#endif
#ifdef JZ_SYS_WIN32
#include "platform/win32_window.h"
typedef struct win32_window platform;
#endif
#endif