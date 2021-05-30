#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOM 40
#define MAX_DIAS_MES 31 
#define MAX_CATEGORIA 40 
#define MAX_ADDRESS 100

/*
#define EXTES
*/

typedef struct 
{
  long long int NID;              /* Identification number - rang:0-2^32-1*/
  char Nom[MAX_NOM];  
  char Cognoms[MAX_NOM];  
  int  horesMes[MAX_DIAS_MES]; 
  char Categoria[MAX_CATEGORIA];
  unsigned int ptrClauForaneaDepartament;
  unsigned int ptrClauCategoria;
#ifdef EXTES     
  char Address[MAX_ADDRESS];
  char Nom_parella[MAX_NOM];
  char Cognoms_parella[MAX_NOM];
#endif
} Templeat;

typedef struct
{
  long long int NID;
  unsigned int index;
} Tindex;

int compare(const void *p1, const void *p2)
{
    if (((Tindex*) p1)->NID > ((Tindex*) p2)->NID) return(1);
    else if (((Tindex*) p1)->NID < ((Tindex*) p2)->NID) return(-1);
    else return(0);
}

int main(int argc, char *argv[])
{
	Templeat *empleats_data;
  Tindex   *empleats_index;

  Templeat *empleats_ordered;
  
	unsigned int N = 2000000, i, j;
  int block = 100;

	if (argc > 1) N = atoi(argv[1]);
	if (argc > 2) block = atoi(argv[2]);

  empleats_ordered  =  (Templeat  *)  malloc(block*sizeof(Templeat));
  empleats_data     =  (Templeat  *)  malloc(N*sizeof(Templeat));
  empleats_index    =  (Tindex    *)  malloc(N*sizeof(Tindex));

	if (empleats_data == NULL) { fprintf(stderr, "Out of memory\n"); exit(0); }
	memset(empleats_data, 0, N*sizeof(Templeat));

	/* Random generation */
	for (i=0; i<N; i++) {
    long long int NID = rand();
  
    empleats_index[i].index  =  i;
    empleats_index[i].NID    =  NID;

		empleats_data[i].NID = NID;
		empleats_data[i].Nom[0] = 'A' + ((i>>3) + (i<<2)) & 0x15;
		empleats_data[i].Cognoms[0] = 'a' + ((i>>2) + (i<<3)) & 0x15;
		empleats_data[i].horesMes[i % MAX_DIAS_MES] = i;
		empleats_data[i].Categoria[i % MAX_CATEGORIA] = (i << 2) * i;
		empleats_data[i].ptrClauForaneaDepartament = i<<10 + i<<14 + i>>3;
		empleats_data[i].ptrClauCategoria = i<<24 + i<< 18 + i<<10 + i>>2;
#ifdef EXTES     
      empleats_data[i].Address[0]          =  'A'  +  ((i>>4)  +  (i<<2))  &  0x15;
      empleats_data[i].Nom_parella[0]      =  'a'  +  ((i>>5)  +  (i<<2))  &  0x15;
      empleats_data[i].Cognoms_parella[0]  =  'A'  +  ((i>>5)  +  (i<<3))  &  0x15;
#endif
	}

	qsort(empleats_index, N, sizeof(Tindex), compare);
  i = 0;
 	for (i; i<N-block; i+=block){
    for (j=0; j<block; ++j)
      empleats_ordered[j] = empleats_data[empleats_index[i+j].index]; 
    write(1, empleats_ordered, block*sizeof(Templeat));
 	}
	for (j=0; i+j<N; j++){
    empleats_ordered[j] = empleats_data[empleats_index[i+j].index]; 
	}
  write(1, empleats_ordered, j*sizeof(Templeat));

	return 0;
}
