
/* 
 * MatchGroup
 *
 *
 * */

#ifndef MATCHGROUP_INCLUDED
#define MATCHGROUP_INCLUDED
#include <seq.h>

/*------------------------------------------------------
 Child Datastructure : FilePhraseCount
 -------------------------------------------------------*/

typedef struct FilePhraseCount FilePhraseCount;
struct FilePhraseCount {
        int  file_num;
        int* line_nums;
        int  capacity;
        int  length;
};

extern FilePhraseCount* FilePhraseCount_new ( int filenum );

/* returns the number of elements in the array placed in the pointer
 * to an array data. Array is allocated to the heap. client must
 * free the data.*/
extern int  FilePhraseCount_data ( FilePhraseCount* fpc, int **data );

extern void FilePhraseCount_copy ( FilePhraseCount *fpc,
                                   FilePhraseCount **dest );

/* Frees the Seq_T in FilePhraseCount */
extern void FilePhraseCount_free ( FilePhraseCount *fpc );
extern void FilePhraseCount_add  ( FilePhraseCount *fpc, int linenum );

/*------------------------------------------------------
 Parent Datastructure : MatchGroup
 -------------------------------------------------------*/

typedef struct MatchGroup MatchGroup;
struct MatchGroup {
        const char* phrase;
        Seq_T file_phrase_counts;
};

extern MatchGroup* MatchGroup_new( const char *match_phrase );
extern char MatchGroup_add  ( MatchGroup *m, int filenum, int linenum );

/*Return the length of the array */
extern int  MatchGroup_data ( MatchGroup *m, FilePhraseCount ***fpc_array );
extern void MatchGroup_print( MatchGroup *m );
extern void MatchGroup_free ( MatchGroup *m );

#endif
