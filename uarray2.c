/*      
 *      uarray2.c
 *      by Arpan Gurung and Rui Qin, 2/6/17
 *      Two-Dimensional, Polymorphic, Unboxed Arrays
 *      
 */

#include <stdio.h>
#include <stdlib.h>

#include "assert.h"
#include "mem.h"
#include "uarray2.h"
#include "uarray.h"

#define T UArray2_T

/* the struct contains the width and the height of the
   2D array. Also, a pointer points to that array*/
struct T {
        int width;
        int height;
        UArray_T elems;
        
};

/* Creat a 2D array with the given width and height */
T UArray2_new(int width, int height, int size)
{
        T uarray2;
        NEW(uarray2);
        
        UArray_T new_array = UArray_new(width*height, size);
        uarray2->elems = new_array;
        uarray2->width = width;
        uarray2->height = height;
        
        return uarray2;
}

/* free the memory */
void UArray2_free(T *uarray2)
{
        assert(uarray2 != NULL && *uarray2 != NULL);
        
        UArray_free((&(*uarray2)->elems));
        FREE((*uarray2)->elems);
        FREE(*uarray2);
} 


/* return the void pointer points to the value in the 
   specific position with the given row and col in uarray2 */
void *UArray2_at(T uarray2, int col, int row)
{
        assert(uarray2 != NULL);
        assert((row >= 0 && row < uarray2->height) && 
              (col >= 0 && col < uarray2->width));
        return UArray_at(uarray2->elems, row * uarray2->width + col);
}


/* return the width of the simulated 2D array */
int UArray2_width (T  uarray2)
{
        assert(uarray2 != NULL);
        return uarray2->width;
        
}

/* return the height of the simulated 2D array */
int UArray2_height(T  uarray2)
{
        assert(uarray2 != NULL);
        return uarray2->height;        
}

/* return the size of the value */
int UArray2_size  (T  uarray2)
{
        assert(uarray2 != NULL);
        return UArray_size(uarray2->elems);
} 


/* calls an apply function for each element in the array. 
   Column indices vary more rapidly than row indices.*/
void UArray2_map_row_major(T uarray2, void apply(int col, int row, 
                           UArray2_T a, void *p1, void *p2),void *cl)
{
        int row, col;
        assert(uarray2 != NULL);
        assert(apply);
        for (row = 0; row < uarray2->height; row++) {
                for(col = 0; col < uarray2->width; col++) {
                        void *p1 = UArray2_at(uarray2, col, row);
                        apply(col,row,uarray2,p1,cl);
                }
        }        
}

/* calls an apply function for each element in the array. 
   Row indices vary more rapidly than column indices. */
void UArray2_map_col_major(T uarray2, void apply(int col, int row,
                           UArray2_T a, void *p1, void *p2),void *cl)
{
        int row, col;
        assert(uarray2 !=NULL );
        assert(apply);
        for (col = 0; col < uarray2->width; col++) {
                for(row = 0; row < uarray2->height; row++) {
                        void *p1 = UArray2_at(uarray2,col,row );
                        apply(col,row,uarray2,p1,cl);
                }
        }
}





