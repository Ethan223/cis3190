/*************************************************
Name: Ethan Coles
ID: 0843081
File: sieve.c
Description: CIS*3190 Assignment 4, C implentation
of Sieve of Eratosthenes algorithm.
*************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*Initializes array of integers from 2 to the upper limit.*/
int* populatePrimes(int* prime, int upperLim) {
    int i;

    for(i=0; i<upperLim; i++)
        prime[i] = i+2;

    return prime;
}

/*Prints out the prime numbers to an ASCII file.
Any remaining numbers in the prime array that are not 0 are written.*/
void printPrimes(FILE* fp, int* prime, int length) {
    int i;

    for(i=0; i<length; i++) {
        if(prime[i] != 0)
            fprintf(fp, "%d\n", prime[i]);
    }
}

int main(int argc, char *argv[]) {
    FILE* fp;        /*File pointer*/
    int* prime;      /*Array containing prime numbers*/
    int limit, i, j; /*Upper limit of prime numbers to output*/
    char buffer[80]; /*Input buffer*/

    printf("Enter a limit: ");
    fgets(buffer, 80, stdin);

    i = 0; /*Verify input is a number*/
    while(buffer[i] != '\n') {
        if(!isdigit(buffer[i])) {
            fprintf(stderr, "Error: Not a decimal value\n");
            return -1;
        }

        i++;
    }

    limit = atoi(buffer);
    limit -= 1; /*1 less array element because starting at 2*/

    prime = malloc(sizeof(int)*limit);
    prime = populatePrimes(prime, limit);

    for(i=0; i<limit; i++) { /*Main algorithm for Sieve of Eratosthenes*/
        if(prime[i] != 0) {
            for(j=i+1; j<limit; j++) {
                if(prime[j]%prime[i] == 0)
                    prime[j] = 0;
            }
        }
    }

    fp = fopen("primeNumbers.txt", "w"); /*Write to file*/
    if(fp == NULL) {
        fprintf(stderr, "Error opening file.\n");
        free(prime);
    }

    printPrimes(fp, prime, limit);
    fclose(fp);

    free(prime);    
    return 0;
}