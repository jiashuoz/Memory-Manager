/**
 * CSE374 Winter 2017
 * Homework 6 Memory Management
 * Josh(Jiashuo) Zhang 1365330
 * Ethan(Chiho) Kim 0963203 
 * Feb 20, 2017
 * Implementation of function getmem
 * The program returns a pointer to a block of memory with at least size of user
 * request. User needs to give appropriate size for it to properly function. The memory
 * blocks allocated by this program are 16-byte aligned in address boundary.
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "mem_impl.h"

// Function prototypes
FreeBlock* create(FreeBlock* block, uintptr_t size);
FreeBlock* split(FreeBlock* block, uintptr_t size);

// Return pointer to a memory block with at least size of given parameter
void* getmem(uintptr_t size) {
    check_heap();
    if (size <= 0) {
        return NULL;
    }

    uintptr_t returnAddress = 0;

    // Make sure multiple of 16 in size including the header
    uintptr_t realSize = size + HEADER_SIZE;
    uintptr_t alignSize = realSize % 16 ? (1 + realSize / 16) * 16 : realSize;

    alignSize = alignSize < TH ? TH : alignSize;

    FreeBlock* current = NULL;
    if (!freeList) {
        if (alignSize > REQ_SIZE) {  // Default size not big enough
        current = create(current, alignSize);  // Get larger chunk from OS
        } else {
         current = create(current, REQ_SIZE);  // Get 8K bytes memory from OS
        freeList = split(current, alignSize);   // Split block if necessary
        }
    } else {
        current = freeList;
        // The first block in list is big enough
        if (freeList->size >= alignSize) {
            freeList = split(freeList, alignSize);
            goto END;
        }
        // Loop through free list to find block
        while (current->next != NULL) {
            if (current->next->size >= alignSize) {
                break;
            }
            current = current->next;
        }
        // Fail to find a block big enough, need a new block
        if (!current->next) {
            // Default size not big enough, request a larger chunk
            if (alignSize > REQ_SIZE) {
                current = create(current, alignSize);
                // Default size big enough, split as needed
            } else {
                current = create(current, REQ_SIZE);
                FreeBlock* remainder = split(current, alignSize);
                // Did not split
                if (!remainder) {
                    goto END;
                }
                // Insert the remainder block to the front
                if (remainder < freeList || !freeList) {
                remainder->next = freeList;
                freeList = remainder;
                // Insert the remainder block to the right position
                } else {
                FreeBlock* temp = freeList;
                // Look for correct position to insert
                while (temp->next && remainder > temp->next) {
                    temp = temp->next;
                }
                // Insert
                remainder->next = temp->next;
                temp->next = remainder;
                }
            }
        } else {  // Found a good size block in free list
          FreeBlock* temp = current->next;
          current->next = split(current->next, alignSize);
          current = temp;
        }
    }
    END:
    returnAddress = ((uintptr_t)current + HEADER_SIZE);
    check_heap();
    return (void*)returnAddress;
}

// Create new block, update pointers
FreeBlock* create(FreeBlock* block, uintptr_t size) {
    block = (FreeBlock*)malloc(size);
    if (!block) {
        printf("Error: Unable to allocate memory.\n");
        exit(1);
    }
    block->size = size;
    block->next = NULL;
    totalSize += size;
    return block;
}

// Split the block as needed
FreeBlock* split(FreeBlock* block, uintptr_t size) {
  // Remaining block greater than threshold
  if (block->size - size >= TH) {
    FreeBlock* current = block;
    // Set header for remaining block
    block = (FreeBlock*)((uintptr_t)current + size);
    block->size = current->size - size;
    block->next = current->next;
    // Set current block ready for client
    current->size = size;
    current->next = NULL;
    return block;
  }
  return block->next;
}
