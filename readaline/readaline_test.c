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
void test_blank_file();
void test_long_lines();
void test_open_without_reading();
void test_reading_error();
void test_filling_memory();
void test_closed_file();
char is_word_char ( char c );
int  if_full_expand ( char **linepp, int capacity, int num );
        /*
        test_blank_file();
        test_long_lines();
        test_open_without_reading();
	test_reading_error();
        test_filling_memory();
        test_closed_file();
        */
 



/* 
 *
 * */
void clean_line(char **datapp, size_t num_bytes);
void test_clean_line();

int main ( int argc, char *argv[] ) 
{
        parse_input( argc, argv );
        test_clean_line();
       /*return */EXIT_SUCCESS;

}

/*----------------------------------------------------------------------- */





/* turn all non-word groups of characters into a single space,
 * and to add a null character at the end of datapp 
 * */
void clean_line( char **datapp, size_t num_bytes )
 {
        int  length = num_bytes, capacity = 10;
        char this_is_word, last_is_word = 0, *clean;
        int  i, length_clean = 0;
        clean = malloc( sizeof( char ) * capacity );

        /**datapp = realloc( (*datapp), length++ );*/
        for ( i = 0; i < length; i++ ) {
                capacity = if_full_expand ( &clean, capacity, length_clean );
                this_is_word = is_word_char((*datapp)[i]);                      
                if ( this_is_word ) {
                        clean[ length_clean++ ] = (*datapp)[i]; 
                } else if ( last_is_word ) {
                        clean[ length_clean++ ] = 32 ; 
                }
                last_is_word = this_is_word;
        }

        if ( length_clean != 0 && clean[ length_clean-1 ] == 32 ) {
                clean[ length_clean-1 ] = 0;
        } else {
                capacity = if_full_expand( datapp, capacity, length_clean );
                clean[ length_clean ] = 0; 
        }       
        free( *datapp );
        (*datapp) = clean;
        return; 
}

void test_clean_line()
{
        FILE *fp = open_file("clean_test.txt");
        char *datap;
        size_t num_bytes;
        num_bytes = readaline( fp, &datap );
       
        while ( datap ) {
                clean_line( &datap, num_bytes ); 
                printf( "%s\n", datap );
                free(datap);
                num_bytes = readaline( fp, &datap );

        };

        close_file( fp );
}

/* returns non-zero value if it is a word char */
char is_word_char ( char c )
{
        return ((c >= 65 && c<= 90 ) ||
                (c >= 97 && c<= 122) ||
                (c >= 48 && c<= 57 ) ||
                (c == 95));
}

/* */
int if_full_expand( char **linepp, int capacity, int num )
{
        if ( num == capacity ) {
                capacity *= 2;
                *linepp = realloc ( *linepp, sizeof( char ) * capacity ); 
        }
        return capacity;
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






