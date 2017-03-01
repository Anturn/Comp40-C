/*      
 *      sudoku.c
 *      Modified by: Arpan Gurung and Rui Qin
 *      Last modified: 2/14/17
 *      Using the UArray2 abstraction to identify Sudoku solutions
 *      
 */


#include <stdio.h>
#include <stdlib.h>

#include "sudoku.h"



/* the main function, which contains the parse_input
   function that will check the valid inputs. It also
   check whether the file is valid and can be successfully
   closed */
int main(int argc, char* argv[] ) {
        FILE* file_ptr = NULL;
        parse_input( argc, argv, file_ptr );
        if( file_ptr != NULL && !(fclose(file_ptr)) ){         
                exit(EXIT_SUCCESS);
        }
}



/* check whether the input is valid: number of inputs, type of file
 * Parameters: argc, argv, file pointer
 */
void parse_input(int argc, char* argv[], FILE* file_ptr )
{
        Pnmrdr_T *reader;
        
        if ( argc == 2 ) {
                file_ptr = fopen( argv[1], "rb" );
                if ( file_ptr == NULL ) {
                        runtime_error( "File does not exist." );
                }
                NEW(reader);
                *reader = Pnmrdr_new( file_ptr );
        } else if( argc == 1 ) {
                NEW(reader);
                *reader = Pnmrdr_new( stdin );
        } else {
                runtime_error( "Wrong number of arguments." );
        }
        
        if ( Pnmrdr_data(*reader).type != 2 ){
                free_memory(file_ptr, reader, NULL);
                runtime_error( "Invalid file type." );
        }
        
        check_sudoku( reader, file_ptr );
}



/* Check if it is a sovled sudoku by checking: the height and 
 * the width, the density of each pixel, repitition
 * Parameters: the reader
 */
void check_sudoku( Pnmrdr_T *reader, FILE * file_ptr)
{
        int width  = Pnmrdr_data( *reader ).width;
        int height = Pnmrdr_data( *reader ).height;
        int denominator = Pnmrdr_data( *reader ).denominator;
        
        if(width != SUDOKU_WIDTH || height != SUDOKU_HEIGHT 
                                || denominator != 9) {
                free_memory(file_ptr, reader, NULL);
                runtime_error(
                "The file does not represent a possible sudoku solution.");
        }
        UArray2_T *pixelArray;
        NEW(pixelArray);
        *pixelArray =  UArray2_new (width, height,ELEMENT_SIZE);
        
        /* read */
        if(sudoku_read(reader, pixelArray, width, height) == true) {
                free_memory(file_ptr, reader, pixelArray);
                exit(1);
        }
        
        /* check */
        sudoku_check(reader, file_ptr, pixelArray); 
}




/*---------------------------------------------------------------------------*
 *                                 READ                                      *
 *---------------------------------------------------------------------------* 
 */




/* Put pixels from reader into the 2d array and check whether the density 
 * of each pixel is valid. 
 * Parameters: the reader, the 2d array, width, height
 */
bool sudoku_read(Pnmrdr_T *reader, UArray2_T *pixelArray,
                     int width, int height)
{
        int row, col;
        bool error = false;
        for (row = 0; row < height; row++){
                for(col = 0; col < width; col++){
                        int currentValue = Pnmrdr_get( *reader );
                        if(currentValue > 0 && currentValue< 10){
                                *((int *)UArray2_at
                                  (*pixelArray, col, row)) = currentValue;
                        }else{
                                error = true;
                        }
                }
        }
        return error;
}




/*---------------------------------------------------------------------------*
 *                                 CHECK                                     *
 *---------------------------------------------------------------------------* 
 */




/* Check to see if pixelArray is a valid sudoku solution
 * Parameters: pointers to reader and pixelArray, file pointer
 */
