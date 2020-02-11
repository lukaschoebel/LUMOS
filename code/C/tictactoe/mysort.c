//  Created by Lukas Schöbel on 21.01.20.
//  Copyright (c) 2020 Lukas Schöbel. All rights reserved.

/**********************************
 * INCLUDES
 **********************************/

#include "mysort.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**********************************
 * DEFINES
 **********************************/

#define DEBUG 0

/**********************************
 * FUNCTIONS
 **********************************/

/**
 * merge
 *
 * This function will merge two lists in order to get one array that will be returned in ret_arra
 *
 * @param list1         list1
 * @param list2         list2
 * @param list_1_length length of list1
 * @param list_2_length length of list2
 * @param ret_arr       merged list
 * @param objlen        length of one object in bytes
 * @return void
 */

void merge (void *list_1, int list_1_length, void *list_2, int list_2_length, void *ret_arr,
            int objlen, int compfun(void *, void *))
{
    int i = 0;      // counter for list_1
    int j = 0;      // counter for list_2
    int k = 0;      // counter for ret_arr
    
    while (i < list_1_length && j < list_2_length)
    {
        if (compfun((list_1+i*objlen), (list_2+j*objlen)) == 1) // copy list_1 to ret_array and move counter i
        {
            // move the i-th element of list_1 to the k-th position on the ret_arr
            memcpy(ret_arr+k*objlen, (char*)list_1+i*objlen, objlen);
            i++;
        }
        else
        {
            // move the j-th element of list_2 to the k-th position on the ret_arr
            memcpy(ret_arr+k*objlen, (char*)list_2+j*objlen, objlen);
            j++;
        }
        k++;                                        // move counter k
    }
    
    while (i < list_1_length)
    {
        // if i is less than list_1 --> copy elements to ret_arr
        memcpy(ret_arr+k*objlen, (char*)list_1+i*objlen, objlen);
        i++;
        k++;
    }
    
    while (j < list_2_length)
    {
        // if j is less than list_2 --> copy elements to ret_arr
        memcpy(ret_arr+k*objlen, (char*)list_2+j*objlen, objlen);
        j++;
        k++;
    }
}


/**
 * mergesort
 *
 * Recursive function to merge two lists through divide and conquer. A call to mergesort
 * will divide the input string into two and call mergesort on each of those until the base
 * case (empty list or list of size 1) is hit. Always returns with the list it is called on
 * in sorted order in place in the string (by reference).
 *
 * @param array         pointer to a generic array
 * @param arrlen        length of the string to sort
 * @param objlen        length of one object in bytes
 * @param threshold     parameter to make the sorting algorithm more efficient
 * @return void
 */

void merge_sort(void *array, int arrlen, int objlen, unsigned int threshold, int compfun(void *, void *))
{
    if (arrlen < 2)        // if list_length is less than 2 --> array is sorted
        return;
    
    // define a counter
    int counter = 0;
    
    // divide array into two arrays list1 and list2
    int list_1_length = arrlen / 2;                // divide the list into parts
    int list_2_length = arrlen - list_1_length;    // list_2_length
    
    // Allocate memory for two temporary lists
    void *list1 = (void*)malloc(objlen * list_1_length);
    void *list2 = (void*)malloc(objlen * list_2_length);
    
    if (list1 == NULL || list2 == NULL)
    {
        printf("[ERROR] Could not allocate memory!\n");
        exit(-1);
    }
    
    if (list_1_length < list_2_length)             // set counter to the lowest array value
        counter = list_1_length;
    else
        counter = list_2_length;
    
#if (DEBUG == 1)
    printf("\nlist1: %d - ", list_1_length);
    printf("list2: %d\n", list_2_length);
    printf("counter: %d\n", counter);
#endif
    
    memmove(list1, array, list_1_length*objlen);
#if (DEBUG == 1)
    printf("l1:");
    if(objsize == sizeof(int)) print_arr(list1, list_1_length, 3);
    else print_char(list1, list_1_length, 3);
#endif
    
    memmove(list2, (char*)array+(list_1_length*objlen), list_2_length*objlen);
#if (DEBUG == 1)
    printf("l2:");
    if(objsize == sizeof(int)) print_arr(list2, list_2_length, 3);
    else print_char(list2, list_2_length, 3);
#endif
    
    // if the length of the lists are less or equal than threshold --> use bubblesort
    if (counter > threshold)
    {
        // *********************************************
        // BEGIN RECURSION
        // *********************************************
        // Get sorted version of first half (recursively)
        merge_sort(list1, list_1_length, objlen, threshold, compfun);
        // Get sorted version of first half (recursively)
        merge_sort(list2, list_2_length, objlen, threshold, compfun);
        // *********************************************
        // END RECURSION
        // *********************************************
        
    }
    else if (counter <= threshold){            // if the length of the list are greater than threshold --> use mergesort
        bubble_sort(list1, list_1_length, objlen, compfun);
        bubble_sort(list2, list_2_length, objlen, compfun);
    }
    
    // MERGE RETURNED LISTS
    merge(list1, list_1_length, list2, list_2_length, array, objlen, compfun);
    
    // free the temporary lists
    free(list1);
    free(list2);
}


