/*      
 *      unblackedges.c
 *      Modified by: Arpan Gurung and Rui Qin 
 *      Last modified: 2/14/17
 *      Part D: Using the Bit2 abstraction to remove black edges
 *      
 */

#include <stdio.h>
#include <stdlib.h>
#include "unblackedges.h"




/* the main function, which contains the parse_input
 * function that will check the valid inputs. It also
 * check whether the file is valid and can be successfully
 * closed 
 */ 
int main(int argc, char* argv[] ) 
{
        FILE* file_ptr = NULL;
        parse_input( argc, argv, file_ptr );
        if( file_ptr != NULL && !(fclose(file_ptr)) ){         
                exit( EXIT_SUCCESS );
        }
}



/* check whether the input is valid, including: the number
 * of the input,that should be 1 or 2; the type of the file
 * should be valid
 */ 
void parse_input(int argc, char* argv[], FILE* file_ptr)
{
        Pnmrdr_T *reader;

        if ( argc == 2 ) {
                file_ptr = fopen( argv[1], "rb" );
                if ( file_ptr == NULL ) {
                        runtime_error("File does not exist.");
                }
                NEW(reader);
                *reader = Pnmrdr_new( file_ptr );
        } else if( argc == 1 ) {
                NEW(reader);
                *reader = Pnmrdr_new( stdin );
        } else {
                runtime_error( "Wrong number of arguments." );
        }
        if ( Pnmrdr_data(*reader).type != 1 ){
                free_memory(file_ptr, reader, NULL, NULL);
                runtime_error( "Invalid file type." );
        }
        
        check_blackedges(reader, file_ptr);     
}



/* check and remove black edges and print the output to stdout 
 * Parameters: the pointer to the reader and pointer to the file
 */
void check_blackedges( Pnmrdr_T * reader, FILE * file_ptr)
{
        int width  = Pnmrdr_data( *reader ).width;
        int height = Pnmrdr_data( *reader ).height;
        int denominator = Pnmrdr_data( *reader ).denominator;

        if (denominator != 1){
                free_memory(file_ptr, reader, NULL, NULL);
                runtime_error("Not a valid portable bitmap. \n");
        }
        
        /* bitArray stores the original file */
        Bit2_T *bitArray;
        NEW(bitArray);
        *bitArray =  Bit2_new (width, height); 
        
        /* markedArray stores the black edges */
        Bit2_T *markedArray;
        NEW(markedArray);
        *markedArray = Bit2_new (width, height);
        
        /* read*/
        if (pbm_read(reader, bitArray, width, height) == true) {
                free_memory(file_ptr, reader, bitArray, markedArray);
                RAISE(Density_Failed);
        }
        
        /* write*/
        pbm_write(bitArray, markedArray);
        
        /* output */
        pbm_output(stdout, *bitArray);
        
        free_memory(file_ptr, reader, bitArray, markedArray);
}




/*---------------------------------------------------------------------------*
 *                                 READ                                      *
 *---------------------------------------------------------------------------* 
 */




/* Put bits from reader into the 2D array and check whether the density 
 * of each pixel is valid. 
 * Parameters: the reader, the 2D array, width, height
 * Return value: returns true if there is an error
 */
bool pbm_read(Pnmrdr_T *reader, Bit2_T *bitArray, int width, int height)
{
        int row, col;
        bool error = false;
        for (row = 0; row < height; row++){
                for(col = 0; col < width; col++){
                        int current_value = Pnmrdr_get( *reader );
                        if(current_value == 0 || current_value == 1){
                                Bit2_put(*bitArray, col, row, current_value);
                        }else{
                                error = true;
                        }
                }
        }

        return error;       
}




/*---------------------------------------------------------------------------*
 *                                 WRITE                                     *
 *---------------------------------------------------------------------------* 
 */




/* check edge bits and their neighbors and update the arrays
 * Parameters: pointers to bitArray and markedArray
 * Return value: none
 */
void pbm_write(Bit2_T *bitArray, Bit2_T *markedArray)
{
        check_edge(bitArray, markedArray);
        Bit2_map_row_major(*bitArray, check_bits, markedArray);
        Bit2_map_row_major(*bitArray, update_bits, markedArray);
}



/* check the edges and update the marked array
 * Parameters: the pointer to initial 2D array and
 * the pointer to the marked array
 */
void check_edge(Bit2_T *bitArray, Bit2_T *markedArray)
{
        int width = Bit2_width(*bitArray);
        int height = Bit2_height(*bitArray);
        int col, row;
        int currentEdge1, currentEdge2;
        
        /* mark the row edges */
        for(col = 0; col < width; col++ ){
                currentEdge1  = Bit2_get(*bitArray,col,0);
                currentEdge2 = Bit2_get(*bitArray,col,height-1);
                Bit2_put(*markedArray, col, 0, currentEdge1);
                Bit2_put(*markedArray, col, height-1, currentEdge2);
        }
        
        /* mark the col edges */
        for(row = 0; row < height; row++ ){
                currentEdge1  = Bit2_get(*bitArray, 0, row);
                currentEdge2 = Bit2_get(*bitArray, width-1, row);
                Bit2_put(*markedArray, 0, row, currentEdge1);
                Bit2_put(*markedArray, width-1, row, currentEdge2);
        }
}



