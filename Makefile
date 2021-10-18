CC = gcc
CFLAGS = -std=c99 -pedantic -Wall -Wno-deprecated-declarations -Os
LIBS = -lX11 -lvulkan
LDFLAGS = -shared ${LIBS}
TARGET = libjz_wind.so

SRC = src/input.c src/vulkan.c src/window.c src/platform/x11_native.c
OBJ = ${SRC:.c=.o}

all: options $(TARGET)

options:
	@echo jz wind build options:
	@echo "CFLAGS = ${CFLAGS}"
	@echo "LDFLAGS = ${LDFLAGS}"
	@echo "CC = ${CC}"

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(TARGET) $(OBJ)

clean:
	rm -f $(OBJ) $(TARGET)
