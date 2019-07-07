#ifndef _BLOOM_H_
#define _BLOOM_H_

#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include <stddef.h>
#include <limits.h>

#include "murmur3.h"

/* Size of the Bloom filter */
#define _BF_SIZE 4096
/* Number of hashes used to add/query elements in the filter */
#define _BF_HASH_NUMBER 12

typedef struct {
  uint64_t data[_BF_SIZE];
} BloomFilter;

/* Create a new, empty Bloom filter */
BloomFilter BloomFilter_create();

/* Add `key` of length `len` into the Bloom filter `bf` */
void BloomFilter_add(BloomFilter * bf, const void * key, int len);

/* Query if `key` of length `len` is in the Bloom filter `bf` */
/* Returns 0 is false, 1 if true */
int BloomFilter_query(BloomFilter * bf, const void * key, int len);

#endif // _BLOOM_H_
