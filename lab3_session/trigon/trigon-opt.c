
#include <math.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define N 6000
#define PUNTS 1000


double *buffer;
double mem_cos[PUNTS];
double mem_sin[PUNTS];

int main(int argc, char *argv[])
{
	unsigned int i, r, j, n, m, index;
	double d, x, y;

	if (argc == 1) n = N; else n = atoi(argv[1]);

        buffer = malloc((PUNTS+PUNTS)*n*sizeof(double));


        // Memoization of sin and cos calculations
        for(m=0, d=0; m<PUNTS; m++) {
            mem_cos[m] = cos(d);
            mem_sin[m] = sin(d);
            d += 2*M_PI/PUNTS;
        }

        index = 0;
	srand(0);
	for (i=0; i<n; i++)
	{
		r = rand();
		for (j=0, d=0; j<PUNTS; j++)
		{
                        index = ((i*PUNTS) + j) << 1;
			x = r*mem_cos[j]; y = r*mem_sin[j];
                        buffer[index] = x;
                        buffer[index+1] = y;
		}
	}
	fwrite(&buffer, sizeof(double), (PUNTS+PUNTS)*n, stdout);
	return 0;
}
