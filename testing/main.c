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

/* ---------------------------------------------- */

int main ( int argc, char *argv[] ) 
{       
        check_input( argc, argv );
        run_simlines( argc, argv );
}

/* ---------------------------------------------- */

void run_simlines ( int argc, char* argv[] ) 
{
        Seq_T   matches; /* TODO: declare a new sequence_t*/
        Table_T table; /* TODO: declare new table */

        process_files_into_table ( argc, argv, matches, table );
        print_similar_lines( matches, table );
}


void process_all_files_into_table ( int argc,               char *argv[], 
                                    Seq_T matches,  Table_T table )
{
        FILE *fp;
        int i;
        
        /* assumes already checked argc and argv */
        for ( i = 1; i < argc; i++ ){
                fp = fopen ( argv[i], "r" )
                process_file_into_table ( fp, i, table, matches ) ;
                close ( fp ); 
        }   
}


void process_file_into_table ( FILE *fp, int i, Table_T table, Seq_T matches )
{
        char    *line;
        size_t  length;

        length = readaline( fp, &line );
        while ( length != 0 ) {
                clean_line ( &line );
                put_into_table ( line, length, i, table, matches );
                length = readaline ( fp, &line );
        } 
}

void put_into_table (   char* line,     int     length, 
                        int   file_num, Table_T table, Seq_T matches )
{
        /*
         *
         *
         * TODO: S
         *
         *
         *
         * */
        line = Atom_new( line, length );       
        MatchGroup*  group;

        group = Table_get ( &line );

        if ( group == NULL ) {
                /* WE WRITE THIS OURSELVES */ 
                
                /*
                void *MatchGroup_new ( char* );
                */

                group = MatchGroup_new( &line );                
        }else {
                

        }

        /* we know we have a valid group */
        
        /*
        MatchGroup_add( int filenum,  );
        */
        
        MatchGroup_add( file_num, group );

        Table_put ( table, &line, &group  );  
               
}

/* leaves only word characters separated by single spaces*/
void clean_line ( char **line )
{
        /*
        TODO: do
        */
}





















































