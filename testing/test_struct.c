/* test_struct
 */

#include "MatchGroup.h"
#include <stdio.h>
#include <stdlib.h>


MatchGroup* MatchGroup_new( const char* match_phrase )
{
        MatchGroup* match = malloc( sizeof( MatchGroup )  );
        match-> phrase = match_phrase;

}


