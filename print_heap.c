/**
 * CSE374 Winter 2017
 * Homework 6 Memory Management
 * Josh(Jiashuo) Zhang 1365330
 * Ethan(Chiho) Kim 0963203 
 * Feb 20, 2017
 * Implementation of function print_heap
 * The function prints a formatted listing to a given file showing
 * the free blocks on free list. It shows the address and the length
 * of the block. Could add more describing features.
 */

#include <stdint.h>
#include <stdio.h>

#include "mem_impl.h"

// Prints the free blocks in a formatted listing to a give file
void print_heap(FILE* f) {
    FreeBlock* temp = freeList;
    // Free block number
    int num = 1;

    while (temp) {
        fprintf(f, "%p %6p %9p %3d\n",
               temp, (void*)temp->size, temp->next, num++);
        temp = temp->next;
    }
}
