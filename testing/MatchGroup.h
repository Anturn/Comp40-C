
/* $Id$ */

#ifndef MATCHGROUP_INCLUDED
#define MATCHGROUP_INCLUDED
#include <seq.h>

typedef struct FilePhraseCount FilePhraseCount;
struct FilePhraseCount {
        int file_num;
        int phrase_num;
};

typedef struct MatchGroup MatchGroup;
struct MatchGroup {
        const char* phrase;
        Seq_T file_phrase_counts;
};

extern MatchGroup* MatchGroup_new( const char* match_phrase );
extern char MatchGroup_add  ( MatchGroup* m , int filenum );

/*Return the length of the array */
extern int  MatchGroup_data ( MatchGroup* m, FilePhraseCount** fpc_array );
extern void MatchGroup_print( MatchGroup* m );
extern void MatchGroup_free ( MatchGroup* m );

/*
extern void *MatchGroup_add( const char* match_phrase );
*/

#endif

/*

void *MatchGroup_new ( char* );
void MatchGroup_add( int filenum,  );

*/
