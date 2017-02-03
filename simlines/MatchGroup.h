/*
 *      MatchGroup.h
 *      by Ashton Stephens and Rui Qin, 1/31/17
 *      Files, Pictures and Interfaces
 *      
 *      header file for the abstract data structure implementation
 *      MatchGroup. Designed to hold line locations to Matched phrases.
 *      Not intended for use outside of Simlines program.
 */

#ifndef MATCHGROUP_INCLUDED
#define MATCHGROUP_INCLUDED
#include <seq.h>

typedef struct MatchGroup MatchGroup;
struct MatchGroup {
        const char* phrase;
        Seq_T file_phrase_counts;
};

typedef struct FilePhraseCount FilePhraseCount;
struct FilePhraseCount {
        int  file_num;
        int* line_nums;
        int  capacity;
        int  length;
};


/*------------------------------------------------------
 |      Parent Datastructure : MatchGroup
 -------------------------------------------------------*/

/* calls malloc to get assign a pointer to a MatchGroup. 
 * Expects an immutable atom pointing to an array of chars.
 * 
 * checked runtime error:
 *      cannot use malloc to allocate memory
 * 
 * unchecked runtime error:
 *      match_phrase is NULL     
 *
 * */
extern MatchGroup* MatchGroup_new( const char *match_phrase );

/* Adds a file number and a line number to the MatchGroup.
 * 
 * 
 * */
extern char MatchGroup_add  ( MatchGroup *m, int filenum, int linenum );

/* Return the length of the array */
extern int  MatchGroup_data ( MatchGroup *m, FilePhraseCount ***fpc_array );

extern void MatchGroup_free ( MatchGroup *m );


/*------------------------------------------------------
 |      Child Datastructure : FilePhraseCount
 -------------------------------------------------------*/

extern FilePhraseCount* FilePhraseCount_new ( int filenum );

/* returns the number of elements in the array placed in the pointer
 * to an array data. Array is allocated to the heap. client must
 * free the data.*/
extern int  FilePhraseCount_data ( FilePhraseCount* fpc, int **data );

/* coppies one FilePhraseCount to another.
 * */
extern void FilePhraseCount_copy ( FilePhraseCount *fpc,
                                   FilePhraseCount **dest );

/* Frees the Seq_T in FilePhraseCount */
extern void FilePhraseCount_free ( FilePhraseCount *fpc );

/* Adds a line number to the FilePhraseCount */
extern void FilePhraseCount_add  ( FilePhraseCount *fpc, int linenum );

#endif
