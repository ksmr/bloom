CFLAGS = -O3 -march=native -Wall -Wextra -Wpedantic

.PHONY: all clean

tests: tests.c bloom murmur3
	$(CC) $(CFLAGS) -o tests tests.c bloom.o murmur3.o
	./tests

bloom: bloom.c bloom.h
	$(CC) $(CFLAGS) -c bloom.c

murmur3: murmur3.c murmur3.h
	$(CC) $(CFLAGS) -Wno-implicit-fallthrough -c murmur3.c 

clean:
	rm -rf *.o *.so
	rm -rf tests
