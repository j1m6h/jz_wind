/* this is where we check which platform we are on
-> introduce the platform structures accordingly */

#ifndef WINDOW_IMPL_H
#define WINDOW_IMPL_H

#include "config.h"

#ifdef JZ_SYS_UNIX
#include "platform/x11_native.h"
typedef struct x11_window platform;
#endif
#ifdef JZ_SYS_WIN32
#include "platform/win32_native.h"
typedef struct win32_native platform;
#endif
#endif
