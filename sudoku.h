/*      
 *      sudoku.h
 *      Modified by: Arpan Gurung and Rui Qin
 * 	Last modified: 2/14/17
 *      Using the UArray2 abstraction to identify Sudoku solutions
 *      Header file for the sudoku implementation
 */

#ifndef SUDOKU_H
#define SUDOKU_H

#include <setjmp.h> 
#include <stdio.h>
#include <stdlib.h>
#include <pnmrdr.h>
#include <assert.h>
#include <stdbool.h>
#include <mem.h>
#include "uarray2.h"

#define SUDOKU_WIDTH 9
#define SUDOKU_HEIGHT 9 

typedef long number;
const int ELEMENT_SIZE = sizeof(number);



/* Functions */


/* check whether the input is valid: number of inputs, type of file */
void parse_input(int argc, char* argv[], FILE* file_ptr );


/* Check if it is a sovled sudoku by checking: the height and 
 * the width, the density of each pixel, repitition */
void check_sudoku( Pnmrdr_T *reader, FILE * file_ptr);


/* Divide the whole sudoku into 9 3 * 3 blocks and check each element*/
void check_blocks(UArray2_T pixelArray, bool *blockArray);


/* Go through each element of 3 * 3 block and check for repitition */
void check_blockelements(int row, int col,UArray2_T pixelArray, 
                                                  bool *blockArray);

/*apply function to check wether each column of the 2D array is valid that
 * is no repetition */
void check_rows(int col, int row, UArray2_T a, void *curr, void *p);


/* apply function to check wether each row of the 2D array is valid that is
 * no repetition */
void check_cols(int col, int row, UArray2_T a, void *curr, void *p);


/* Put pixels from reader into the 2d array and check whether the density 
 * of each pixel is valid. */
bool sudoku_read(Pnmrdr_T *reader, UArray2_T *pixelArray,
                                       int width, int height);


/* Check to see if pixelArray is a valid sudoku solution */
void sudoku_check(Pnmrdr_T *reader, FILE * file_ptr, UArray2_T *pixelArray);


/* runtime error function */
void runtime_error( char *error );


/* free used memory */
void free_memory(FILE * file_ptr, Pnmrdr_T * reader, UArray2_T * pixelArray);


#endif /* SUDOKU_H */