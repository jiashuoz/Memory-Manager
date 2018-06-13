/**
 * CSE374 Winter 2017
 * Homework 6 Memory Management
 * Josh(Jiashuo) Zhang 1365330
 * Ethan(Chihio) Kim 0963203 
 * Feb 20, 2017
 * Header file for internal functions for memory manager.
 * The functions included in this file are not public functions 
 * for clients to use.
 */

#ifndef MEM_IMPL_H
#define MEM_IMPL_H

#define HEADER_SIZE 16  // Header size
#define REQ_SIZE 8000  // Default request size from operating system
#define TH 128  // Threshold of remainder block in free list

// Keep track of amount of bytes acquired from operating system
uintptr_t totalSize;

// The free list data structure.
// Each block contains information: size of the block and pointer to
// the next block. The size is the total size of the payload and
// the header(16 bytes)).
typedef struct FreeList {
    uintptr_t size;
    struct FreeList* next;
} FreeBlock;

// The head of free list, null if empty
FreeBlock* freeList;

// Check errors for free list structure
void check_heap();

#endif
