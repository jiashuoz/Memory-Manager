/**
 * CSE374 Winter 2017
 * Homework 6 Memory Management
 * Josh(Jiashuo) Zhang 1365330
 * Ethan(Chiho) Kim 0963203 
 * Feb 20, 2017
 * Implementation of function get_mem_stats
 * This function stores the statistics information about the current state of
 * the memory manager. The total amount of memory acquired in bytes, the amount 
 * of free memory available in bytes, and the amount of free blocks are stored.
 */

#include <stdint.h>
#include <stdio.h>

#include "mem_impl.h"

// Store the statics information of the memory manager
void get_mem_stats(uintptr_t* total_size,
                     uintptr_t* total_free, uintptr_t* n_free_blocks) {
    *total_size = totalSize;

    *total_free = 0;
    *n_free_blocks = 0;
    FreeBlock* temp = freeList;
    while (temp) {
        *total_free += temp->size;
        *n_free_blocks += 1;
        temp = temp->next;
    }
}
