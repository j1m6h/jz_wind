#ifndef CONFIG_H
#define CONFIG_H

#if defined(__linux__) || defined(__linux)
#define JZ_SYS_UNIX
#endif
#endif

#ifdef JZ_SYS_UNIX
#include <X11/Xatom.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#endif