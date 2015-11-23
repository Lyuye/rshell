VPATH = src
CFLAGS = -g -Wall -Werror -ansi -pedantic
FILES = $(addprefix src/, rshell.cpp)


bin/rshell: rshell.cpp | bin
	g++ $(CFLAGS) $(FILES) -o $@

bin:
	mkdir bin

clean:
 	rm -rf bin
