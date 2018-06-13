# CSE 374 17wi HW5
# Josh(Jiashuo) Zhang 1365330
# Ethan(Chiho) Kim 0963203
# March 3, 2017
# Makefile for memory manager

CC = gcc -Wall -g -std=c11
MEMO = getmem.o freemem.o get_mem_stats.o print_heap.o mem_utils.o
MEMO2 = getmem.o freemem.o get_mem_stats.o print_heap.o mem_utils_n.o

# Produce the executable file
bench: bench.o $(MEMO)
	$(CC) -o bench bench.c $(MEMO)

# Default test
test: bench.o $(MEMO)
	./bench

# Disable asserts
noAssert: bench.o $(MEMO2)
	$(CC) -DNDEBUG -o bench bench.c $(MEMO2)

# Simple testing
smallTest: bench.o $(MEMO)
	./bench 50 50 10 200 20000 0

# Large test to measure CPU time
largeTest: bench.o $(MEMO)
	./bench 2000000 50 10 200 20000 0

# Small test for 100% getmem
pctget100: bench.o $(MEMO)
	./bench 50 100 10 200 20000 0

# Small test for 100% large block > 8000
pctlarge: bench.o $(MEMO)
	./bench 50 50 100 8000 20000 0

bench.o: bench.c mem.h
	$(CC) -c bench.c

getmem.o: getmem.c mem.h mem_impl.h
	$(CC) -c getmem.c

freemem.o: freemem.c mem.h mem_impl.h
	$(CC) -c freemem.c

get_mem_stats.o: get_mem_stats.c mem.h
	$(CC) -c get_mem_stats.c

print_heap.o: print_heap.c mem.h
	$(CC) -c print_heap.c

mem_utils.o: mem_utils.c mem_impl.h
	$(CC) -c mem_utils.c

mem_utils_n.o: mem_utils.c mem_impl.h
	$(CC) -DNDEBUG -o mem_utils_n.o -c mem_utils.c

clean:
	rm -f *.o bench *~