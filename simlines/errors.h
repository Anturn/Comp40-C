/*
 *      errors.h
 *      by Ashton Stephens and Rui Qin, 2/02/17
 *      Files, Pictures and Interfaces
 *      
 *      header file for functions that handle basic checked
 *      runtime errors. 
 */

#ifndef ERR_HANDLE_INCLUDED
#define ERR_HANDLE_INCLUDED

/* prints the error to stderr and exits program with
 * a failure 
 * 
 * unchecked runtime error: 
 *      NULL pointer to error
 * */
extern void runtime_error( char *error  );

/* function similarly to -alloc functions. Send a runtime
 * error instead of returning NULL upon failed memory
 * assignment 
 * */
extern void *malloc_cre  ( size_t bytes  );
extern void *realloc_cre ( void *ptr, size_t bytes );

/* functions similarly to fopen. Sends a runtime
 * error instead of returning NULL upon failing to
 * open the file.
 *
 * unchecked runtime error: 
 *      NULL pointer to filename
 *      NULL pointer to mode
 * */
extern FILE *fopen_cre ( char *filename, char *mode );

/* produces a checked runtime error if  ptr is NULL.
 *
 * unchecked runtime error:
 *      NULL pointer to var_name
 * */
extern void check_null( void *ptr, char *var_name );

#endif
