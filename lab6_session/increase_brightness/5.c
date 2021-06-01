#include <stdio.h>
#include <stdlib.h>
#include <emmintrin.h>

#define N 16000000

typedef struct s_pixel_rgb {
	unsigned char r;
	unsigned char g;
	unsigned char b;
} t_pixel_rgb;


void increase_brightness (t_pixel_rgb *rgb, int len, unsigned char inc, int N_iter)
{
	int i,j, m;
    char*  chars      =  (char *) rgb;
    int    chars_len  =  len*3;
    __m128i rgb_128i;
    __m128i result_add, result_sub, result;

    __m128i masks_sub[3];
    masks_sub[0] = _mm_set_epi8(0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF);
    masks_sub[1] = _mm_set_epi8(0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00);
    masks_sub[2] = _mm_set_epi8(0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00);

    __m128i masks_add[3];
    masks_add[0] = _mm_set_epi8(0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x00);
    masks_add[1] = _mm_set_epi8(0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0xFF);
    masks_add[2] = _mm_set_epi8(0xFF, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF);

    __m128i incr_vector = _mm_set1_epi8(inc);

    for (j=0; j<N_iter; j++) {
        for (i=0; i<chars_len - 15; i += 16) {
            rgb_128i = _mm_load_si128((__m128i *) &chars[i]);
            result_add   = _mm_adds_epu8(rgb_128i, incr_vector);
            result_sub   = _mm_subs_epu8(rgb_128i, incr_vector);

            m = i % 3; 
            result_add = _mm_and_si128(result_add, masks_add[m]);
            result_sub = _mm_and_si128(result_sub, masks_sub[m]);

            result     = _mm_or_si128(result_add, result_sub);

            _mm_store_si128((__m128i *) &chars[i], result);
        }
    
        for (; i<chars_len; i++) {
            if(i % 3 == 0) {
                if(chars[i] < inc) {
                    chars[i] = 0;
                } else {
                    chars[i] -= inc;
                }
            } else {
                if ((chars[i] + inc) > 255) {
                    chars[i] = 255;
                } else {
                    chars[i] += inc;
                }
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
