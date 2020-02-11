//  Created by Lukas Schöbel on 21.01.20.
//  Copyright (c) 2020 Lukas Schöbel. All rights reserved.

#ifndef single_linked_stack_h
#define single_linked_stack_h

/**********************************
 * STRUCTS
 **********************************/

struct Node
{
    int data;
    struct Node *next;
};

struct Stack
{
    struct Node *head;
    char *name;
};

/**********************************
 * DEFINES
 **********************************/

struct Stack *new_stack(char *name);
unsigned int stack_size(struct Stack *the_stack);
void push_value(struct Stack *the_stack, int value);
void push(struct Stack *the_stack, struct Node *new_node);
struct Node *pop(struct Stack *the_stack);
void clear_stack(struct Stack *the_stack);
void print_stack(struct Stack *the_stack);

#endif /* single_linked_stack.h */
