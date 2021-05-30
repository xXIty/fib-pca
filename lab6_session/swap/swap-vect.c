#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <immintrin.h>

void panic(char *miss)
{
        if (errno != 0) perror(miss);
        else fprintf(stderr, "%s\n", miss);

        exit(1);
}

int main(int argc, char *argv[])
{
    int count = 100;
    if (argc == 2) count = atoi(argv[1]);


    int  n1;
    __m256i *c1;
    __m256i *c1_out;

    c1        = (__m256i *) aligned_alloc(16, count * sizeof(__m256i ));
    c1_out    = (__m256i *) aligned_alloc(16, count * sizeof(__m256i ));

    // Vectorization code
    __m256i mask, out;
    mask = _mm256_set_epi8(14, 15, 12, 13, 10, 11, 8, 9, 6, 7, 4, 5, 2, 3, 0, 1, 14, 15, 12, 13, 10, 11, 8, 9, 6, 7, 4, 5, 2, 3, 0, 1);

    while ((n1=read(0, c1, count*32)) > 0)
    {
        int i, j;
	int r = n1 & 0xFF;
        for (i=0; i<n1/32; i++) {
		c1_out[i] = _mm256_shuffle_epi8(c1[i], mask);
        }
	for (j=0; j < r-1 ; j+=2) {
          	((char *)c1_out)[(i*32)+j]     = ((char *) c1)[(i*32)+j+1];
          	((char *)c1_out)[(i*32)+j+1]     = ((char *) c1)[(i*32)+j];
	}
        if (j < r)
          	((char *)c1_out)[(i*32)+j]     = ((char *) c1)[(i*32)+j];

        if (write(1, c1_out, n1) < 0) panic("write2");
    }

    if ((n1==-1) ) panic("read");

    free(c1);
    free(c1_out);
    return 0;
}
