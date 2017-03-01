/*      
 *      unblackedges.h
 *      Modified by: Arpan Gurung and Rui Qin
 *	Last Modified: 2/14/17
 *      Part D: Using the Bit2 abstraction to remove black edges
 *	Header file for unblackedges implementation
 *      
 */

#ifndef UNBLACKEDGES_H
#define UNBLACKEDGES_H

#include <setjmp.h> 
#include <except.h>
#include <stdio.h>
#include <stdlib.h>
#include <pnmrdr.h>
#include <assert.h>
#include <stdbool.h>
#include <mem.h>
#include <stack.h>
#include "bit2.h"


/* Exceptions */
static Except_T Density_Failed = { "Pixel density out of range" };


/* the struct used in stack to save the col and row
 * for the location of a single bit
 */
typedef struct coordinates {
	int col;
	int row;
}coordinates;


/* Functions */


/* check whether the input is valid, including: the number
 * of the input,that should be 1 or 2; the type of the file
 * should be valid
 */ 
void parse_input(int argc, char* argv[], FILE * file_ptr );


/* check and remove black edges and print the output to stdout 
 * Parameters: the pointer to the reader and pointer to the file
 */
void check_blackedges( Pnmrdr_T *reader, FILE * file_ptr);


/* Put bits from reader into the 2D array and check whether the density 
 * of each pixel is valid.
 */ 
bool pbm_read(Pnmrdr_T *reader, Bit2_T *pixel_array,
		   int width, int height);


/* check edge bits and their neighbors and update the arrays
 * Parameters: pointers to bitArray and markedArray
 */
void pbm_write(Bit2_T *bitArray, Bit2_T *markedArray);


/* print out the corrected pbm file as std output
 */
void pbm_output(FILE *outputfp, Bit2_T bitmap);


/* check the edges and update the marked array
 */
void check_edge(Bit2_T *bitArray, Bit2_T *markedArray);


/* Check the current value, if it is 1, then check its
 * neighbor
 */
void check_bits(int col, int row, Bit2_T a, int curr, void *p1);


/* Reomove marked array bits from the original bit array
 */
void update_bits(int col, int row, Bit2_T a, int curr, void *p1);


/* print the bits in the specific location in 2D array with
 * the given col and row each time
 */
void print_bits(int col, int row, Bit2_T a, int curr, void *p1);


/* check the neighbors of the current bit for black edges
 */
void check_neighbors(Bit2_T *bitArray, Bit2_T *markedArray, int col, int row);


/* set new coordinates
 */ 
coordinates set_coordinate(int col, int row);


/* free used memory
 */
void free_memory(FILE* file_ptr, Pnmrdr_T* reader, 
		 Bit2_T* bitArray, Bit2_T* markedArray);


/* runtime error function
 */
void runtime_error( char *error );


#endif /* UNBLACKEDGES_H */
