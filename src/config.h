#ifndef CONFIG_H
#define CONFIG_H

#if defined(__linux__) || defined(__linux) || defined(__unix__)
#define JZ_SYS_UNIX
#elif defined(WIN32) || defined(_WIN32)
#define JZ_SYS_WIN32
#endif

#ifdef JZ_SYS_UNIX
#include <X11/Xatom.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#elif JZ_SYS_WIN32
#include <Windows.h>
#endif
#endif
