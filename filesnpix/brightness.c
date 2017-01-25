
#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <pnmrdr.h>

int main(int argc, char* argv[] ) {
        
	FILE *fp;
	
        fp = fopen( argv[1], "rb" );
	
        Pnmrdr_T reader = Pnmrdr_new(fp);
	
	int pixels = Pnmrdr_data(reader).width * Pnmrdr_data(reader).height;
	
	int denominator = Pnmrdr_data(reader).denominator;
	long int sum  = 0;
	int p;
	TRY
		for( p = 0 ; p < pixels; p++ ){
			sum += Pnmrdr_get( reader );
		}
	
	float result = (float) sum / pixels ;
	printf("%.3f\n", result/denominator );
	
	argc++; /* !!!!!!!!!!!!!!!!!!!!!!!!!!!! */
	
        if( fclose( fp ) ) { 	
		exit( EXIT_SUCCESS );
        }
	exit ( EXIT_FAILURE ); 
}
