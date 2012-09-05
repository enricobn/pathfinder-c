#CPPFLAGS = -lglut -lGLU
all : path_example.bin list_test.bin field_test.bin move_example.bin

move_example.bin : move_example.o astar_pathfinder.o cpathfinder.h list.o field.o
	@echo 'Building $@'
	cc -g -lglut -lGLU $^ -o $@

path_example.bin : path_example.o astar_pathfinder.o cpathfinder.h list.o field.o
	@echo 'Building $@'
	cc -g -lglut -lGLU $^ -o $@

field_test.bin : field_test.o list.o field.o 
	@echo 'Building $@'
	cc -g $^ -o $@

list_test.bin : list_test.o list.o 
	@echo 'Building $@'
	cc -g $^ -o $@

%.o : %.c 
	@echo 'Compiling $<'
	cc -O2 -std=c99 -pedantic -save-temps -Wall -c $<

.PHONY : clean

clean :
	rm -f *.bin; rm -f *.o; rm -f *.i; rm -f *.s;
