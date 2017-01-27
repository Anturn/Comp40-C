/*
 *
 * */

#include "readaline.h"
#include <stdlib.h>
#include <stdio.h>

FILE* open_file ( char *filename );
void  close_file( FILE *file_ptr );
void  test_readaline();
void  parse_input( int argc, char* argv[] );

int main ( int argc, char *argv[] ) 
{
        parse_input( argc, argv );
        test_readaline();
}


void  test_readaline()
{
        FILE *fp;
	char **datapp = NULL;
        
        fp = open_file("test1.txt");
	do{
		printf("Get in ?");
		readaline(fp,datapp);
		
		/*printf("%s\n",*datapp);*/	
		printf("Line 32 right?");
		
		
	}while(datapp);
        readaline( fp, datapp );
        close_file( fp );

}

FILE* open_file ( char* filename ) 
{
        FILE *fp = fopen( filename, "r" );
        return fp;
}


void  close_file( FILE* file_ptr )
{
        if ( !(fclose( file_ptr )) ) {
                exit( EXIT_FAILURE );
        }
        exit( EXIT_SUCCESS );
}

void  parse_input( int argc, char* argv[] )
{
        if ( argc != 1 ) {
                printf (" dont use \"./%s\" with arguments", argv[0]);
                exit ( EXIT_SUCCESS );
        }
        
}

