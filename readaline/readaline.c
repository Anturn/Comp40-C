/*
 */

#include "readaline.h"
#include <stdlib.h>
#include <stdio.h>

#define TRUE 1
#define FALSE 0

char valid_input( FILE *inputfd, char **datapp );
int expand_line( char *old_array, int old_cap );
void checked_runtime_error();

size_t readaline(FILE *inputfd, char **datapp ) 
{
        int i = 0;
        int capacity = 100;
        char *line = malloc( sizeof(char)*capacity );
        if ( !valid_input( inputfd, datapp  ) ){
                checked_runtime_error();
                return 0;
        }else if ( feof( inputfd ) ) {
                printf("END OF FILE\n");
                *datapp = NULL;
                return 0;
        } else {
                line[0] = '0'; 
                do {                
                
                        line[i] = fgetc( inputfd );
                        if ( i >= capacity ) {
                                capacity = expand_line( line, capacity );
                        }
                        

                } while ( line[i++] != '\n' );
        
                /*!!!*/ 
                line[i] = '\0';
                /*!!!*/
                
                (*datapp) = line; 
                return sizeof(char) * i;
        }
}

/* ------------------------------------------------------  */

char valid_input( FILE *inputfd, char **datapp )
{
        if ( inputfd == NULL || datapp == NULL ) {
                return FALSE;
        }
        return TRUE;
}

int expand_line( char *old_array, int old_cap )
{
        int  new_cap = old_cap * 2;
        char *new_array = malloc( sizeof(char) * new_cap );
         
        int i;
        for( i = 0; i < old_cap; i++ ){
                new_array[i] = old_array[i];
        }
        
        free( old_array );
        old_array = new_array;
        return new_cap;
}

void checked_runtime_error()
{
}






