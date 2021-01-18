#gcc flags:
# -c assemble but do not link
# -g include debug information
# -o output
# -s make stripped libray

# uncomment the last part in line 9 to compile with debug symbold 

CFLAGS =-Wall -Werror -std=c++11 #-g 


all: function_pointer.o
	c++ -o function_pointer function_pointer.o $(CFLAGS)

function_pointer.o: function_pointer.c
	 c++ -c function_pointer.c $(CFLAGS)

.PHONY: clean
clean:
	rm *.o