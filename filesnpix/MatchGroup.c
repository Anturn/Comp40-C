/* test_struct
 */

#include <seq.h>
#include "MatchGroup.h"
#include <stdio.h>
#include <stdlib.h>

/* return -1 when not found */
int search ( MatchGroup *m, int filenum );
 
MatchGroup* MatchGroup_new( const char* match_phrase )
{
        MatchGroup* match = malloc( sizeof( MatchGroup )  );
        match-> phrase = match_phrase;
        
        Seq_T sequence = Seq_new( 1 );
        match-> file_phrase_counts = sequence;
         
        return match;
}

/* returns the number of times its been added to.
 */
char MatchGroup_add( MatchGroup *m, int filenum )
{
        int file_location = search( m, filenum );
        FilePhraseCount *fpc;

        if( file_location == -1 ) {
                fpc = malloc( sizeof(FilePhraseCount) );
                fpc-> file_num   = filenum;
                fpc-> phrase_num = 1;
                Seq_addhi( m-> file_phrase_counts, fpc );
                return 0;
        } else {
                fpc = Seq_get( m-> file_phrase_counts, file_location );
                fpc-> phrase_num++;
                return 1;
        }

}





int  MatchGroup_data ( MatchGroup* m, FilePhraseCount** fpc_array )
{
        int i;
        int leng = Seq_length(m->file_phrase_counts);
        *fpc_array = malloc (sizeof(FilePhraseCount)* leng); 
        FilePhraseCount *fpc;
        
        for(i = 0; i < leng ; i++){
                fpc = Seq_get( m-> file_phrase_counts, i );
                (*fpc_array)[i].file_num   = fpc->file_num;
                (*fpc_array)[i].phrase_num = fpc->phrase_num;
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
                printf("f:%i\tc:%i\n", fpc->file_num, fpc->phrase_num );
        }
}

/* Frees Memory */
void MatchGroup_free ( MatchGroup* m )
{
        FilePhraseCount *fpc;
        
        while ( Seq_length( m-> file_phrase_counts ) != 0 ){
                fpc = Seq_remhi( m-> file_phrase_counts );        
                free( fpc );
        }

        Seq_free( &(m-> file_phrase_counts) );
        free( m );
}














