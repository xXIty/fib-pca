#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

int N, N4;
signed char a[25480], b[25480], c[25480];


unsigned u_MOD_5   [5   * 10 -1];
unsigned u_MOD_25  [25  * 10 -1];
unsigned u_MOD_239 [239 * 10 -1];

unsigned u_DIV_5   [5   * 10 -1];
unsigned u_DIV_25  [25  * 10 -1];
unsigned u_DIV_239 [239 * 10 -1];

unsigned r_IMUL_10  [239];

void DIVIDE_5( signed char *x, int n )
{                                                
    int j, k;
    unsigned q, r, u;
    long v;

    r = 0;                                       
    for( k = 0; k <= N4-2+1; k=k+2 )                  
    {                                            
        u = r_IMUL_10[r] + x[k];                       
        x[k] = u_DIV_5[u];                               
        r = u_MOD_5[u];                           
        
        u = r_IMUL_10[r] + x[k+1];                       
        x[k+1] = u_DIV_5[u];                               
        r = u_MOD_5[u];                           
    }                                           
    for( ; k <= N4; k++ )                  
    {                                            
        u = r_IMUL_10[r] + x[k];                       
        x[k] = u_DIV_5[u];                               
        r = u_MOD_5[u];                           
    }

}

void DIVIDE_25( signed char *x, int n )
{                                                
    int j, k;
    unsigned q, r, u;
    long v;

    r = 0;                                       
    for( k = 0; k <= N4-2+1; k=k+2 )                  
    {                                            
        u = r_IMUL_10[r] + x[k];                       
        x[k] = u_DIV_25[u];
        r = u_MOD_25[u];                           
        
        u = r_IMUL_10[r] + x[k+1];                       
        x[k+1] = u_DIV_25[u];
        r = u_MOD_25[u];                           
    }                                           
    for( ; k <= N4; k++ )                  
    {                                            
        u = r_IMUL_10[r] + x[k];                       
        x[k] = u_DIV_25[u];
        r = u_MOD_25[u];                           
    }
}

void DIVIDE_239( signed char *x, int n )
{                                                
    int j, k;
    unsigned q, r, u;
    long v;

    r = 0;                                       
    for( k = 0; k <= N4-2+1; k=k+2 )                  
    {                                            
        u = r_IMUL_10[r] + x[k];                       
        x[k] = u_DIV_239[u];                               
        r = u_MOD_239[u];                           
        
        u = r_IMUL_10[r] + x[k+1];                       
        x[k+1] = u_DIV_239[u];                               
        r = u_MOD_239[u];                           
    }                                           
    for( ; k <= N4; k++ )                  
    {                                            
        u = r_IMUL_10[r] + x[k];                       
        x[k] = u_DIV_239[u];                               
        r = u_MOD_239[u];                           
    }
}


void DIVIDE_TWO_TIMES_239( signed char *x, int n )
{                                                
    int j, k;
    unsigned q, r1, r2, u;
    long v;

    r1 = 0;                                       
    r2 = 0;
    for( k = 0; k <= N4; k++ )                  
    {                                            
        u = r_IMUL_10[r1] + x[k];                       
        q = u_DIV_239[u];                               
        r1 = u_MOD_239[u];                           

        u = r_IMUL_10[r2] + q;                       
        x[k] = u_DIV_239[u];                               
        r2 = u_MOD_239[u];                           
    }                                           
}

void LONGDIV( signed char *x, int n )
{                                                
    int j, k;
    unsigned q, r, u;
    long v;

    if( n < 6553 )                               
    {                                            
        r = 0;                                   
        for( k = 0; k <= N4; k++ )               
        {                                        
            u = r * 10 + x[k];                   
            q = u / n;                           
            r = u - q * n;                       
            x[k] = q;                            
        }                                       
    }                                            
    else                                         
    {                                            
        r = 0;                                   
        for( k = 0; k <= N4; k++ )              
        {                                       
            if( r < 6553 )                      
            {                                   
                u = r * 10 + x[k];              
                q = u / n;                      
                r = u - q * n;                  
            }                                   
            else                                
            {                                   
                v = (long) r * 10 + x[k];       
                q = v / n;                      
                r = v - q * n;                  
            }                                   
            x[k] = q;                           
        }                                       
    }                                           
}