void sudoku_check(Pnmrdr_T *reader, FILE * file_ptr, UArray2_T *pixelArray)
{
        /* bool arrays to check rows, cols, and blocks 
         * last element holds true if there is an error
         */
        bool rowArray[10] = {false};
        bool colArray[10] = {false};
        bool blockArray[10] = {false};
        
        /* check rows, cols, and blocks */
        UArray2_map_row_major(*pixelArray, check_rows, rowArray);
        UArray2_map_col_major(*pixelArray, check_cols, colArray);
        check_blocks(*pixelArray, blockArray);
        
        /* check for errors */
        if (rowArray[9] == true || colArray[9] == true 
                                || blockArray[9] == true) {
                free_memory(file_ptr, reader, pixelArray);
                exit(1);
        }

        free_memory(file_ptr, reader, pixelArray);      
}



/* apply function to check wether each column of the 2D array is valid that
 * is no repetition 
 * Parameters: col, row, the 2d array, a void pointer to the current value,
 *             a void pointer to a boolean array
 */
void check_rows(int col, int row, UArray2_T a, void *curr, void *p)
{
        (void)row;
        (void)a;
        
        /* mark the current value in the bool array */
        int currentValue = *(int*)curr;
        ((bool *)p)[currentValue-1] = true;
        
        /* last column for each row */
        if (col == 8) {
                int count;
                for (count = 0; count < 9; count++){
                        /* if an index has not been marked */
                        if (((bool*)p)[count] != true) {
                                ((bool *)p)[9] = true;
                        }
                        /* reset array elements to false */
                        ((bool *)p)[count] = false;
                        
                }
        }
}



/* apply function to check wether each row of the 2D array is valid that is
 * no repetition 
 * Parameters: col, row, the 2d array, a void pointer to the current 
 *             value, a void pointer to a boolean array
 */
void check_cols(int col, int row, UArray2_T a, void *curr, void *p)
{
        (void)col;
        (void)a;
        
        /* mark the current value in the bool array */
        int currentValue = *(int*)curr;
        ((bool *)p)[currentValue-1] = true;
        
        /* last row for each column */
        if (row == 8) {
                int count;
                for (count = 0; count < 9; count++) {
                        /* if an index has not been marked */
                        if (((bool *)p)[count] != true) {
                                ((bool *)p)[9] = true;
                        }
                        /* reset array elements to false */
                        ((bool *)p)[count] = false;
                }
        }
}

/* Divide the whole sudoku into 9 3 * 3 blocks and check each element
 * Parameters: the 2d array, a pointer to a boolean array
 */
void check_blocks(UArray2_T pixelArray, bool *blockArray)
{
        int row, col;
        
        for (row = 0; row < 9; row+=3) {
                /* move to first element of each block */
                for (col = 0; col < 9; col+=3)
                        check_blockelements(row, col, pixelArray, 
                                            blockArray);
        }
}



/* Go through each element of 3 * 3 block and check for repitition
 * Parameters: col, row, the 2d array, a void pointer to the current value, 
 *             a pointer to a boolean array
 */
void check_blockelements(int row, int col, UArray2_T pixelArray, 
                         bool *blockArray)
{
        int subRow, subCol, currentValue, count;
        
        /* go through block */
        for (subRow = 0; subRow < 3; subRow++) {
                for (subCol = 0; subCol < 3; subCol++) {
                        /* mark the current value in the bool array */
                        currentValue = *((int *)UArray2_at
                                 (pixelArray, col + subCol, row + subRow));
                        blockArray[currentValue-1] = true;
                }
        }
        
        /* check if an index has not been marked */ 
        for (count = 0; count < 9; count++) {
                if (blockArray[count] != true) {
                        blockArray[9] = true;
                }
                /* reset array elements to false */
                blockArray[count] = false;
        }
}




/*---------------------------------------------------------------------------*
 */




/* runtime error function
 * Parameters: the error message
 */
void runtime_error( char *error )
{
        fprintf( stderr, "%s\n", error );
        exit(EXIT_FAILURE);
}



/* free used memory
 * Parameters: file pointer, reader, pixel array
 */
void free_memory(FILE * file_ptr, Pnmrdr_T * reader, UArray2_T * pixelArray)
{
        if (file_ptr != NULL)
                fclose(file_ptr);
        
        if (reader != NULL) {
                Pnmrdr_free(reader);
                FREE(reader);
        }
        
        if (pixelArray != NULL) {
                UArray2_free( pixelArray);
                FREE(pixelArray);
        }
}
