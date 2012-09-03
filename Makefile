#CPPFLAGS = -lglut -lGLU
all : path_example view_test

path_example : path_example.o astar_path_finder.o cpathfinder.h
	@echo 'Building $@'
	cc -lglut -lGLU $^ -o $@

view_test : view_test.o cpathfinder.h
	@echo 'Building $@'
	cc $^ -o $@

%.o : %.c 
	@echo 'Compiling $<'
	cc -std=c99 -pedantic -save-temps -Wall -c $<

.PHONY : clean

clean :
	rm path_example; rm view_test; rm *.o; rm *.i; rm *.s;
