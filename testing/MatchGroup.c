/* test_struct
 */

#include <seq.h>
#include "MatchGroup.h"
#include <stdio.h>
#include <stdlib.h>

/* -------------------------------------------------------------- *
 |              Child Data Structure : FilePhraseCount
 * -------------------------------------------------------------- */

/* return -1 when not found */
int search ( MatchGroup *m, int filenum );
 
FilePhraseCount* FilePhraseCount_new ( int filenum )
{
        FilePhraseCount *fpc = malloc( sizeof( FilePhraseCount )  );
        fpc-> file_num  = filenum;
        fpc-> capacity  = 1;
        fpc-> line_nums = malloc( sizeof( int ) * 1 );
        fpc-> length = 0;
        return fpc;       
}

/* returns the number of elements in the array placed in the pointer
 * to an array data. Array is allocated to the heap. client must
 * free the data.*/
int  FilePhraseCount_data ( FilePhraseCount* fpc, int **datapp )
{
        int i;
        int length      = fpc-> length;
        int *line_nums  = fpc-> line_nums;
        *datapp         = malloc ( sizeof( int ) * length ); 
        
        for( i = 0; i < length; i++ ){
                (*datapp)[i] = line_nums[i];
        }
        return length;
}

/* allocates dest into a new place in the heap. dest
 * should not be allocated beforehand */
void FilePhraseCount_copy ( FilePhraseCount*  fpc,
                            FilePhraseCount** dest )
{
        int i;
        int length = fpc-> length;
        (*dest) = malloc( sizeof( FilePhraseCount ) );
        int *line_nums_copy = malloc( sizeof( int ) * length ); 
        int *line_nums      = fpc-> line_nums;
        (*dest)-> file_num  = fpc-> file_num; 
        (*dest)-> capacity  = fpc-> capacity;
        (*dest)-> length    = fpc-> length;

        for ( i = 0; i < length; i++ ) {
                line_nums_copy[i] = line_nums[i];
        }

        (*dest)-> line_nums = line_nums_copy;
}

/* Frees the array in FilePhraseCount */
void FilePhraseCount_free ( FilePhraseCount *fpc )
{
        free( fpc->line_nums ); 
        free( fpc );    
}

/* adds line to PhraseCount */
void FilePhraseCount_add  ( FilePhraseCount *fpc, int linenum )
{       
        fpc-> length++;
        if ( fpc-> length == fpc-> capacity ) {
                fpc-> capacity = 2 * (fpc-> capacity);
                fpc-> line_nums = realloc( fpc-> line_nums
                                , sizeof( int ) * fpc-> capacity); 
        }
        fpc-> line_nums[ fpc->length-1 ] = linenum;
}


/* -------------------------------------------------------------- *
 |              Parent Data Structure : MatchGroup
 * -------------------------------------------------------------- */


MatchGroup* MatchGroup_new( const char* match_phrase )
{
        MatchGroup* match = malloc( sizeof( MatchGroup )  );
        match-> phrase = match_phrase;
        
        Seq_T sequence = Seq_new( 1 );
        match-> file_phrase_counts = sequence;
         
        return match;
}

/* Adds a file and line number to the MatchGroup.
 *
 * Unchecked Runtime Errors:
 *      Passing NULL MatchGroup pointer m
 * */
char MatchGroup_add( MatchGroup *m, int filenum, int linenum )
{
        int file_location = search( m, filenum );
        FilePhraseCount *fpc;

        if( file_location == -1 ) {
                fpc = FilePhraseCount_new( filenum );
                FilePhraseCount_add( fpc,  linenum );
                Seq_addhi( m-> file_phrase_counts, fpc );
                return 0;
        } else {
                fpc = Seq_get( m-> file_phrase_counts, file_location );
                FilePhraseCount_add( fpc, linenum );
                return 1;
        }
}

/* */
int  MatchGroup_data ( MatchGroup* m, FilePhraseCount*** fpc_array )
{
        /* TODO: FIND THE MEMORY LEAK (SINGLE POINTER MISSING?! 
         * HIGHLY POSSIBLE HERE */
        int i;
        int leng = Seq_length( m->file_phrase_counts );
        (*fpc_array) = malloc ( sizeof( FilePhraseCount* ) * leng ); 
        FilePhraseCount *fpc;
        for( i = 0; i < leng; i++ ){
                fpc = Seq_get( m-> file_phrase_counts, i );
                FilePhraseCount_copy ( fpc, &((*fpc_array)[i])  ); /* */ 
        }
        return leng;
}

/* search the sequence and return index. Return -1 if not found*/
int search ( MatchGroup *m, int filenum )
{
        int i;
        int leng = Seq_length( m-> file_phrase_counts );
        FilePhraseCount *fpc;

        for ( i = 0; i < leng; i++ ) {
                fpc = Seq_get( m-> file_phrase_counts, i );
                if ( fpc-> file_num == filenum ) {
                        return i;
                }
        }
        return -1;
}

/* prints Matchgroup */
void MatchGroup_print( MatchGroup *m )
{
        int i;
        int leng = Seq_length( m-> file_phrase_counts );
        FilePhraseCount *fpc;
        
        printf( "%s\n", m-> phrase );
        for ( i = 0; i < leng; i++ ) {
                fpc = Seq_get( m-> file_phrase_counts, i );
                printf("f:%i\t\n", fpc->file_num  );
        }
}

/* Frees Memory */
void MatchGroup_free ( MatchGroup* m )
{
        /* TODO: make line_nums an array */
        FilePhraseCount *fpc;
        
        while ( Seq_length( m-> file_phrase_counts ) != 0 ){
                fpc = Seq_remhi( m-> file_phrase_counts );        
                FilePhraseCount_free( fpc );
        }

        Seq_free( &(m-> file_phrase_counts) );
        free( m );
}





