
/* $Id$ */

#ifndef MATCHGROUP_INCLUDED
#define MATCHGROUP_INCLUDED

typedef struct MatchGroup MatchGroup;
struct MatchGroup {
        const char* phrase;
};

extern MatchGroup* MatchGroup_new( const char* match_phrase );

/*
extern void *MatchGroup_add( const char* match_phrase );
*/


#endif

/*

void *MatchGroup_new ( char* );
void MatchGroup_add( int filenum,  );

*/
