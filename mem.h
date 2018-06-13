/**
 * CSE374 Winter 2017
 * Homework 6 Memory Management
 * Josh(Jiashuo) Zhang 1365330
 * Ethan(Chiho) Kim 0963203 
 * Feb 20, 2017
 * Header file for public functions in memory manager.
 * Client interface to be used.
 */

#ifndef MEM_H
#define MEM_H

// Return pointer to a memory block with at least size of user request size
void* getmem(uintptr_t size);

// Return the given block memory back to the free list
void freemem(void* p);

// Store the statics information of the memory manager
void get_mem_stats(uintptr_t* total_size, uintptr_t* total_free,
                   uintptr_t* n_free_blocks);

// Prints the free blocks in a formatted listing to a give file
void print_heap();
#endif
