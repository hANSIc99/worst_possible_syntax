#gcc flags:
# -c assemble but do not link
# -g include debug information
# -o output
# -s make stripped libray

# uncomment the last part in line 9 to compile with debug symbold 
#-Wall
CFLAGS = -Werror -g 


all: function_pointer method_pointer
	

function_pointer: function_pointer.o
	gcc -o function_pointer function_pointer.o $(CFLAGS)

function_pointer.o: function_pointer.c
	 gcc -c function_pointer.c $(CFLAGS)

method_pointer: method_pointer.o
	c++ -o method_pointer method_pointer.o $(CFLAGS)

method_pointer.o: method_pointer.cpp
	c++ -c method_pointer.cpp $(CFLAGS)

.PHONY: clean
clean:
	rm *.o