/**
 * CSE374 Winter 2017
 * Homework 6 Memory Management
 * Josh(Jiashuo) Zhang 1365330
 * Ethan(Chiho) Kim 0963203 
 * Feb 20, 2017
 * Bench program for testing
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

#include "mem.h"

// Default testing parameters
#define NTRIALS 1000
#define PCTGET 50
#define PCTLARGE 10
#define SMALL 200
#define LARGE 20000

int main(int argc, char** argv) {
    // Total amount of memory acquired
    uintptr_t totalSize, totalFree, nFreeBlocks;

    // For CPU time measure;
    time_t start, end;
    double cpu_time_used;

    // ntrials, pctget, pctlarge, small_limit, large_limit, random_seed
    uintptr_t testControl[] = {0, NTRIALS, PCTGET, PCTLARGE, SMALL, LARGE,
                               time(NULL)};

    // Update default values based on user input
    for (int i = 1; i < argc; i++) {
        testControl[i] = atoi(argv[i]);
    }

    // Create local variables for easy reading purpose
    int ntrials = testControl[1];
    int pctget = testControl[2];
    int pctlarge = testControl[3];
    int smallLimit = testControl[4];
    int largeLimit = testControl[5];
    int randomSeed = testControl[6];

    // Initialize random number generator
    srand(randomSeed);

    // Client pointers
    uintptr_t* blockInUse = (uintptr_t*)malloc(ntrials * sizeof(uintptr_t));

    if (!blockInUse) {
        printf("Error: Unable to allocate memory.\n");
        exit(1);
    }
    
    // Client tracker
    int clientIndex = 0;

    // For properly 10%-step printing purpose
    int ntrials_round = ntrials / 10 * 10;
    int printInformation = ntrials_round / 10;

    start = clock();

    printf("CPU_T  Total_Size  Blocks_Num       Avg_Size\n");
    for (int i = 1; i <= ntrials; i++) {
        // Do getmem
        if ((rand() % 100) < pctget) {
            // Get a large block based on pctlarge
            if (rand() % 100 < pctlarge) {
                blockInUse[clientIndex] = (uintptr_t)getmem(rand() %
                                                     largeLimit + 1);
                clientIndex++;
            // Get a small block
            } else {
                uintptr_t bytes = rand() % smallLimit + 1;
                blockInUse[clientIndex] = (uintptr_t)getmem(bytes);
                clientIndex++;
            }
        // Do freemem
        } else {
            // Only do freemem when there's unfreed block
            if (clientIndex > 0) {
                int index = rand() % clientIndex;
                freemem((void*)blockInUse[index]);
                blockInUse[index] = blockInUse[clientIndex - 1];
                clientIndex--;
            }
        }

        // Print stats to stdout
        if (ntrials > 10 && i % printInformation == 0 && i <= ntrials_round) {
            end = clock();
            cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
            get_mem_stats(&totalSize, &totalFree, &nFreeBlocks);
            printf("%6.3f %10lu %11lu %14.2f\n",
                cpu_time_used, totalSize, nFreeBlocks,
                    (float)totalFree/nFreeBlocks);
        } else if (ntrials <= 10) {
            end = clock();
            cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
            get_mem_stats(&totalSize, &totalFree, &nFreeBlocks);
            printf("%6.3f %10lu %11lu %14.2f\n",
                cpu_time_used, totalSize, nFreeBlocks,
                    (float)totalFree/nFreeBlocks);
        }
    }
    return 0;
}
