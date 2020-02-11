//  Created by Lukas Schöbel on 21.01.20.
//  Copyright (c) 2020 Lukas Schöbel. All rights reserved.


/**********************************
 * INCLUDES
 **********************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "single_linked_stack.h"
#include <ctype.h>

/**********************************
 * FUNCTIONS
 **********************************/


/**
 * digit_control
 *
 * controls the start and end digits and prints out a error message if necessary
 *
 *
 * @param   digit           digit as string
 *
 */

void digit_control(char *digit)
{
    unsigned int i = 0;
    
    // if 1st letter != "+"/"-"/"0-9" -> exit and return -2
    if (((*(digit+0) != 43) || (*(digit+0) != 45)) && (*(digit+0) < 48) && (*(digit+0) > 57))
    {
        printf("USAGE: range_start and range_end must be integer values.\n");
        exit(-2);
    }
    
    for (i = 1; *(digit+i) != '\0'; i++)
    {
        if (isdigit(*(digit+i)) != 1)
        {
            printf("USAGE: range_start and range_end must be integer values.\n");
            exit(-2);
        }
        else
            ;
    }
    
}


/**
 * range_control
 *
 * controls the range and prints out a error message if necessary
 *
 *
 * @param   range_start
 * @param   range_end
 * @return  num_discs/error
 ￼*/

unsigned int range_control(int range_start, int range_end)
{
    if (range_start == range_end)
    {
        return 1;
    }
    
    if (range_start > range_end)
    {
        printf("RANGE ERROR: A positive non-zero number of disks is required.\n");
        exit(-3);
    }
    else
    {
        return (range_end - range_start) + 1;
    }
}


/**
 * move
 *
 * solves the tower of hanoi with the given discs on the three given stacks
 *
 *
 * @param   num_discs       number of discs
 * @param   source          source stack "Alice"
 * @param   destination     destionation stack "Bob"
 * @param   intermediate    intermediate stack "Carol"
 ￼*/

void move(int num_discs, struct Stack *source, struct Stack *destination, struct Stack *intermediate)
{
    if (num_discs == 1)
    {
        printf("Move ==> %d from %s to %s\n", source->head->data, source->name, destination->name);
        push(destination, pop(source));
    }
    else
    {
        move(num_discs - 1, source, intermediate, destination);
        push(destination, pop(source));
        printf("Move ==> %d from %s to %s\n", destination->head->data, source->name, destination->name);
        move(num_discs - 1, intermediate, destination, source);
    }
}

/**********************************
 * MAIN
 **********************************/

int main(int argc, char **argv) {
    
    if (argc != 6)
    {
        printf("USAGE: run_towers range_start range_end tower1_name tower2_name tower3_name\n");
        return -1;
    }
    
    int range_start = atoi(*(argv+1));                              // range_start
    int range_end = atoi(*(argv+2));                                // range_end
    struct Stack *source = new_stack(*(argv+3));                    // creates 'Alice'
    struct Stack *intermediate = new_stack(*(argv+4));       		// creates 'Bob'
    struct Stack *destination = new_stack(*(argv+5));       		// creates 'Carol'


    digit_control(*(argv+1));           // control if range_start is an integer value
    digit_control(*(argv+2));           // control if range_end is an integer value
    unsigned int num_discs = range_control(range_start, range_end);

    while (range_end >= range_start)    // pushes the values (range_start - range_end) into the source stack
    {
        push_value(source, range_end);
        range_end--;
    }

    printf("\n***** BEFORE SOLVING *****\n\n");
    printf("Tower %s\n", *(argv+3));
    print_stack(source);
    printf("\nTower %s\n", *(argv+4));
    print_stack(intermediate);
    printf("\nTower %s\n", *(argv+5));
    print_stack(destination);
    
    printf("\n***** SOLVING PUZZLE *****\n\n");
    move(num_discs, source, destination, intermediate);
    
    printf("\n***** AFTER SOLVING *****\n\n");
    printf("Tower %s\n", source->name);
    print_stack(source);
    printf("\nTower %s\n", intermediate->name);
    print_stack(intermediate);
    printf("\nTower %s\n", destination->name);
    print_stack(destination);


	clear_stack(destination);           // frees every element in the destination stack
	free(source);                       // frees the whole stack source
	free(intermediate);                 // frees the whole stack intermediate
	free(destination);                  // frees the whole stack destination


    return 0;
}