/**
 * swap
 *
 * This function will swap to elements a and b
 *
 * @param a             pointer to element a
 * @param b             pointer to element b
 * @param objlen        length of one object in bytes
 * @return void
 */

void swap(char *a, char *b, unsigned objlen)
{
    char tmp;
    
    if (a != b) {               // as long as a is not equal to b...
        while (objlen) {       // and objsize != 0, continue this loop:
            tmp = *a;           // set tmp to the value of a...
            *a++ = *b;          // a++ to b...
            *b++ = tmp;         // and b++ equal to tmp.
            objlen--;          // increment the objsize
        }
    }
}

/**
 * bubble_sort
 *
 * Following the bubble sort algorithm, this function will sort a generic array
 *
 * @param array         pointer to a generic array
 * @param arrlen        length of the string to sort
 * @param objlen        length of one object in bytes
 * @return void
 */

void bubble_sort(void *array, int arrlen, int objlen, int compfun(void *, void *))
{
    if (arrlen == 0 || arrlen == 1)     // array is sorted
        return;
    
    // define two counters
    int i = 0;
    int j = 0;
    
    for (i = 0; i < arrlen; i++)
    {
        for (j = 0; j < arrlen - i - 1; j++)
        {
            if (compfun((array+j*objlen), (array+(j+1)*objlen)) == 0)  // compare two elements, if 0 --> swap
            {
                void *a = (char*)array + j*objlen;        // cast the j-th element of the array into a void pointer
                void *b = (char*)array+(j+1)*objlen;      // cast the (j+1)-th element of the array into a void pointer
                swap((char*)a, (char*)b, objlen);         // swap those elements: j <-> j+1
            }
        }
    }
}


/**
 * Higher level sorting function that gets an array of objects as input
 * and applies a sorting function on the array using a custom comperator. *
 *
 * @param array         Pointer to an array of objects.
 * @param objlen        Length of one object in bytes.
 * @param arrlen        Number of objects in the array.
 * @param threshold     Number of max elements for which Bubblesort should be used.
 * @param compfun       Callback used to compare two values.
 * @return              This function does not return anything.
 *
 */

void sortArray(void *array, unsigned int objlen, unsigned int arrlen, unsigned int threshold,
               int compfun(void *, void *))
{
    if (arrlen == 0 || array == NULL)       // case: empty array
        return;
    
    if (arrlen < 2 && arrlen != 0)          // case: array is sorted
        return;
    
    if (objlen == 0)                        // error
    {
        printf("[ERROR] Objlen in bytes cannot be 0\n");
        exit(-1);
    }
    
    if (arrlen <= threshold)
        bubble_sort(array, arrlen, objlen, compfun);
    
    merge_sort(array, arrlen, objlen, threshold, compfun);
    return;
    
}


int main()
{
//    int arr[alen] = {-9, -5, -6, 2, 3, 5, -1, 0, 7, -8, 4};
//    long long int arr2[] = {-12121212121212, 44223523243423423, 123441121212, 12123123323221321, 8584757469756};
//    char arr3[] = {"qwertzuiopasdfghjklyxcvbnmmnbvcxylkjhgfdsapoiuztrewq"};
//    
//    // int array
//    print_arr(arr, alen, 0);
//    sortArray(arr, sizeof(int), 10, 5, compare);
//    print_arr(arr, alen, 1);
//    
//    // long long array
//    print_lld(arr2, 5, 0);
//    sortArray(arr2, sizeof(long long int), 5, 5, compare);
//    print_lld(arr2, 5, 1);
//    
//    // char array
//    print_char(arr3, (int)strlen(arr3), 0);
//    sortArray(arr3, sizeof(char), (int)strlen(arr3), 10, compare);
//    print_char(arr3, (int)strlen(arr3), 1);
    return 0;
}
