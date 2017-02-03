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

char in_sequence ( Seq_T sequence, char *query );
void check_input( int argc, char *argv[] );
void run_simlines ( int argc, char* argv[] );
void process_all_files_into_table ( int argc,   char *argv[], Seq_T file_names,
                                    Seq_T matches,  Table_T table );
void process_file_into_table ( FILE *fp, int i, Table_T table, Seq_T matches );
void put_into_table (   char* line,     int line_num,
                        int file_num,   Table_T table,  Seq_T matches );
char in_sequence  ( Seq_T sequence, char *query );
void clean_line   ( char **datapp, size_t num_bytes );
char is_word_char ( char c );
int  if_full_expand( char **linepp, int capacity, int num );

/* ---------------------------------------------- */

int main ( int argc, char *argv[] ) 
{       
        check_input( argc, argv );
        run_simlines( argc, argv );
        return 1;
}

/* ---------------------------------------------- */

void check_input( int argc, char *argv[] )
{
}


void run_simlines ( int argc, char* argv[] ) 
{
        Seq_T   matches; /* TODO: declare a new sequence_t*/
        Seq_T   file_names;
        Table_T table; /* TODO: declare new table */
        
        process_all_files_into_table (  argc, argv, file_names, 
                                        matches, table );
        print_similar_lines ( matches, table );
}

void process_all_files_into_table ( int argc,   char *argv[], Seq_T file_names,
                                    Seq_T matches,  Table_T table )
{
        FILE *fp;
        int i;
        (matches)    = Seq_new( 30 );        
        (file_names) = Seq_new( 3  );        
 
        /* assumes already checked argc and argv */
        for ( i = 1; i < argc; i++ ){
                Seq_addhi( file_names, argv[i] );
                fp = fopen ( argv[i], "r" );
                process_file_into_table ( fp, i, table, matches );
                close ( fp );
        }   
}


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

void put_into_table (   char* line,     int line_num,
                        int file_num,   Table_T table,  Seq_T matches )
{
        line = Atom_string( line ); 
        MatchGroup*  group;

        table = Table_new( 100, NULL, NULL );
        group = Table_get ( line ); /* possible to place &line */

        if ( group == NULL ) {
                group = MatchGroup_new( line );                
        } else if( !in_sequence( matches, line ) ) {
                Seq_addhi( matches, line );
        }
                
        MatchGroup_add( group, filenum, line_num );
        Table_put ( table, line, group );  
}


char in_sequence ( Seq_T sequence, char *query ) 
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





















