/* Check the current value, if it is 1, then check its
 * neighbor
 * Parameters: col and row, the pointer to original array 
 * and the current value, and a pointer to the marked array
 */
void check_bits(int col, int row, Bit2_T a, int curr, void *p1)
{        
        (void)curr;
        int currentbit = Bit2_get(*(Bit2_T *)p1, col, row);
        
        if (currentbit == 1){
                check_neighbors(&a, (Bit2_T *)p1, col, row);
        }
}        



/* check the neighbors of the current bit for black edges
 * Parameters: a pointer to the original array,the pointer to the
 * marked array, col and row
 */
void check_neighbors(Bit2_T *bitArray, Bit2_T *markedArray, int col, int row)
{        
        Stack_T stk = Stack_new();
        coordinates colrow;
        colrow.col = col;
        colrow.row = row;
        
        Stack_push(stk, &colrow);

        while(Stack_empty(stk) != 1) {
                /* pop current col and row */ 
                colrow = *((coordinates *)Stack_pop(stk));
                
                int current = Bit2_get(*bitArray, colrow.col, colrow.row);
                
                if (current == 1) {
                        Bit2_put(*markedArray, colrow.col, 
                                 colrow.row, current);
                        
                        /* check neighbor bit is in range and not visited */
                        if (colrow.col + 1 < Bit2_width(*bitArray) && Bit2_get
                           (*markedArray, colrow.col+1, colrow.row) == 0) {
                                coordinates colrow1 = set_coordinate
                                (colrow.col + 1, colrow.row);
                                /* push next coordinates onto the stack */
                                Stack_push(stk, &colrow1);
                        }
                        if (colrow.col >= 1 && Bit2_get
                           (*markedArray, colrow.col-1, colrow.row) == 0 ) {
                                coordinates colrow2 = set_coordinate
                                (colrow.col - 1, colrow.row);
                                Stack_push(stk, &colrow2);
                        }
                        if (colrow.row + 1 < Bit2_height(*bitArray) && Bit2_get
                           (*markedArray, colrow.col, colrow.row+1) == 0) {
                                coordinates colrow3 = set_coordinate
                                (colrow.col, colrow.row + 1);
                                Stack_push(stk, &colrow3);
                        }
                        if (colrow.row >= 1 && Bit2_get
                           (*markedArray, colrow.col, colrow.row-1) == 0) {
                                coordinates colrow4 = set_coordinate
                                (colrow.col, colrow.row - 1);
                                Stack_push(stk, &colrow4);
                        }
                }
        }
        Stack_free(&stk);
}   



/* set new coordinates
 * Parameters: the col and row
 */
coordinates set_coordinate(int col, int row)
{
        coordinates colrow;
        colrow.col = col;
        colrow.row = row;
        return colrow;
}



/* Reomove marked array bits from the original bit array
 * Parameters: col and row, the pointer to the original
 * array, the current value and the pointer to the marked
 * array
 */
void update_bits(int col, int row, Bit2_T a, int curr, void *p1)
{
        (void)curr;
        int currentMarkedBit = Bit2_get(*(Bit2_T *)p1, col, row);
        if (currentMarkedBit == 1)
                Bit2_put(a, col, row, 0);
}




/*---------------------------------------------------------------------------*
 *                                OUTPUT                                     *
 *---------------------------------------------------------------------------* 
 */




/* print out the corrected pbm file as std output
 * Parameters: file pointer, the corrected 2D array
 */
void pbm_output(FILE *outputfp, Bit2_T bitmap)
{
        fprintf(outputfp, "P1\n");
        fprintf(outputfp, "# black edges have been removed\n");
        fprintf(outputfp, "%d %i\n", Bit2_width(bitmap), Bit2_height(bitmap));
        Bit2_map_row_major(bitmap, print_bits, NULL);
}



/* print the bits in the specific location in 2D array with
 * the given col and row each time
 * Parameters: col and row, the 2D array,the current value
 * and a void pointer 
 */ 
void print_bits(int col, int row, Bit2_T a, int curr, void *p1)
{
        (void)row;
        (void)p1;
        
        fprintf(stdout, "%d ", curr);
        /* last bit in row */
        if (col == Bit2_width(a) - 1)
                fprintf(stdout, "\n");
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
void free_memory(FILE * file_ptr, Pnmrdr_T * reader, 
                 Bit2_T * bitArray, Bit2_T * markedArray)
{
        if (file_ptr != NULL)
                fclose(file_ptr);
        
        if (reader != NULL) {
                Pnmrdr_free(reader);
                FREE(reader);
        }
        
        if (bitArray != NULL) {
                Bit2_free(bitArray);
                FREE(bitArray);
        }
        
        if (markedArray != NULL) {
                Bit2_free(markedArray);
                FREE(markedArray);
        }
}