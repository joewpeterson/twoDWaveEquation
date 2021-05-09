#include "twoDWave.h"

/*
 * Initialize the values in the 2D velocity model. For this example, it sets
 * the velocity on the top three fourths to vl1 and bottome fourth to vl2 
 */
void init_vel (std::unique_ptr<float[]> & vel, int nx, int ny, float vl1, float vl2)
{
	#pragma omp parallel for
	for (int ix = 0; ix<nx; ix++){
		for (int iy = 0; iy<ny; iy++){
			int index = ix * ny + iy;

			if(iy < 3. * (float)ny/4.)
				vel[index] = vl1;
			else
				vel[index] = vl2;

		}
	}

}

;
