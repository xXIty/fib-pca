#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <immintrin.h>

#define CACHE_ALIGNMENT 64
#define GRAINSIZE 4

void panic(char *miss)
{
        if (errno != 0) perror(miss);
        else fprintf(stderr, "%s\n", miss);

        exit(1);
}

int main(int argc, char *argv[])
{
    int count = 1000;
    if (argc == 2) count = atoi(argv[1]);


    int  n1;
    int  res;
    __m128i *c1;
    __m128i *c1_out;
    __m128i mask;

    posix_memalign((void *)&c1,      CACHE_ALIGNMENT,  count*sizeof(* c1));
    posix_memalign((void *)&c1_out,  CACHE_ALIGNMENT,  count*sizeof(* c1));

    mask = _mm_set_epi8(14, 15, 12, 13, 10, 11, 8, 9, 6, 7, 4, 5, 2, 3, 0, 1);

    while ((n1=read(0, c1, count*sizeof(* c1))) > 0)
    {
        int i, j;
        int c1_chars_left = n1 & 0xF;
        int c1_size       = n1 >> GRAINSIZE;// / sizeof(* c1); 

        for (i=0; i<c1_size; i++) {
            c1_out[i] = _mm_shuffle_epi8(c1[i], mask);
        }

        // i *= sizeof(* c1);
        i <<= GRAINSIZE; 
        for (j=0; j < c1_chars_left-1 ; j+=2) {
            ((char  *)c1_out)[i+j]    =  ((char  *)  c1)[i+j+1];
            ((char  *)c1_out)[i+j+1]  =  ((char  *)  c1)[i+j];
        }

        if (j < c1_chars_left)
            ((char *)c1_out)[i+j]     =  ((char  *) c1)[i+j];

        if (write(1, c1_out, n1) < 0) panic("write2");
    }


    if ((n1==-1) ) panic("read");

    free(c1);
    free(c1_out);
    return 0;
}

