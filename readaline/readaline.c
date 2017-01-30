/*
 *      readaline.c
 *      by Ashton Stephens and Rui Qin, 1/28/17
 *      Files, Pictures and Interfaces
 *      
 *      reads a line from a file and places it in a character array.
 */

#include "readaline.h"
#include <stdlib.h>
#include <stdio.h>

char at_EOF        ( FILE *inputfd );
void check_input   ( FILE *inputfd, char **datapp );
int  expand_if_full( char **linepp, int  capacity, int num );
void set_size      ( char **linepp, int  new_capacity ); 
void runtime_error ( char *error );

/* --------------------------------------------------------*
 * |                    Main Function
 * --------------------------------------------------------*/

/* takes in a file pointer and a pointer to a char array and
 * fills the array with the next line of file. Returns the 
 * number bytes at the location pointed to by *datapp. relies
 * on client freeing memory allocated to *datapp.
 */
size_t readaline( FILE *inputfd, char **datapp ) 
{        
        int i = 0;
        int capacity = 10;
        char *linep = malloc( sizeof( char ) * capacity ); 

        check_input( inputfd, datapp );
        if ( at_EOF( inputfd ) ) {
                free( linep );
                *datapp = NULL;
                return 0;
        } else {
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
}

/* --------------------------------------------------------*
 * |                     Helper Functions
 * --------------------------------------------------------*/

/* Returns a non zero value if the next character the file
 * will return on a call of fgetc() is EOF
 */
char at_EOF ( FILE *inputfd )
{
        char temp;
        temp = fgetc( inputfd );
        ungetc( temp, inputfd );
        return ( temp == EOF );
}

/* Checks the function input values for the readaline function.
 * If inputs are invalid, terminates the program with a failure.
 */
void check_input( FILE *inputfd, char **datapp )
{
        if ( inputfd == NULL) {
                runtime_error( "readaline called on null FILE pointer" );
        } else if (datapp == NULL ) {
                runtime_error( "readaline called on null char* pointer" );
        }
}

/* Expands the array pointed to by linepp if num is the same
 * size as the capacity. returns the new capacity of the array.
 */
int expand_if_full( char **linepp, int capacity, int num )
{
        if ( num == capacity ) {
                capacity *= 2;
                set_size( linepp, capacity );       
        }
        return capacity;
}

/* Sets the size of the array pointed to by linepp to be new_capacity.
 * expects a non-zero value for new_capacity
 */
void set_size ( char **linepp, int new_capacity ) 
{
        *linepp = realloc( *linepp, sizeof( char ) * new_capacity ); 
        if ( *linepp == NULL ) {
                runtime_error( 
                "readaline experienced memory allocation fail" );
        }
}

/* prints error to stderr and exits the program with a failure.
 */
void runtime_error( char *error )
{
        fprintf( stderr, "%s\n", error );
        exit( EXIT_FAILURE );
}


