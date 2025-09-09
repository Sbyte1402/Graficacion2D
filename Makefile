cflags = -Wall -Werror -pedantic -std=c99 -O2
dflags = -Wall -Werror -pedantic -std=c99 -g

sdl_include = $(shell pkg-config --cflags sdl3)
sdl_lib = $(shell pkg-config --libs sdl3)

source = $(wildcard src/*.c) $(wildcard src/**/*.c)
DVAR = 

output = bin/render_cpu

build:
	gcc $(cflags) $(DVAR) $(source) -o $(output) $(sdl_include) $(sdl_lib) -lm
	@echo "\033[1;35mCompilo exitosamente!!!\033[0m"
run:
	./$(output)