void MULTIPLY( signed char *x, int n )                        
{                                            
    int j, k;
    unsigned q, r, u;
    long v;
    r = 0;                                   
    for( k = N4; k >= 0+1; k=k-2 )               
    {                                        
        q = n * x[k] + r;                    
        r = q / 10;                          
        x[k] = q - r * 10;                   

        q = n * x[k-1] + r;                    
        r = q / 10;                          
        x[k-1] = q - r * 10;                   
    }                                        
    for( ; k >= 0; k-- )               
    {                                        
        q = n * x[k] + r;                    
        r = q / 10;                          
        x[k] = q - r * 10;                   
    }                                        
}

void SET( signed char *x, int n )                              
{                                                
    memset( x, 0, N4 + 1 );                      
    x[0] = n;                                    
}


void SUBTRACT( signed char *x, signed char *y, signed char *z )                      
{                                                
    int j, k;
    unsigned q, r, u;
    long v;
    for( k = N4; k >= 1; k-- )                   
    {                                            
        if( (x[k] = y[k] - z[k]) < 0 )           
        {                                        
            x[k] += 10;                          
            z[k-1]++;                            
        }                                        
    }                                            
    if( (x[k] = y[k] - z[k]) < 0 )           
    {                                        
        x[k] += 10;                          
    }                                        
}

// IN THIS FUSION, y = yy (see main)
void SUBTRACT_FUSIONED( signed char *x, signed char *y, signed char *z, signed char *xx, signed char *yy, signed char *zz )                      
{                                                
    int j, k;
    unsigned q, r, u;
    long v;
    int x_is_neg_mask;
    int xx_is_neg_mask;

    for( k = N4; k >= 1 +1; k=k-2 )                   
    {                                            
        //  if( (x[k] = y[k] - z[k]) < 0 )           
        x[k]           =   y[k] - z[k];          
        x_is_neg_mask  =   x[k]>>(sizeof(x[k])*8);

        x[k]          +=   10 & x_is_neg_mask;  
        z[k-1]        +=   1  & x_is_neg_mask;  
        
        x[k-1]           =   y[k-1] - z[k-1];          
        x_is_neg_mask  =   x[k-1]>>(sizeof(x[k-1])*8);

        x[k-1]          +=   10 & x_is_neg_mask;  
        z[k-2]        +=   1  & x_is_neg_mask;  

        // FUSIO
        //  if( (xx[k] = yy[k] - zz[k]) < 0 )           
        xx[k]           =   y[k] - zz[k];
        xx_is_neg_mask  =   xx[k]>>(sizeof(xx[k])*8);

        xx[k]          +=   10 & xx_is_neg_mask;                
        zz[k-1]        +=   1  & xx_is_neg_mask;                

        xx[k-1]           =   y[k-1] - zz[k-1];
        xx_is_neg_mask  =   xx[k-1]>>(sizeof(xx[k-1])*8);

        xx[k-1]          +=   10 & xx_is_neg_mask;                
        zz[k-2]        +=   1  & xx_is_neg_mask;                
    }                                            

    for(; k >= 1; k-- )                   
    {                                            
        //  if( (x[k] = y[k] - z[k]) < 0 )           
        x[k]           =   y[k] - z[k];          
        x_is_neg_mask  =   x[k]>>(sizeof(x[k])*8);

        x[k]          +=   10 & x_is_neg_mask;  
        z[k-1]        +=   1  & x_is_neg_mask;  
        
        // FUSIO
        //  if( (xx[k] = yy[k] - zz[k]) < 0 )           
        xx[k]           =   y[k] - zz[k];
        xx_is_neg_mask  =   xx[k]>>(sizeof(xx[k])*8);

        xx[k]          +=   10 & xx_is_neg_mask;                
        zz[k-1]        +=   1  & xx_is_neg_mask;                
    }                                            

    //  if( (x[k] = y[k] - z[k]) < 0 )           
    x[k]           =   y[k] - z[k];          
    x_is_neg_mask  =   x[k]>>(sizeof(x[k])*8);
    x[k]          +=   10 & x_is_neg_mask;  

    //  if( (xx[k] = yy[k] - zz[k]) < 0 )           
    xx[k]           =   yy[k] - zz[k];
    xx_is_neg_mask  =   xx[k]>>(sizeof(xx[k])*8);
    xx[k]          +=   10 & xx_is_neg_mask;                
}

