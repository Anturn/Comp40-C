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

void clean_line(char **datapp);

void test_clean_line();
void test_blank_file();
void test_long_lines();
void test_open_without_reading();
void test_reading_error();
void test_filling_memory();
void test_closed_file();








int main ( int argc, char *argv[] ) 
{
        parse_input( argc, argv );
        
        test_clean_line();
        /*
        test_blank_file();
        test_long_lines();
        test_open_without_reading();
	
	test_reading_error();
        test_filling_memory();
        

        test_closed_file();
        */

}

/* turn all non-word groups of characters into a single space,
 * and to add a null character at the end 
 * */
char* clean_line( char **datapp, size_t num_bytes )
{
                do {               
                        capacity = expand_if_full( &linep, capacity, i );
                        linep[i] = fgetc( inputfd );
                        /*
                        if ( linep[i] == EOF ) {
                                runtime_error( "Error reading file" );
                        }*/ 
                } while ( linep[ i++ ] != '\n' );
                set_size ( &linep, i );
                *datapp = linep; 
                return sizeof( char ) * i;

}

void test_clean_line()
{
        File *fp;
        char *datap;
        int k;
        fp = open_file("long_test.txt");
        size_t num_bytes;

        do{
		
                printf( "%s\n", clean_line( &datap, num_bytes ));
                 
                free(datap);
                num_bytes = readaline( fp, &datap );
                
                /* 
                        clean_line( &datap, num_bytes );
                */


        } while( datap );

        close_file( fp );
}

void test_blank_file()
{
	printf("test_blank_file\n");
	FILE *fp;
	char *datapp = malloc(sizeof(char)*1);
        int k = 0, num_bytes = 0;
        fp = open_file("blank_test.txt");
        do{
                for ( k = 0; k < num_bytes; k++ ){
                        printf("%c", datapp[k] );               
                }
                free(datapp);
		num_bytes = readaline( fp, &datapp );
 
        } while(datapp);

        close_file( fp );
	
	
	
	
	
}

void test_long_lines()
{
	printf("test_long_lines\n");
	FILE *fp,*fout;
	char *datapp = malloc(sizeof(char)*1);
        int k = 0, num_bytes = 0;
        fp = open_file("longlines_test.txt");
	fout = fopen( "longlines_out_test.txt", "a" );
	

        do{
                for ( k = 0; k < num_bytes; k++ ){
                        fprintf(fout, "%c", datapp[k] );               
                }
                free(datapp);
		num_bytes = readaline( fp, &datapp );
 
        } while(datapp);

        close_file( fp );
	
	
	
	
	
}
void test_open_without_reading()
{
	printf("test_long_without_reading\n");
	FILE *fp;
	char *datapp = malloc(sizeof(char)*1);
        int k = 0, num_bytes = 0;
        fp = fopen( "wreading_test.txt", "a" );
        

        do{
                for ( k = 0; k < num_bytes; k++ ){
                        printf("%c", datapp[k] );               
                }
                free(datapp);
		num_bytes = readaline( fp, &datapp );
 
        } while(datapp);

        close_file( fp );
	
	
	
	
}

void test_reading_error()
{
	
	
	
	
}


void test_filling_memory()
{
	void* test;
	printf("test_filling_memory\n");
	FILE *fp;
	char *datapp = malloc(sizeof(char)*1);
        int k = 0, num_bytes = 0;
        fp = open_file("longlines_test.txt");
	
	do{
		test = malloc(sizeof(char)*100000);
		test = malloc(sizeof(char)*100);
	}while(test);
	
	

        do{
		
                for ( k = 0; k < num_bytes; k++ ){
                        printf("%c", datapp[k] );               
                }
                free(datapp);
		num_bytes = readaline( fp, &datapp );
 
        } while(datapp);

	close_file( fp );
	
	
	
}


void test_closed_file()
{
	printf("test_closed_file\n");
	FILE *fp;
	char *datapp = malloc(sizeof(char)*1);
        int k = 0, num_bytes = 0;
        fp = open_file("longlines_test.txt");
	close_file( fp );
        do{
		
                for ( k = 0; k < num_bytes; k++ ){
                        printf("%c", datapp[k] );               
                }
                free(datapp);
		num_bytes = readaline( fp, &datapp );
 
        } while(datapp);

        
	
	
	
	
	
}









void  test_readaline()
{
	
        FILE *fp;
	char *datapp = malloc(sizeof(char)*1);
        int k = 0, num_bytes = 0;
        fp = open_file("test1.txt");

        do{
                for ( k = 0; k < num_bytes; k++ ){
                        printf("%c", datapp[k] );               
                }
                free(datapp);
		num_bytes = readaline( fp, &datapp );
 
        } while(datapp);

        close_file( fp );
}

FILE* open_file ( char* filename ) 
{
        FILE *fp = fopen( filename, "r" );
        return fp;
}

void  close_file( FILE* file_ptr )
{
        if ( (fclose( file_ptr )) ) {
                exit( EXIT_FAILURE );
        }
        
	
}

void  parse_input( int argc, char* argv[] )
{
        if ( argc != 1 ) {
                printf (" dont use \"./%s\" with arguments", argv[0]);
                exit ( EXIT_SUCCESS );
        }
        
}






