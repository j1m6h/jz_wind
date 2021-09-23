cmake_minimum_required(VERSION 3.5)

project(jz_wind)

if(UNIX)
	set(native_srcs
		src/platform/x11_native.c)
endif()
if (WIN32)
	set(native_srcs 
		src/platform/win32_native.c)
endif()

add_library(${PROJECT_NAME} SHARED
	src/input.c
	src/vulkan.c
	src/window.c
	${native_srcs})

find_package(X11 REQUIRED)
target_link_libraries(${PROJECT_NAME} ${X11_LIBRARIES})

find_package(Vulkan REQUIRED)
target_link_libraries(${PROJECT_NAME} Vulkan::Vulkan)
