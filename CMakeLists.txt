cmake_minimum_required(VERSION 3.5)

project(jz_wind)

add_executable(${PROJECT_NAME}
	src/input.c
	src/main.c
	src/window.c
	src/platform/x11_native.c)

find_package(X11 REQUIRED)
target_link_libraries(${PROJECT_NAME} ${X11_LIBRARIES})
