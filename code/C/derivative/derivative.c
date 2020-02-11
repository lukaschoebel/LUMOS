
//  Created by Lukas Schöbel on 21.01.20.
//  Copyright (c) 2020 Lukas Schöbel. All rights reserved.


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/**********************************
 * DEFINES
 **********************************/

#define DEBUG 1
#define size 50

/**********************************
 * FUNCTIONS
 **********************************/

/**
 * print_help
 *
 * Print a help message.
 * @param   nothin
 * @return  nothin
 */

void print_help(void)
{
    printf("\nHELP\n");
    printf("----\n");
    printf("I am here in order to helb you with derivates of functions ");
    printf("Example: With the input 'x^2', I would compute '2x'\n\n");
    printf("Further options:\n");
    printf("\t'q' - shut me down\n");
    printf("\t'h' - print this message\n\n");
}

/**
 * find_factor
 *
 * find the factor of a given faction and return it
 *
 * @param   function
 * @return  factor of a function
 */

long int find_factor(char *function)
{
    char k[size] = {0};
    char *ptr;
    ptr = (char*)memchr(function, 'x', strlen(function));
    
    if (!strncmp(function, "x", 1))                             // f(x) = x --> k = 1;
        strncpy(k, "1", 1);
        
    if (ptr!=NULL)                                              // function with x
        strncpy(k, function, ptr-function);
    else                                                        // function without x
        strncpy(k, function, strlen(function));

    k[strlen(k)] = '\0';                                        // add null character at the end

#if (DEBUG == 1)
    printf("[DEBUG] The factor of the function f(x) = %s is %ld!\n", function, atol(k));
#endif
    
    return atol(k);
}

/**
 * find_exp
 *
 * find the factor of a given faction and return it
 *
 * @param   function
 * @return  exponent of a function
 */

long int find_exp(char *function)
{
    char p[size] = {0};
    char *ptr;
    ptr = (char*)memchr(function, 'x', strlen(function));
    
    printf("%s\n", ptr);
    
    if (!strncmp(function, "x", 1))                             // f(x) = x --> p = 1;
        strncpy(p, "1", 1);
    
    if (ptr != NULL && (function + (ptr-function+1)) == '\0')   // function with x
        strncpy(p, "1", 1);
//        strncpy(p, function, ptr-function);
    else                                                        // function without x
        strncpy(p, function, strlen(function));
    
    p[strlen(p)] = '\0';                                        // add null character at the end
    
#if (DEBUG == 1)
    printf("[DEBUG] The exponent of the function f(x) = %s is %ld!\n", function, atol(p));
#endif
    
    return atol(p);
}

/**
 * take_derivative
 *
 * Take the derivative of a given function
 *
 * @param   function
 * @return  derivative of the function
 */

char *take_derivative(char *function)
{
    char *derivative = (char *)malloc(sizeof(char) * size);
    long int k = 0;
    long int p = 0;
    
    find_factor(function);
    
//    k = find_factor(function) * find_exp(function);     // new factor
//    p = find_exp(function) - 1;                         // nex exponent
    
    return derivative;
}

int main(int argc, const char * argv[]) {
    
    char *str_fct = (char *)malloc(sizeof(char) * size);

    
    printf("Hello! I am here to take derivatives!\n");
    printf("\tFor more wisdom enter 'h'!\n");
    printf("=====================================\n");

    
    while (1)
    {
        printf("\n");
        printf("==>CALC:  f(x) = ");
        scanf("%s", str_fct);
        
        if (!strncmp(str_fct, "h", 1))
            print_help();
        
        if (!strncmp(str_fct, "q", 1))
            break;

        printf("==>ANS:   f'(x) = %s", take_derivative(str_fct));
        
    }
    
    free(str_fct);
    
    return 0;
    
}
