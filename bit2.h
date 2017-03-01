/*
 *      bit2.h
 *      by Arpan Gurung and Rui Qin, 2/6/17
 *      Two-Dimensional Arrays of Bits
 *      
 *      header file for the abstract data structure implementation
 *      bit2. Designed to create a 1D array to simulate a 2D array
 *      to save the bits
 */



#include <uarray.h>

#ifndef BIT2_INCLUDED
#define BIT2_INCLUDED

#define T Bit2_T
typedef struct T *T;



extern T     Bit2_new   (int width, int height);
/* Creat a 2D bit array with the given width and height */

extern void  Bit2_free  (T *bit2);
/* free the memory */

extern int   Bit2_width (T  bit2);
/* return the width of the simulated 2D array */

extern int   Bit2_height(T  bit2);
/* return the height of the simulated 2D array */

extern int  Bit2_get(T bit2, int col, int row);
/* return the bit in given location of our simulated 2D
   array bit2 */

extern int  Bit2_put(T bit2, int col, int row, int bit);
/* put the bit in given location of our simulated 2D
   array bit2, and return the previous bit in that location */

extern void Bit2_map_row_major(T bit2, void apply(int col, int row, Bit2_T a,
                                int curr, void *p1),void *cl);
/* calls an apply function for each element in the array. 
   Column indices vary more rapidly than row indices.*/

extern void Bit2_map_col_major(T bit2, void apply(int col, int row, 
                        Bit2_T a, int curr, void *p1),void *cl);
/* calls an apply function for each element in the array. 
   Row indices vary more rapidly than column indices. */


#undef T
#endif