void calculate( void );
void progress( void );
void epilog( void );


int main( int argc, char *argv[] )
{
    N = 10000;

    if( argc > 1 )
        N = atoi(argv[1]);

    setbuf(stdout, NULL);

    int i;
    unsigned  acumulator_5    =  0;
    unsigned  acumulator_10   =  0;
    unsigned  acumulator_25   =  0;
    unsigned  acumulator_239  =  0;

    for (i = 0; i < 5 * 10; ++i) {
      u_MOD_5    [i]  =  acumulator_5      %  5;
      u_MOD_25   [i]  =  acumulator_25     %  25;
      u_MOD_239  [i]  =  acumulator_239    %  239;

      u_DIV_5    [i]  =  acumulator_5++    /  5;
      u_DIV_25   [i]  =  acumulator_25++   /  25;
      u_DIV_239  [i]  =  acumulator_239++  /  239;
    }
    for (i; i < 25 * 10; ++i) {
      u_MOD_25   [i]  =  acumulator_25     %  25;
      u_MOD_239  [i]  =  acumulator_239    %  239;

      u_DIV_25   [i]  =  acumulator_25++   /  25;
      u_DIV_239  [i]  =  acumulator_239++  /  239;
    }
    for (i; i < 239 * 10; ++i) {
      u_MOD_239  [i]  =  acumulator_239    %  239;

      u_DIV_239  [i]  =  acumulator_239++  /  239;
    }

    for (i = 0; i < 239; ++i) {
      r_IMUL_10[i] = acumulator_10;
      acumulator_10 += 10;
    }

    calculate();


    epilog();

    return 0;
}

void calculate( void )
{
    int j;

    N4 = N + 4;

    SET( a, 0 );
    SET( b, 0 );

    for( j = 2 * N4 + 1; j >= 3; j -= 2 )
    {
        SET( c, 1 );
        LONGDIV( c, j );

//        SUBTRACT( a, c, a );
        SUBTRACT_FUSIONED(a, c, a, b, c, b);
        DIVIDE_25( a, 25 );

//        SUBTRACT( b, c, b );
        DIVIDE_TWO_TIMES_239( b, 239 );

        progress();
    }

    SET( c, 1 );

    SUBTRACT( a, c, a );
    DIVIDE_5( a, 5 );

    SUBTRACT( b, c, b );
    DIVIDE_239( b, 239 );

    MULTIPLY( a, 4 );
    SUBTRACT( a, a, b );
    MULTIPLY( a, 4 );

    progress();
}

/*

 N = 10000                      
 A = 0                          
 B = 0                          
 J = 2 * (N + 4) + 1            
 FOR J = J TO 3 STEP -2         
     A = (1 / J - A) / 5 ^ 2    
     B = (1 / J - B) / 239 ^ 2  
 NEXT J                         
 A = (1 - A) / 5                
 B = (1 - B) / 239              
 PI = (A * 4 - B) * 4           

*/

void progress( void )
{
    printf(".");
}

void epilog( void )
{
    int j;

    {
        fprintf( stdout, " \n3.");
        for( j = 1; j <= N; j++ )
        {
            fprintf( stdout, "%d", a[j]);
            if( j % 5  == 0 )
                if( j % 50 == 0 )
                    if( j % 250  == 0 )
                        fprintf( stdout, "    <%d>\n\n   ", j );
                    else
                        fprintf( stdout, "\n   " );
                else
                    fprintf( stdout, " " );
        }
    }
}

