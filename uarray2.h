/*      uarray2.h
 *      by Arpan Gurung and Rui Qin, 2/6/17
 *      Two-Dimensional, Polymorphic, Unboxed Arrays
 *      
 *      header file for the abstract data structure implementation
 *      uarray2. Designed to creat a 1D array to simulate a 2D array
 *      to save the data.
 */

#include <uarray.h>

#ifndef UARRAY2_INCLUDED
#define UARRAY2_INCLUDED

#define T UArray2_T
typedef struct T *T;


extern T    UArray2_new   (int width, int height, int size);
/* Creat a 2D array with the given width and height */


extern void UArray2_free  (T *uarray2);
/* free the memory */

extern int UArray2_width (T  uarray2);
/* return the width of the simulated 2D array */

extern int UArray2_height(T  uarray2);
/* return the height of the simulated 2D array */

extern int UArray2_size  (T  uarray2);
/* return the size of the value */

extern void *UArray2_at    (T  uarray2, int col, int row);
/* return the void pointer points to the value in the 
   specific position with the given row and col in uarray2 */

extern void UArray2_map_row_major(T uarray2, void apply(int col, int row,
                           UArray2_T a, void *p1, void *p2),void *cl);
/* calls an apply function for each element in the array. 
   Column indices vary more rapidly than row indices.*/


extern void UArray2_map_col_major(T uarray2, void apply(int col, int row,
                           UArray2_T a, void *p1, void *p2),void *cl);
/* calls an apply function for each element in the array. 
   Row indices vary more rapidly than column indices. */


#undef T
#endif

