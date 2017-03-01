/*
 *      bit2.c
 *      by Arpan Gurung and Rui Qin, 2/6/17
 *      Two-Dimensional Arrays of Bits
 *      
 *   
 */

#include <stdio.h>
#include <stdlib.h>

#include "assert.h"
#include "mem.h"
#include "bit.h"
#include "bit2.h"

#define T Bit2_T

/* the struct contains the width and the height of the
   2D array. Also, a pointer points to that array */
struct T {
        int width;
        int height;
        Bit_T elems;
        
};

/* Creat a 2D bit array with the given width and height */
T Bit2_new(int width, int height)
{
        
        T bit2;
        NEW(bit2);
        
        Bit_T k = Bit_new(width*height);
        bit2->elems = k;
        bit2->width = width;
        bit2->height = height;
        return bit2;
}



/* free the memory */
void Bit2_free(T *bit2)
{
        assert(bit2 && *bit2);
        Bit_free((&(*bit2)->elems));
        FREE((*bit2)->elems);
        FREE(*bit2);
}

/* return the width of the simulated 2D array */
int Bit2_width(T bit2)
{
        assert(bit2);
        return bit2->width;
}


/* return the height of the simulated 2D array */
int Bit2_height(T bit2)
{
        assert(bit2);
        return bit2->height;         
}

/* return the bit in given location of our simulated 2D
   array bit2 */
int  Bit2_get(T bit2, int col, int row)
{
        int value;
        assert(bit2 != NULL);
        assert((row >= 0 && row < bit2->height) && 
               (col >= 0 && col < bit2->width));
        
        value = Bit_get(bit2->elems, row * bit2->width + col); 
        return value;
}

/* put the bit in given location of our simulated 2D
   array bit2, and return the previous bit in that location */
int Bit2_put(T bit2, int col, int row, int bit)
{
        int value;
        assert(bit2 != NULL);
        assert((row >= 0 && row < bit2->height) && 
               (col >= 0 && col < bit2->width));
        
        value = Bit_put(bit2->elems, row * bit2->width + col, bit); 
        return value;
}

/* calls an apply function for each element in the array. 
   Column indices vary more rapidly than row indices */
void Bit2_map_row_major(T bit2, void apply(int col, int row, 
                        Bit2_T a, int curr, void *p1),void *cl)
{
        int row, col, curr;

        assert(bit2 != NULL);
        assert(apply);
        for (row = 0; row < bit2->height; row++) {
                for(col = 0; col < bit2->width; col++) {
                        curr = Bit2_get(bit2, col, row);
                        apply(col, row, bit2, curr, cl);
                }
        }
}


/* calls an apply function for each element in the array. 
   Row indices vary more rapidly than column indices. */
void Bit2_map_col_major(T bit2, void apply(int col, int row,
                        Bit2_T a, int curr, void *p1),void *cl)
{
        int row, col, curr;
        assert(bit2 != NULL);
        assert(apply);
        for (col = 0; col < bit2->width; col++) {
                for(row = 0; row < bit2->height; row++) {
                        curr = Bit2_get(bit2, col, row);
                        apply(col, row, bit2, curr, cl);
                }
        }
        
}








