#include "twoDWave.h"

void fdWaveTimeStep(model_parameters *mod, input_wavelet *inwave)
{

	std::unique_ptr<float[]> derivX = std::make_unique<float[]>(mod->model_size);
	std::unique_ptr<float[]> derivY = std::make_unique<float[]>(mod->model_size);

	#pragma omp parallel for
	for (int i=1; i < mod->nx - 1; i++){
		for (int j=1; j < mod->ny - 1; j++){
			int index = i*mod->ny +j;
	  		derivX[index] = (mod->p1[index-mod->ny] - 2*mod->p1[index] + 
						mod->p1[index+mod->ny])/mod->dx/mod->dx;
	  		derivY[index] = (mod->p1[index-1] - 2*mod->p1[index] + 
						mod->p1[index+1])/mod->dy/mod->dy;
			//time derive 
	  		mod->p2[index] = pow(mod->vel[index],2)*pow(inwave->dt,2)*(derivX[index] 
					+ derivY[index]) + 2* mod->p1[index] - mod->p0[index];
		}
	}
	
	//We can code in edge absorption later
	//mod->p2[mod->nx - 1] = -(mod->p1[mod->nx - 1] - mod->p1[mod->nx - 2])*mod->vel[mod->nx -1]*inwave->dt/mod->dx + mod->p1[mod->nx - 1]; 
	
	//swap the pressure waves to increment to the next time
	mod->p0.swap(mod->p1);
	mod->p1.swap(mod->p2);
}

