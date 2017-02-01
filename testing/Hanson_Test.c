/*
 * Hanson_Test.c
 *
 */


#include <stdio.h>
#include <stdlib.h>

#include <table.h>
#include <seq.h>


void add_numbers_to_sequence ( Seq_T *seq, int num );
void check_input ( int argc, char *argv[] );
void make_table ();
void make_sequence ();


/* ---------------------------------------------------*
 |              Main                                  |
 *----------------------------------------------------*/

int main ( int argc, char *argv[] ) 
{
        check_input( argc, argv );
        
        make_sequence();
        
        /*
        make_table();
        */
}

/* ---------------------------------------------------*
 *----------------------------------------------------*/


void make_table ()
{
        //Table_T test_table;
}

void make_sequence ()
{
        Seq_T test_sequence;
        test_sequence = Seq_new( 100 );
        
        add_numbers_to_sequence ( &test_sequence , 100);
        Seq_free( &test_sequence );
}

void add_numbers_to_sequence ( Seq_T *seq, int num )
{
        int i;

        for ( i = 0; i < num; i++ ) {
                Seq_addhi( (*seq), &i );
        }

}

void check_input ( int argc, char *argv[] )
{
        int i;

        printf(" running %s\n", argv[0] );
        for ( i = 1; i < argc; i++ ) {
                printf ( "%-27s%i\n", argv[i], i );
        }
 
}








/*
 *
 */
