/*
 */

#include "readaline.h"
#include <stdlib.h>
#include <stdio.h>

size_t readaline(FILE *inputfd, char **datapp ) 
{
       
        printf("Hello World!\n");
	datapp = malloc(sizeof(char*));
        char *buffer = malloc( sizeof(char) * 200 );
	
	
	

        *datapp = fgets( buffer, 200, inputfd );
	printf("Hello World1!\n");
        if ( *datapp != NULL ) {
                printf( "%s\n", *datapp );
        }

        /* ---------------------------------*/
        size_t placeholder = 0;
        return placeholder;
}


