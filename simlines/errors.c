/*
 *      errors.c
 *      by Ashton Stephens and Rui Qin, 2/02/17
 *      Files, Pictures and Interfaces
 *      
 *      implementation file for functions that handle basic checked
 *      runtime errors. 
 */

#include <stdio.h>
#include <stdlib.h>
#include "errors.h"

/* prints the error to stderr and exits program with
 * a failure 
 * 
 * unchecked runtime error: 
 *      NULL pointer to error
 * */
void runtime_error( char *error )
{
        fprintf( stderr, "%s\n", error );
        exit( EXIT_FAILURE );
}

/* function similarly to -alloc functions. Send a runtime
 * error instead of returning NULL upon failed memory
 * assignment 
 * */
void *malloc_cre ( size_t bytes ) 
{
        void* new_ptr =  malloc( bytes );
        if ( new_ptr == NULL ) {
                runtime_error( "out of memory in heap" );
        }
        return new_ptr;
}

void *realloc_cre ( void *ptr, size_t bytes )
{
        ptr =  realloc( ptr, bytes );
        if ( ptr == NULL ) {
                runtime_error( "out of memory in heap" );
        }
        return ptr;
}

/* functions similarly to fopen. Sends a runtime
 * error instead of returning NULL upon failing to
 * open the file.
 *
 * unchecked runtime error: 
 *      NULL pointer to filename
 *      NULL pointer to mode
 * */
FILE *fopen_cre ( char *filename, char *mode ) 
{
        FILE* new_file = fopen( filename, mode );
        if ( new_file == NULL ) {
                fprintf( stderr, "unable to open %s\n", filename );
                exit( EXIT_FAILURE );
        }
        return new_file;
}

/* produces a checked runtime error if  ptr is NULL.
 *
 * unchecked runtime error:
 *      NULL pointer to var_name
 * */
void check_null( void *ptr, char *var_name )
{
        if ( ptr == NULL ) { 
                fprintf( stderr, "recieved NULL pointer %s\n", var_name );
                exit( EXIT_FAILURE );
        }
}


