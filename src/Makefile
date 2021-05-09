OBJ= timestep.o init_vel.o twoDWave.o init_wavelet.o
CPP=g++
export CXXFLAGS = -fopenmp

twoDWave: $(OBJ)
	$(CPP) $(OBJ) -o twoDWave $(CXXFLAGS)

$(OBJ): twoDWave.h 

.PHONY:clean

clean:
	rm $(OBJ) twoDWave

memcheck:
	valgrind --tool=memcheck ./twoDWave
