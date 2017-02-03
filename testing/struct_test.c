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
void print_info_test();

int main( int argc, char* argv[] ) {
        check_args( argc, argv );
        make_struct(argc, argv );
        basic_struct_test();
    //    capacity_struct_test();
        print_info_test ();
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
       
        MatchGroup_add( my_struct, -1,1 );
        MatchGroup_add( my_struct, 1, 1 );
        MatchGroup_add( my_struct, 3, 1 );
        MatchGroup_add( my_struct, 1000, 1 );
        MatchGroup_add( my_struct, 3, 1 );
        MatchGroup_add( my_struct, 3, 1 );
        MatchGroup_add( my_struct, -1, 1 );
        
        MatchGroup_print( my_struct );
        MatchGroup_free( my_struct );
}

void capacity_struct_test()
{
        MatchGroup* my_struct;
        const char* char_atom = Atom_string ( "whatever" );
        my_struct = MatchGroup_new( char_atom ); 
        int i;
        int total = 99999;

        for ( i = 0; i < total; i++ ) {
                MatchGroup_add( my_struct, i%1000, i%100 );
        }
        MatchGroup_print( my_struct );
        MatchGroup_free( my_struct );
}


void print_info_test ()
{
        MatchGroup* my_struct;
        const char* char_atom = Atom_string ( "whatever!" );
        my_struct = MatchGroup_new( char_atom ); 
        FilePhraseCount **fpc_array;
        int i, j, MG_length, FPC_length, *datap;
        int total = 1000;
        
        for ( i = 0; i < total; i++ ) {
                MatchGroup_add( my_struct, i%10, i%1000 );
        }

        printf("%s\n", my_struct-> phrase );
        MG_length = MatchGroup_data( my_struct, &fpc_array );
        for ( i = 0; i < MG_length; i++ ) {
                FPC_length = FilePhraseCount_data( fpc_array[i], &datap );
                printf( "\n\t%i \n", fpc_array[i]-> file_num );
                for ( j = 0; j < FPC_length; j++ ) {
                        printf( " \t\t%i\n", datap[j] );
                }
                free( datap );
                FilePhraseCount_free( (fpc_array[i]) );
        }
        free( fpc_array );
       
        /* MatchGroup_print( my_struct ); */
        MatchGroup_free( my_struct );
}



