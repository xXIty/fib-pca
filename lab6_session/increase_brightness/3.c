#include <stdio.h>
#include <stdlib.h>

#define N 16000000

typedef struct s_pixel_rgb {
	unsigned char r;
	unsigned char g;
	unsigned char b;
} t_pixel_rgb;


void increase_brightness (t_pixel_rgb *rgb, int len, unsigned char inc, int N_iter)
{
	int i,j;
    char*  chars      =  (char *) rgb;
    int    chars_len  =  len*3;

    for (j=0; j<N_iter; j++) {
        for (i=0; i<chars_len - 15; i += 16) {
            if ((chars[i] + inc) > 255) {
                chars[i]  = 255;
            } else {
                chars[i] += inc;
            }
            if ((chars[i+1] + inc) > 255) {
                chars[i+1]  = 255;
            } else {
                chars[i+1] += inc;
            }
            if ((chars[i+2] + inc) > 255) {
                chars[i+2]  = 255;
            } else {
                chars[i+2] += inc;
            }
            if ((chars[i+3] + inc) > 255) {
                chars[i+3]  = 255;
            } else {
                chars[i+3] += inc;
            }
            if ((chars[i+4] + inc) > 255) {
                chars[i+4]  = 255;
            } else {
                chars[i+4] += inc;
            }
            if ((chars[i+5] + inc) > 255) {
                chars[i+5]  = 255;
            } else {
                chars[i+5] += inc;
            }
            if ((chars[i+6] + inc) > 255) {
                chars[i+6]  = 255;
            } else {
                chars[i+6] += inc;
            }
            if ((chars[i+7] + inc) > 255) {
                chars[i+7]  = 255;
            } else {
                chars[i+7] += inc;
            }
            if ((chars[i+8] + inc) > 255) {
                chars[i+8]  = 255;
            } else {
                chars[i+8] += inc;
            }
            if ((chars[i+9] + inc) > 255) {
                chars[i+9]  = 255;
            } else {
                chars[i+9] += inc;
            }
            if ((chars[i+10] + inc) > 255) {
                chars[i+10]  = 255;
            } else {
                chars[i+10] += inc;
            }
            if ((chars[i+11] + inc) > 255) {
                chars[i+11]  = 255;
            } else {
                chars[i+11] += inc;
            }
            if ((chars[i+12] + inc) > 255) {
                chars[i+12]  = 255;
            } else {
                chars[i+12] += inc;
            }
            if ((chars[i+13] + inc) > 255) {
                chars[i+13]  = 255;
            } else {
                chars[i+13] += inc;
            }
            if ((chars[i+14] + inc) > 255) {
                chars[i+14]  = 255;
            } else {
                chars[i+14] += inc;
            }
            if ((chars[i+15] + inc) > 255) {
                chars[i+15]  = 255;
            } else {
                chars[i+15] += inc;
            }
        }
    
        for (; i<chars_len; i++) {
            if ((chars[i] + inc) > 255) {
                chars[i] = 255;
            } else {
                chars[i] += inc;
            }
        }
    }
}

int main (int argc, char *argv[])
{

  t_pixel_rgb *A;
  int i;
  int n=N; // tamanyo vectores
  int NIt=50; // Num.iters
  unsigned char incr=1;

  if (argc>1) NIt = atoi(argv[1]);
  if (argc>2) n = atoi(argv[2]);
  if (argc>3) incr = (unsigned char) atoi(argv[3]);

  if (n>N) { printf("Maxima longitud vector: %d\n",N); exit(-1); }

  if (posix_memalign((void**)&A, 16, n*sizeof(t_pixel_rgb)) != 0) {
      fprintf(stderr, "No hay memoria.\n");
      exit(-1);
  }

   /* Inicialitzacio nombres "aleatoris" */
   for (i=0;i<n;i++) {
     A[i].r= i^(i-54) & 0x2f;
     A[i].g= (i+89)^(i-200) & 0x2f;
     A[i].b= (i+70)^(i+325) &0x2f;
   }

   increase_brightness (A, n, incr, NIt); 

   write(1, A, n*sizeof(t_pixel_rgb));

   return(0);
}
