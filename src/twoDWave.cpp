#include "twoDWave.h"


int main()
{
	model_parameters mp;
	input_wavelet iw(mp);

	//int tid;
	//#pragma omp parallel private(tid)	
	//{
	//	tid = omp_get_thread_num();
	//	std::cout << "My tid is: " << tid << std::endl;
	//}
	
	//struct timeval start, end;

	//gettimeofday(&start, NULL);
	int N = 20;
	int fnum = 0;
	//Do the wave propagation
	for (int i=0; i<iw.nt; i++){
		//Inject the source
		mp.p1[iw.inject_index] += iw.dt * iw.dt * mp.vel[iw.inject_index] 
					  * 2 / mp.dx  * iw.wavelet[i];
	
		fdWaveTimeStep(&mp, &iw);
	  
		//TO DO: make this binary eventurally
		if (i%N == 0){
			fnum += 1;
			FILE *fptr;
			char fname[50];
			sprintf(fname, "data_%03d.dat", fnum);
			fptr = fopen(fname, "w");
			for (int j=0; j < mp.nx*mp.ny; j++)
					fprintf(fptr, "%.12f\n", mp.p2[j]);
			
			fclose(fptr);
		}
	  	
	} 

	//gettimeofday(&end, NULL);

	//int elapse;
	//elapse = (end.tv_sec - start.tv_sec)*1e6 + end.tv_usec - start.tv_usec;
	//std::cout << "run time: " << elapse << std::endl;

	return 0;
}
