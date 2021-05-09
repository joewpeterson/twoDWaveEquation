#include "twoDWave.h"

void init_wavelet (std::unique_ptr<float[]>& wavelet, int nt, float dt )
{
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
}
