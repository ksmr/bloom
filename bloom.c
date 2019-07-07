#include "bloom.h"

BloomFilter BloomFilter_create()
{
  BloomFilter bf;
  memset(bf.data, 0, _BF_SIZE * sizeof(uint64_t));
  return bf;
}

void BloomFilter_add(BloomFilter * bf, const void * key, int len)
{
  uint32_t out[4];
  for(uint n = 0; n < _BF_HASH_NUMBER / 4; ++n) {
      MurmurHash3_x64_128(key, len, n, &out);
      for(uint k = 0; k < 4 && 4*n+k < _BF_HASH_NUMBER; ++k) {
	int h = out[k] % (CHAR_BIT * sizeof(uint64_t) * _BF_SIZE);
	int i = h / (CHAR_BIT * sizeof(uint64_t));
	int j = h % (CHAR_BIT * sizeof(uint64_t));
	bf->data[i] |= (uint64_t) 1 << j;
      }
  }
}

int BloomFilter_query(BloomFilter * bf, const void * key, int len)
{
  uint32_t out[4];
  for(uint n = 0; n < _BF_HASH_NUMBER; ++n) {
    MurmurHash3_x64_128(key, len, n, out);
    for(uint k = 0; k < 4 && 4*n+k < _BF_HASH_NUMBER; ++k) {
      int h = out[k] % (CHAR_BIT * sizeof(uint64_t) * _BF_SIZE);
      int i = h / (CHAR_BIT * sizeof(uint64_t));
      int j = h % (CHAR_BIT * sizeof(uint64_t));
      if(!(bf->data[i] & ((uint64_t) 1 << j)))
	return 0;
    }
  }
  return 1;
}
