/*
 *
 *
 *
 *
 */

#include "MatchGroup.h"
#include <atom.h>
#include <stdlib.h>
#include <stdio.h>

void check_args ( int argc, char* argv[] );
void make_struct( int argc, char* argv[]);
void basic_struct_test ();
void capacity_struct_test();

int main( int argc, char* argv[] ) {
        check_args( argc, argv );
        make_struct(argc, argv );
        basic_struct_test(); 
        capacity_struct_test();
        exit( EXIT_SUCCESS );
}


void check_args( int argc, char* argv[] )
{
        printf("%s\n", argv[argc-1]);
}

void make_struct( int argc, char* argv[])
{
        MatchGroup* my_struct;
        const char* char_atom = Atom_string ( argv[ argc-1 ] );
        my_struct = MatchGroup_new( char_atom ); 
        MatchGroup_free( my_struct );
}


void basic_struct_test ()
{
        MatchGroup* my_struct;
        const char* char_atom = Atom_string ( "whatever" );
        my_struct = MatchGroup_new( char_atom ); 
       
        MatchGroup_add( my_struct, -1 );
        MatchGroup_add( my_struct, 1 );
        MatchGroup_add( my_struct, 3 );
        MatchGroup_add( my_struct, 1000 );
        MatchGroup_add( my_struct, 3 );
        MatchGroup_add( my_struct, 3 );
        MatchGroup_add( my_struct, -1 );
        
        MatchGroup_print( my_struct );
        MatchGroup_free( my_struct );
}

void capacity_struct_test()
{
        MatchGroup* my_struct;
        FilePhraseCount *fpc_array ;
        const char* char_atom = Atom_string ( "whatever" );
        my_struct = MatchGroup_new( char_atom ); 
        int i;
        int leng;
        int total = 10000;


        for ( i = 0; i < total; i++ ) {
                MatchGroup_add( my_struct, i%1000 );
        }
        
        leng =  MatchGroup_data(my_struct, &fpc_array);
        for( i = 0; i < leng ; i++) {
                printf("%i \n ", fpc_array[i].file_num);
        } 
        MatchGroup_print( my_struct );
        free(fpc_array);
        MatchGroup_free( my_struct );
}





