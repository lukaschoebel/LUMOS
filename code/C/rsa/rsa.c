//  Created by Lukas Schöbel on 21.01.20.
//  Copyright (c) 2020 Lukas Schöbel. All rights reserved.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * square_mult
 * 
 * Square-Multiply-Algorithm to get result = base^exp % modulus
 *
 ￼￼￼￼￼* @param base     Base
 * @param exp      Exponent
 * @param modulus  Modulus
 * @return result
 ￼￼*/

unsigned int square_mult(unsigned int base, unsigned int exp, unsigned int modulus)
{
    unsigned long long int l_base = base;           // save the base as a long long int
    unsigned long long int result = 1;
    
    if (base == 0) {
        return 1;
    }
    else if (base == 1) {
        return (unsigned int)(l_base % (unsigned long long int)modulus);
    }
    
    while (exp > 0){
        if ((exp % 2) == 1)
        {
            result = (result * l_base) % (unsigned long long int)modulus;
        }
        
        exp /= 2;
        l_base = (l_base * l_base) % (unsigned long long int)modulus;

    }
    
    return (unsigned int)result;
}


/**
 * extendedEuclid
 *
 * Extended Euclidean Algorithm finds the multiplicative inverse of two co-prime numbers
 *
 ￼￼￼￼￼* @param e        base
 * @param phi_N    Modulus
 * @return d       d is multiplicative inverse (d = e^(-1) % phi_N
 ￼￼*/

unsigned int extendedEuclid(unsigned long int e, unsigned long long int phi_N)
{
    int long result = 1;
    unsigned long int x = 0;
    unsigned long int y = 1;
    unsigned long int v = 0;
    
    unsigned long int c = 0;                        // coeff of lin comb
    unsigned long int d = 0;                        // coeff of lin comb
    unsigned long int r = 0;                        // remainder
    unsigned long int quo = 0;                      // phi_N = e * quo + remainder
    
    unsigned long int i1 = e;
    unsigned long int i2 = phi_N;
    
    if (phi_N == 1)                                 // If phi_N = 1: 1 = e^-1 mod 1 --> e^-1 = 0 mod1
    {
        result = 0;
        return (unsigned int)result;
    }
    
    while (i1 > 1)
    {
        quo = i2 / i1;                              // because we use uint, we do not get floats!
        r = i2 % i1;                                // get the remainder
        c = x - quo * result;
        d = y - quo * v;
        
        x = result;                                 // swap the values for the next iteration
        y = v;
        result = c;
        v = d;
        i2 = i1;
        i1 = r;
        
    }
    
    if (result < 0)                                 // add v1 (phi_N) to negative results to get a positive inverse!
        result = result + phi_N;
    
    return (unsigned int)result;
}


/**
 * en_crypt
 *
 * Encrypts the given message with the Square and Multiply-Algorithm (s.a.)
 *
 ￼￼￼￼￼* @param message  converted Message
 * @param e        Exponent (public key)
 * @param N        Modulus
 * @return result  encrypted Message
 ￼￼*/

unsigned int en_crypt(unsigned int message, unsigned int e, unsigned int N)
{
    unsigned long long int result = 0;
    
    result = square_mult(message, e, N);
    
    return (unsigned int)result;
}


/**
 * decrypt
 *
 * Decrypts the given message with the Square and Multiply-Algorithm (s.a.)
 *
 ￼￼￼￼￼* @param message  converted Message
 * @param e        Exponent (private key)
 * @param N        Modulus
 * @return result  decrypted Message
 ￼￼*/

unsigned int decrypt(unsigned int message, unsigned int d, unsigned int N)
{
    unsigned long long int result = 0;
    
    result = square_mult(message, d, N);
    
    return (unsigned int)result;
}


/**
 * crypt_Union
 *
 * Define union crypt_Union
 *
 ￼￼￼￼￼* @param message          char array to save letters (strings)
 * @param rsa_numbers      int array to save numbers
 ￼￼*/

union crypt_Union
{
    char message[1024];
    unsigned int rsa_numbers[256];
} crypt_text;


int main(int argc, const char * argv[])
{
    unsigned int p = 0;
    unsigned int q = 0;
    unsigned long int phi_N = 0;
    unsigned int d = 0;
    unsigned int N = 0;
    unsigned int e = 0;
    char ask_user = {0};
    int i = 0;
    union crypt_Union crypt_text;
    
    printf("Enter N: ");
    scanf(" %u", &N);
    
    printf("Enter e: ");
    scanf(" %u", &e);
    
    printf("Encrypt or Decrypt [e/d]? ");
    fflush(stdout);
    scanf(" %c", &ask_user);
    getchar();
    
    while ((ask_user != 'e') && (ask_user != 'd'))
    {
        printf("Encrypt or Decrypt [e/d]? ");
        fflush(stdout);
        scanf(" %c", &ask_user);
        getchar();
    }
    
    memset(crypt_text.rsa_numbers, 0, 256);             // initialize with 0
    
    switch (ask_user)
    {
        
        case 'e':
            
            printf("Enter Message: ");
            fgets(crypt_text.message, 1025, stdin);
            
            while (crypt_text.message[i] != '\n') {                     // iterate through the string
                i++;
            }
            crypt_text.message[i] = '\0';                               // add a null character at the end
            int counter = i/4;                                          // save the amount of letters in the entered message
            i = 0;
         
            printf("Encrypted Message is: ");                           // Encrypt it!
            for (i = 0; i < counter + 1; i++) {
                printf("%u", en_crypt(crypt_text.rsa_numbers[i], e, N));
                printf(" ");
            }
            
            printf("\n");
            break;
            
            
        case 'd':

            printf("Enter d: ");
            fflush(stdout);
            scanf(" %u", &d);
            
            if (d == 0)                                                 // If d = 0
            {
                printf("Enter p: ");                                    // Enter p and...
                scanf(" %u", &p);
                getchar();
                
                printf("Enter q: ");                                    // ... q in order to ...
                scanf(" %u", &q);
                getchar();
                
                N = p * q;
                phi_N = (p-1) * (q-1);
                d = extendedEuclid(e, phi_N);                           // ... d with the extended euclidean Algorithm
                printf("Calculated d is: %u\n", d);                    // Print d!
            }
            
            i = 0;
            while (1)                                                   // get Chipherblocks!
            {
                printf("Enter next Cipherblock: ");
                fflush(stdout);
                scanf("%u", &crypt_text.rsa_numbers[i]);
                getchar();
                
                if (crypt_text.rsa_numbers[i] == 0)                     // if entered cipherblock is equal to 0 --> STOP
                    break;
                
                crypt_text.rsa_numbers[i] = decrypt(crypt_text.rsa_numbers[i], d, N);
                i++;
            }

            printf("Decrypted Message is: ");                           // print the decrypted string.
            printf("%s", crypt_text.message);
            printf("\n");
            
            break;
            
        default:
            break;
    }
    
    return 0;
}
