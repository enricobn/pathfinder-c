#SAVE-TEMPS = -save-temps
SAVE-TEMPS =
#PROFILER = -pg
PROFILER =
CC = cc
DEBUG = -g
#DEBUG =
CFLAGS = -Wall -c $(DEBUG) -std=c99 -O3 -pedantic $(SAVE-TEMPS) $(PROFILER)
LFLAGS = -Wall $(DEBUG) $(PROFILER) 
GL = -lglut -lGLU
LIB = /usr/local/lib/libJudy.a

all : path_example.bin list_test.bin field_test.bin move_example.bin

move_example.bin : move_example.o astar_pathfinder.o list.o field.o
	@echo 'Building $@'
	$(CC) $(LFLAGS) $(GL) -o $@ $^ $(LIB)

path_example.bin : path_example.o astar_pathfinder.o list.o field.o
	@echo 'Building $@'
	$(CC) $(LFLAGS) $(GL) -o $@ $^ $(LIB)

field_test.bin : field_test.o list.o field.o 
	@echo 'Building $@'
	$(CC) $(LFLAGS) -o $@ $^ $(LIB)

list_test.bin : list_test.o list.o 
	@echo 'Building $@'
	$(CC) $(LFLAGS) -o $@ $^ $(LIB)

%.o : %.c 
	@echo 'Compiling $<'
	$(CC) $(CFLAGS) $(DEBUG) $<

.PHONY : clean

clean :
	rm -f *.bin; rm -f *.o; rm -f *.i; rm -f *.s; rm -f *.out
