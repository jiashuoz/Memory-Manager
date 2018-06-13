/**
 * CSE374 Winter 2017
 * Homework 6 Memory Management
 * Josh(Jiashuo) Zhang 1365330
 * Ethan(Chiho) Kim 
 * Feb 20, 2017
 * Implementation of function check_heap and other utility functions
 * needed for the memory manager.
 * See comment for each specific function in details.
 */
#include <stdint.h>
#include <assert.h>
#include <stdio.h>
#include "mem_impl.h"

// Check for possible problems with the free list. Make sure the free list
// has the correct properties. Return silently if no errors.
void check_heap() {
    FreeBlock* temp = freeList;
    uintptr_t prevAddr = 0;
    if (!temp) return;
    // Check the blocks except the first one if there exists any
    while (temp->next) {
        // Check addresses in ascending order
        assert(prevAddr < (uintptr_t)temp);
        // Check sizes greater than threshold value
        assert(temp->size >= TH);
        // Check blocks do not overlap or touch each other
        assert(((uintptr_t)temp + temp->size) < (uintptr_t)temp->next);
        // Check the blocks aligned by a multiple of 16
        assert((uintptr_t)temp % 16 == 0);
        // Check the block size aligned by a multiple of 16
        assert(temp->size % 16 == 0);

        // Previous block's address
        prevAddr = (uintptr_t)temp;
        temp = temp->next;
    }
    // Check the last block or this is the only block existing
    assert(temp->size >= TH);
    assert(temp->size % 16 == 0);
    assert((uintptr_t)temp % 16 == 0);
    assert((uintptr_t)temp->next == 0);
}
