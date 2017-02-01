
#include <setjmp.h> 
#include <stdio.h>
#include <stdlib.h>
#include <pnmrdr.h>

/*
        TODO:
        - format
        - Pnmrdr exception handling
        - look better

*/

void parse_input(int argc, char* argv[], FILE* file_ptr );
void print_brightness( Pnmrdr_T *reader );

int main(int argc, char* argv[] ) {
        FILE* file_ptr = NULL;
        parse_input( argc, argv, file_ptr );
        if( file_ptr != NULL && !(fclose(file_ptr)) ){ 	
                exit( EXIT_SUCCESS );
        }
}

void parse_input(int argc, char* argv[], FILE* file_ptr )
{
        Pnmrdr_T reader;
        if ( argc == 2 ) {
                file_ptr = fopen( argv[1], "rb" );
                if ( file_ptr == NULL ) {
                        exit( EXIT_FAILURE );
                }
                reader = Pnmrdr_new( file_ptr );
        } else if( argc == 1 ) {
                reader = Pnmrdr_new( stdin );
        } else {
                exit( EXIT_FAILURE );
        }
        if ( Pnmrdr_data(reader).type != 2 ){
                exit( EXIT_FAILURE );
        }
        print_brightness( &reader );
}

void print_brightness( Pnmrdr_T *reader )
{
        
        int pixels = Pnmrdr_data( *reader ).width 
                * Pnmrdr_data( *reader ).height;
	int denominator = Pnmrdr_data( *reader ).denominator;
	long int sum  = 0;
	int p;
	for( p = 0 ; p < pixels; p++ ){
		sum += Pnmrdr_get( *reader );
	}
	float result = (float) sum / pixels ;
	printf("%.3f\n", result/denominator );
}

