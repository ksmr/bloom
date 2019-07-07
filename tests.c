#include <stdio.h>

#include "bloom.h"

#define TEST(p) do{\
  if(!p)\
    printf("Test failed at line %u of file %s.\n", __LINE__, __FILE__);\
  else\
    printf("Test passed at line %u of file %s.\n", __LINE__, __FILE__);\
  }while(0)

void BloomFilter_print_bytes(BloomFilter * bf)
{
  char * data = (char *) bf->data;
  for(uint i = 0; i < sizeof(uint64_t) * _BF_SIZE; ++i)
    {
      printf("%hhx ", data[i]);
    }
  printf("\n");
}

double BloomFilter_load_factor(BloomFilter * bf)
{
  int n = 0;
  for(uint i = 0; i < (sizeof(uint64_t)/sizeof(unsigned int)) * _BF_SIZE; ++i)
    {
      int m = __builtin_popcount(((unsigned int*)(bf->data))[i]);
      n += m;
    }

  return (double) n / (double) (CHAR_BIT * sizeof(uint64_t) * _BF_SIZE);
}

int main(void)
{
  BloomFilter bf = BloomFilter_create();

  TEST(BloomFilter_query(&bf, "AA", 2) == 0);
  BloomFilter_add(&bf, "AA", 2);
  TEST(BloomFilter_query(&bf, "AA", 2) != 0);

  return 0;
}
