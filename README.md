#Why this one?
The idea behind this project was to make a simpler version of GLFW. One major difference compared to GLFW is this library doesn't include any built in OpenGL support.
This library will provide basic functions needed to get a vulkan window up and running, with no by default OpenGL support. I really believe that the more minimal the library 
is the better it will be. So this is a personal project I developed to have nothing more than a bare bones window, with a few integrated vulkan functions.

# How to compile
This library uses CMake as its build system, yes it's not needed but it's what is used. Other than that there are no dependencies other than X11 or Win32, and of course git if you chose.
	
	# Unix
	1. git clone https://github.com/joshuamatthewhagen/jz_wind
	2. cd jz_wind 
	3. mkdir build 
	4. cd build
	5. cmake ../
	6. make

	# Win32
	1. git clone https://github.com/joshuamatthewhagen/jz_wind
	2. Enter jz_wind folder 
	3. Create a new build directory and go in it
	4. cmake ../ 
	5. make

# Want to contribute?
Any contributers are welcome, as long as you believe in the minimal concept of this project. If it were meant to be big and bloated it would just be GLFW, SFML, or SDL.
