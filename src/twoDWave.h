#include<iostream>
#include<cmath>
#include<memory>
#include <omp.h>
#include <time.h>
#include <sys/time.h>

#ifndef TWO_D_WAVE
#define TWO_D_WAVE
class model_parameters;
class input_wavelet;

void init_vel (std::unique_ptr<float[]> & vel, int nx, int ny, float vl1, float vl2);
void init_wavelet (std::unique_ptr<float[]> & wavelt, int nt, float dt);
void fdWaveTimeStep(model_parameters *mod, input_wavelet *inwave);

/*
 * Right, I think ideally we would want the user to provide a file
 * which we read and for model and wavelet information. For the time being
 * I just build the model and wavelet here.
 */
class model_parameters {
public:
	// x direction
	int nx = 1024;
	int lx = 600;
	float dx = (float)lx/(float)nx;
	
	// y direction
	int ny = 1024;
	int ly = 600;
	float dy = (float)ly/(float)ny;

	// Vel of input model layers
	float minVel = 1500;
	float maxVel = 2000;

	// init the needed pointers
	int model_size = nx * ny;
	std::unique_ptr<float[]> p0 = std::make_unique<float[]>(model_size);
	std::unique_ptr<float[]> p1 = std::make_unique<float[]>(model_size);
	std::unique_ptr<float[]> p2 = std::make_unique<float[]>(model_size);

	std::unique_ptr<float[]> vel = std::make_unique<float[]>(model_size);

	model_parameters() 
	{
		std::cout << "mp constructor" << std::endl;

		//initialize the velocity model
		init_vel (vel, nx, ny, minVel, maxVel);
	}

	~model_parameters()
	{
		std::cout << "mp destructor" << std::endl;
	}
};

class input_wavelet
{
public:
	int nt;
	float dt;
	float Lt = 0.5;
	
	int inject_index;

	std::unique_ptr<float[]> wavelet;
	input_wavelet(model_parameters& mod)
	{
		std::cout << "iw constructor" << std::endl;

		float maxVel;
		maxVel = 1.5 * mod.maxVel;
		dt = (float)mod.lx/(float)mod.nx / maxVel;
		nt = Lt / dt;
		inject_index = mod.nx/4 * mod.ny + mod.ny/10;

		init_wavelet (wavelet, nt, dt); 
	}

	~input_wavelet()
	{
		std::cout << "iw destructor" << std::endl;
	}
};


#endif
