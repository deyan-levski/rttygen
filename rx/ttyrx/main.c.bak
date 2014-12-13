// Reads raw PCM file format and prints the samples in signed integer format on the standard output.
//
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#ifndef M_PI
#define M_PI 3.14159265358
#endif
#define PI2 6.2832
#define SAMPLE_RATE 44100 // Hz
#define BITS_PER_SAMPLE 16 // bits
#define N_SAMPLES 18000 // n
#define BIT_AVG_DUR 1500 // Average single bit duration

int convertBitSize(unsigned int in, int bps)
{
        const unsigned int max = (1 << (bps-1)) - 1;
        return in > max ? in - (max<<1) : in;
}

int readPCM(int *data, unsigned int samp_rate, unsigned int bits_per_samp, unsigned int num_samp)

{
	FILE *fp;
	unsigned char buf;
	unsigned int i, j;

	fp = fopen("ttyburst.pcm", "r");

        for (i=0; i < num_samp; ++i) {

		unsigned int tmp = 0;

		for (j=0; j != bits_per_samp; j+=8) {
			fread(&buf, 1, 1, fp);
			tmp += buf << j;
		}

		data[i] = convertBitSize(tmp, bits_per_samp);

        }
}

int dft(int x[N_SAMPLES], float P[N_SAMPLES]){

    // time and frequency domain data arrays
    int n, k;             // indices for time and frequency domains
    //int x[N_SAMPLES];           // discrete-time signal, x
    float Xre[N_SAMPLES], Xim[N_SAMPLES]; // DFT of x (real and imaginary parts)
   // float P[N_SAMPLES];           // power spectrum of x
     
    // Calculate DFT of x using brute force
    	for (k=0 ; k<N_SAMPLES ; ++k)
    	{
        	// Real part of X[k]
       		Xre[k] = 0;
        	for (n=0 ; n<N_SAMPLES ; ++n) Xre[k] += x[n] * cos(n * k * PI2 / N_SAMPLES);
         
        	// Imaginary part of X[k]
        	Xim[k] = 0;
        	for (n=0 ; n<N_SAMPLES ; ++n) Xim[k] -= x[n] * sin(n * k * PI2 / N_SAMPLES);
         
        	// Power at kth frequency bin
        	P[k] = Xre[k]*Xre[k] + Xim[k]*Xim[k];
	}

// Output results to MATLAB / Octave M-file for plotting
    FILE *f = fopen("dftplots.m", "w");
    fprintf(f, "clc;\nclear all;\n");
    fprintf(f, "n = [0:%d];\n", N_SAMPLES-1);
    fprintf(f, "x = [ ");
    for (n=0 ; n<N_SAMPLES ; ++n) fprintf(f, "%d ", x[n]);
    fprintf(f, "];\n");
    fprintf(f, "Xre = [ ");
    for (k=0 ; k<N_SAMPLES ; ++k) fprintf(f, "%f ", Xre[k]);
    fprintf(f, "];\n");
    fprintf(f, "Xim = [ ");
    for (k=0 ; k<N_SAMPLES ; ++k) fprintf(f, "%f ", Xim[k]);
    fprintf(f, "];\n");
    fprintf(f, "P = [ ");
    for (k=0 ; k<N_SAMPLES ; ++k) fprintf(f, "%f ", P[k]);
    fprintf(f, "];\n");
    fprintf(f, "figure(1);\nplot(n,x);\n");
    //fprintf(f, "xlim([0 %d])\n", N_SAMPLES-1);
    fprintf(f, "figure(2);\nplot(n,Xre,n,Xim);\n");
    //fprintf(f, "xlim([0 %d])\n", N_SAMPLES-1);
    fprintf(f, "figure(3);\nstem(n,P);\n");
    //fprintf(f, "xlim([0 %d])\n", N_SAMPLES-1);
    fclose(f);
     
    // exit normally
    return 0;

}

int main(void)
{

	printf("SAMPLE RATE = [%d] BITS PER SAMPLE = [%d] N SAMPLES = [%d]\n", SAMPLE_RATE, BITS_PER_SAMPLE, N_SAMPLES);

	int *data = (int *) malloc(N_SAMPLES * sizeof(int));

        readPCM(data, SAMPLE_RATE, BITS_PER_SAMPLE, N_SAMPLES);

	unsigned int i;
	for (i = 0; i < N_SAMPLES; ++i) {
		printf("%d\n", data[i]);
	} 

	float P[N_SAMPLES];
//int bitslot;
//int bitnum = 0;
//int dataSubset;
//int j;
//
//for (bitslot = 0; bitslot < N_SAMPLES; bitslot += BIT_AVG_DUR) {
//
//bitnum++;
//printf("Performing DFT on bit number = [%d]\n",bitnum);
//
//dataSubset = malloc((N_SAMPLES-(bitnum*BIT_AVG_DUR))*sizeof(int)); 
//
//for(j=(bitnum*BIT_AVG_DUR);j<N_SAMPLES;j++){
//dataSubset[j] = data[j];
//}

//	dft(data, P);

//}

return 0;

}
