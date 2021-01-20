#gcc flags:
# -c assemble but do not link
# -g include debug information
# -o output
# -s make stripped libray

CFLAGS = -Werror -g 
CPPFLAGS = -Werror -std=c++14 -g 

all: function_pointer method_pointer
	

function_pointer: function_pointer.o
	gcc -o function_pointer function_pointer.o $(CFLAGS)

function_pointer.o: function_pointer.c
	 gcc -c function_pointer.c $(CFLAGS)

method_pointer: method_pointer.o
	c++ -o method_pointer method_pointer.o $(CPPFLAGS)

method_pointer.o: method_pointer.cpp
	c++ -c method_pointer.cpp $(CPPFLAGS)

.PHONY: clean
clean:
	rm *.o