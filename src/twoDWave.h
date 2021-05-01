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
void fdWaveTimeStep(model_parameters *mod, input_wavelet *inwave);

/*
 * Right, I think ideally we would want the user to provide a file
 * which we read and for model and wavelet information. For the time being
 * I just build the model and wavelet here.
 */
class model_parameters {
public:
	//x direction
	int nx = 1024;
	int lx = 600;
	float dx = (float)lx/(float)nx;
	
	//y direction
	int ny = 1024;
	int ly = 600;
	float dy = (float)ly/(float)ny;

	int model_size = nx * ny;
	std::unique_ptr<float[]> p0 = std::make_unique<float[]>(model_size);
	std::unique_ptr<float[]> p1 = std::make_unique<float[]>(model_size);
	std::unique_ptr<float[]> p2 = std::make_unique<float[]>(model_size);

	std::unique_ptr<float[]> vel = std::make_unique<float[]>(model_size);

	model_parameters() 
	{
		std::cout << "mp constructor" << std::endl;
		//initialize the velocity model
		init_vel (vel, nx, ny, 1500, 2000);
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
		float maxVel = 0;
		for (int i = 0; i< mod.nx*mod.ny; i++)
			if (mod.vel[i] > maxVel)
				maxVel = mod.vel[i];

		// Safety margine
		maxVel *= 1.5;

		dt = (float)mod.lx/(float)mod.nx / maxVel;
		nt = Lt / dt;
		wavelet = std::make_unique<float[]>(nt);
		std::cout << nt << std::endl;
		
		double tau;
		float fc, t0;
		fc = 20;
		t0 = 1.5/fc;
		for (int i=0; i<nt; i++){
			tau = fc* M_PI * (i*dt - t0); 
			wavelet[i] = (1 - 2*(pow(tau, 2))) *exp(-pow(tau,2));
		}

		inject_index = mod.nx/4 * mod.ny + mod.ny/10;
 
	}

	~input_wavelet()
	{
		std::cout << "iw destructor" << std::endl;
	}
};


#endif
