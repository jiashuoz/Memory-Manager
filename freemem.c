/**
 * CSE374 Winter 2017
 * Homework 6 Memory Management
 * Josh(Jiashuo) Zhang 1365330
 * Ethan(Chiho) Kim 0963203 
 * Feb 20, 2017
 * Implementation of function freemem
 * This program returns the given block of memory back to the pool of available
 * memory storage(freelist). The user should to give valid pointer for it functions 
 * properly. It checks for NULL pointer but not other cases. The operation is
 * undefined if the pointer given is invalid.
 */

#include <stdint.h>
#include <stdio.h>

#include "mem_impl.h"

// Return the given block memory back to the free list
void freemem(void* p) {
    check_heap();
    if (!p) {
        goto END;
    }

    FreeBlock* pHead = (FreeBlock*)((uintptr_t)p - HEADER_SIZE);
    FreeBlock* temp = freeList;
    uintptr_t endAddress = (uintptr_t)pHead + pHead->size;

    // FreeList null, insert it anyways
    if (!freeList) {
        freeList = pHead;
        freeList->next = temp;
        goto END;
    }

    // Merge with preceding and following blocks
    if ((uintptr_t)pHead == ((uintptr_t)freeList + freeList->size)
              && freeList->next && endAddress == (uintptr_t)freeList->next) {
        freeList->size = freeList->size + pHead->size + freeList->next->size;
        freeList->next = freeList->next->next;
        goto END;
    // Merge with following block
    } else if (endAddress == (uintptr_t)freeList) {
        freeList = pHead;
        freeList->size = freeList->size + temp->size;
        freeList->next = temp->next;
        goto END;
    // Merge with preceding block
    } else if ((uintptr_t)pHead == ((uintptr_t)freeList + freeList->size)) {
        freeList->size = freeList->size + pHead->size;
        goto END;
    // Add to the very beginning
    } else if (pHead < freeList) {
        pHead->next = freeList;
        freeList = pHead;
        goto END;
    }

    // Find the correct position to insert block
    while (temp->next) {
        uintptr_t prevEnd = (uintptr_t)temp->next + temp->next->size;

        // Merge with preceding and following block
        if ((uintptr_t)pHead == prevEnd && endAddress ==
                             (uintptr_t)temp->next->next) {
            temp->next->size = temp->next->size + pHead->size +
                               temp->next->next->size;
            temp->next->next = temp->next->next->next;
            goto END;
        // Merge with preceding block
        } else if ((uintptr_t)pHead == prevEnd) {
            temp->next->size = temp->next->size + pHead->size;
            goto END;
        // Merge with following block
        } else if (endAddress == (uintptr_t)temp->next) {
            pHead->next = temp->next->next;
            pHead->size = pHead->size + temp->next->size;
            temp->next = pHead;
            goto END;
        // Current address too big, continue searching
        // Current block needs to be inserted here, stop searching
        } else if (pHead < temp->next) {
            break;
        }
        temp = temp->next;
    }
    // Simply insert it, no merge
    pHead->next = temp->next;
    temp->next = pHead;

    END:
    check_heap();
}
