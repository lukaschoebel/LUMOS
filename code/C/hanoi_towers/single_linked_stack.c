//  Created by Lukas Schöbel on 21.01.20.
//  Copyright (c) 2020 Lukas Schöbel. All rights reserved.


/**********************************
 * INCLUDES
 **********************************/

#include <stdlib.h>
#include <stdio.h>
#include "single_linked_stack.h"

/**********************************
 * DEFINES
 **********************************/

#define DEBUG 0

/**********************************
 * FUNCTIONS
 **********************************/


/**
 * new_stack
 *
 * Creates a new empty stack
 *
 *
 * @return new_List     new empty list
 ￼*/

struct Stack *new_stack(char *name)
{
    struct Stack *new_stack = (struct Stack*)malloc(sizeof(struct Stack));
    
    new_stack->name = name;
    new_stack->head = NULL;
    
    if (new_stack == NULL)
    {
        printf("Could not allocate memory!\n");
        exit(-1);
        return NULL;
    }
    
#if (DEBUG == 1)
    printf("[DEBUG] Created new stack %s @ %p!\n", name, new_stack);
#endif
    
    return new_stack;
}


/**
 * stack_size
 *
 * Returns the size of the stack
 *
 *
 * @param   the_stack   stack
 * @return  len         size of the stack
 ￼*/

unsigned int stack_size(struct Stack *the_stack)
{
    unsigned int len = 0;
    struct Node *tmp = the_stack->head;
    
    while (tmp)
    {
        len++;
        tmp = tmp->next;
    }
    
    return len;
}


/**
 * push_value
 *
 * Pushes a certain value into the stack
 *
 *
 * @param *the_stack     stack
 * @param value          value the user wants to insert in the stack
 ￼*/

void push_value(struct Stack *the_stack, int value)
{
    struct Node *tmp = (struct Node *)malloc(sizeof(struct Node));
    struct Node *cursor = the_stack->head;
    
    if (tmp == NULL)
    {
        printf("Could not allocate memory!\n");
        exit(-1);
    }
 
    tmp->data = value;
    tmp->next = NULL;
    
    if (cursor == NULL)
    {
        the_stack->head = tmp;
    }
    else
    {
        tmp->next = cursor;                     // set old head next to inserted node
        the_stack->head = tmp;                  // inserted node is new head
    }
    
#if (DEBUG == 1)
    printf("[DEBUG] Created new node @ %p with data %d!\n", tmp, value);
#endif
    
}


/**
 * push
 *
 * Pushes a certain value into the stack
 *
 *
 * @param *the_stack     stack
 * @param new_node       node the user wants to insert in the stack
 ￼*/

void push(struct Stack *the_stack, struct Node *new_node)
{
    struct Node *cursor = the_stack->head;
    
    if (new_node == NULL)
    {
        printf("Node cannot be allocated!\n");
        exit(-1);
    }
    
    new_node->next = NULL;
    
    if (cursor == NULL)                                 // empty list
    {
        the_stack->head = new_node;
    }
    else
    {
        new_node->next = cursor;                        // set old head next to inserted node
        the_stack->head = new_node;                     // inserted node is new head
    }
    
#if (DEBUG == 1)
    printf("[DEBUG] Pushes node into the stack @ %p!\n", new_node);
#endif
}


/**
 * pop
 *
 * Pops a certain value from the stack
 *
 *
 * @param *the_stack     stack
 * @return new_node      node the user wants to insert in the stack
 ￼*/

struct Node *pop(struct Stack *the_stack)
{
    struct Node *pop_node = the_stack->head;

    if (the_stack->head == NULL)                                 // case: empty list
    {
        pop_node = NULL;
    }
    else
    {
        // pop_node = the_stack->head;
        the_stack->head = pop_node->next;
    }
    
#if (DEBUG == 1)
    printf("[DEBUG] Pops node from the stack @ %p!\n", pop_node);
#endif
    
    return pop_node;
}


/**
 * clear_stack
 *
 * Frees all nodes but not the stack itself
 *
 *
 * @param the_stack     stack the user wants to clear
 ￼*/

void clear_stack(struct Stack *the_stack)
{
    struct Node *tmp = the_stack->head;
    
    while (tmp)
    {
        struct Node *cursor = tmp;
        tmp = cursor->next;
        
#if (DEBUG == 1)
        printf("[DEBUG] Deleted node @ %p!\n", cursor);
#endif
        
        free(cursor);
    }
    
    the_stack->head = NULL;
    free(tmp);
    return;
}


/**
 * print_stack
 *
 * Prints the stack
 *
 *
 * @param the_stack     stack the user wants to print
 ￼*/

void print_stack(struct Stack *the_stack)
{
    struct Node *tmp = the_stack->head;
    
    printf("--Top--\n");
    while (tmp != NULL)                                     // As long as the head ptr != NULL...
    {
        printf("%d\n", tmp->data);                          // ... print out the data of the list and...
        tmp = tmp->next;                                    // ... move to the next node
    }
    printf("--Bottom--\n");
}

