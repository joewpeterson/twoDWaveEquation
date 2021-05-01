#include "twoDWave.h"

void init_vel (std::unique_ptr<float[]> & vel, int nx, int ny, float vl1, float vl2)
{
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
