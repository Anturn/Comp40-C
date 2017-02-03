/* 
 *
 * */

#include <stdio.h>
#include <stdlib.h>
#include "clean_line.h"

void clean_line    ( char **datapp, size_t num_bytes );
int  if_full_expand( char **linepp, int capacity, int num );
char is_word_char  ( char c );
char is_blank      ( char* line );

/* turn all non-word groups of characters into a single space,
 * and to add a null character at the end of datapp 
 * */
void clean_line( char **datapp, size_t num_bytes )
 {
        int  length = num_bytes, capacity = 10;
        char this_is_word, last_is_word = 0, *clean;
        int  i, length_clean = 0;
        clean = malloc( sizeof( char ) * capacity );
        
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
        if ( !is_blank( clean ) ) {
                (*datapp) = clean;
        } else {
                (*datapp) = NULL;
                free( clean );
        }
        return; 
}

/* returns non-zero value if it is a word char */
char is_word_char ( char c )
{
        return ((c >= 65 && c<= 90 ) ||
                (c >= 97 && c<= 122) ||
                (c >= 48 && c<= 57 ) ||
                (c == 95));
}

/*
 * */
int if_full_expand( char **linepp, int capacity, int num )
{
        if ( num == capacity ) {
                capacity *= 2;
                *linepp = realloc ( *linepp, sizeof( char ) * capacity ); 
        }
        return capacity;
}

char is_blank ( char* line ) {
        int i = 0;
        while( line[++i] ){
                if ( line[i] != 32 && line[i] != 10  ) {
                        return 0;
                }
        }
        return 1;
}


























