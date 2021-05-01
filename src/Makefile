OBJ= timestep.o init_vel.o twoDWave.o

twoDWave: $(OBJ)
	g++-10 -std=c++17 $(OBJ) -o twoDWave -fopenmp 

$(OBJ): twoDWave.h 

.PHONY:clean

clean:
	rm $(OBJ) twoDWave

memcheck:
	valgrind --tool=memcheck ./twoDWave
