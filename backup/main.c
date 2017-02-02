/*
 * Simlines Main
 *
 *
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <table.h>
#include <seq.h>
#include <atom.h>
#include "readaline.h" 
#include "MatchGroup.h"

void free_table_element ( const void *key, void **value, void *cl );
char in_sequence ( Seq_T sequence, const char *query );
void check_my_input( int argc, char *argv[] );
void run_simlines ( int argc, char* argv[] );
void process_all_files_into_table ( int argc,   char *argv[], 
                                    Seq_T matches,  Table_T table );
void process_file_into_table ( FILE *fp, int i, Table_T table, Seq_T matches );
void put_into_table(   char* line,     int line_num,
                        int file_num,   Table_T table,  Seq_T matches );
void clean_line    ( char **datapp, size_t num_bytes );
char is_word_char  ( char c );
int  if_full_expand( char **linepp, int capacity, int num );
void print_similar_lines ( Seq_T matches, char *argv[] );
void exit_program ( Seq_T matches, Table_T table );

/* ---------------------------------------------- */

int main ( int argc, char *argv[] ) 
{       
        check_my_input( argc, argv );
        run_simlines( argc, argv );
        return 1;
}

/* ---------------------------------------------- */

void check_my_input( int argc, char *argv[] )
{
        /* TODO: make this good */
}


void run_simlines ( int argc, char* argv[] ) 
{
        Seq_T   matches    = Seq_new( 30 );
        Table_T table      = Table_new( 100, NULL, NULL );
        
        process_all_files_into_table (  argc, argv, matches, table );
        print_similar_lines ( matches, argv );
        exit_program( matches, table );
}

void print_similar_lines ( Seq_T matches, char *argv[] )
{
        MatchGroup *my_struct;
        FilePhraseCount **fpc_array;
        int i, j, k, MG_length, FPC_length, SEQ_length, *datap;
       
        SEQ_length = Seq_length( matches ); 
        for ( k = 0; k < SEQ_length; k++  ) {
                my_struct = Seq_remhi( matches );
                printf("%s\n", my_struct-> phrase );
                MG_length = MatchGroup_data( my_struct, &fpc_array );
                for ( i = 0; i < MG_length; i++ ) {
                        FPC_length = FilePhraseCount_data( fpc_array[i], &datap );
                        for ( j = 0; j < FPC_length; j++ ) {
                                printf( "%-27s%i\n",argv[ fpc_array[i]-> file_num ], datap[j] );
                        }
                        free( datap );
                        FilePhraseCount_free( (fpc_array[i]) );
                }
                free( fpc_array );
        }
        /* MatchGroup_print( my_struct ); */

}

void process_all_files_into_table ( int argc,   char *argv[],
                                    Seq_T matches,  Table_T table )
{
        FILE *fp;
        int i;
        
        for ( i = 1; i < argc; i++ ){
                fp = fopen ( argv[i], "r" );
                process_file_into_table ( fp, i, table, matches );
                fclose ( fp );
        }   
}

/*  Take a file pointer, an int i, a table, and a secuence of matches. All
 *  of the locations of lines in the file are placed into the table, and 
 *  any that come up twice, or that have appeared in a separate file, get 
 *  placed in the sequence matches.
 * */
void process_file_into_table ( FILE *fp, int i, Table_T table, Seq_T matches )
{
        char    *line;
        size_t  length;
        int     line_num = 0; 

        length = readaline( fp, &line );
        while ( length != 0 ) {
                clean_line ( &line, length );
                put_into_table ( line, line_num, i, table, matches );
                line_num++;
                length = readaline ( fp, &line );
        } 
}

/* */
void put_into_table (   char* line,     int line_num,
                        int file_num,   Table_T table,  Seq_T matches )
{
        const char *key = Atom_string( line ); 
        MatchGroup *group;

        group = Table_get ( table, key ); /* possible to place &line */

        if ( group == NULL ) {
                group = MatchGroup_new( key );                
        } else if( !in_sequence( matches, key ) ) {
                Seq_addhi( matches, group ); /* */
        }
                
        MatchGroup_add( group, file_num, line_num );
        Table_put ( table, key, group );  
}


char in_sequence ( Seq_T sequence, const char *query ) 
{
        int length = Seq_length( sequence );
        int i;

        for ( i = 0; i < length; i++ ) {
                if ( query == Seq_get( sequence, i ) ) {
                        return 1;
                }       
        }
        return 0;
}

/* turn all non-word groups of characters into a single space,
 * and to add a null character at the end of datapp 
 * */
void clean_line( char **datapp, size_t num_bytes )
 {
        int  length = num_bytes, capacity = 10;
        char this_is_word, last_is_word = 0, *clean;
        int  i, length_clean = 0;
        clean = malloc( sizeof( char ) * capacity );

        /* *datapp = realloc( (*datapp), length++ );*/
        for ( i = 0; i < length; i++ ) {
                capacity = if_full_expand ( &clean, capacity, length_clean );
                this_is_word = is_word_char((*datapp)[i]);                      
                if ( this_is_word ) {
                        clean[ length_clean++ ] = (*datapp)[i]; 
                } else if ( last_is_word ) {
                        clean[ length_clean++ ] = 32 ; 
                }
                last_is_word = this_is_word;
        }

        if ( length_clean != 0 && clean[ length_clean-1 ] == 32 ) {
                clean[ length_clean-1 ] = 0;
        } else {
                capacity = if_full_expand( datapp, capacity, length_clean );
                clean[ length_clean ] = 0; 
        }       
        free( *datapp );
        (*datapp) = clean;
        return; 
}


/* returns non-zero value if it is a word char */
char is_word_char ( char c )
{
        return ((c >= 65 && c<= 90 ) ||
                (c >= 97 && c<= 122) ||
                (c >= 48 && c<= 57 ) ||
                (c == 95));
}

/* */
int if_full_expand( char **linepp, int capacity, int num )
{
        if ( num == capacity ) {
                capacity *= 2;
                *linepp = realloc ( *linepp, sizeof( char ) * capacity ); 
        }
        return capacity;
}


/*--------------------------------------------------------------*
 |                    Program Termination                       |
 *--------------------------------------------------------------*/

void exit_program( Seq_T matches, Table_T table )
{
        Table_map ( table, free_table_element, NULL ); 
        Table_free( &table );
        Seq_free  ( &matches );
}

void free_table_element ( const void *key, void **value, void *cl ) {
        MatchGroup_free( *value );
}





















































