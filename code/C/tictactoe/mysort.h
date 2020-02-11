//  Created by Lukas Schöbel on 21.01.20.
//  Copyright (c) 2020 Lukas Schöbel. All rights reserved.


#ifndef MYSORT_H
#define MYSORT_H

/**********************************
 * INCLUDES
 **********************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**********************************
 * DECLARATIONS
 **********************************/

void merge (void *list_1, int list_1_length, void *list_2, int list_2_length,
            void *ret_arr, int objsize, int compfun(void *, void *));
void merge_sort(void *array, int arrlen, int objlen, unsigned int threshold, int compfun(void *, void *));
void swap(char *a, char *b, unsigned objsize);
void bubble_sort(void *array, int arrlen, int objlen, int compfun(void *, void *));
void sortArray(void *array, unsigned int objlen, unsigned int arrlen, unsigned int threshold,
               int compfun(void *, void *));

#endif /* MYSORT_H */
