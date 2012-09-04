#CPPFLAGS = -lglut -lGLU
all : path_example.bin list_test.bin

path_example.bin : path_example.o astar_path_finder.o cpathfinder.h
	@echo 'Building $@'
	cc -lglut -lGLU $^ -o $@

list_test.bin : list_test.o list.o 
	@echo 'Building $@'
	cc $^ -o $@

%.o : %.c 
	@echo 'Compiling $<'
	cc -std=c99 -pedantic -save-temps -Wall -c $<

.PHONY : clean

clean :
	rm -f *.bin; rm -f *.o; rm -f *.i; rm -f *.s;