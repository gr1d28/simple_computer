#include "BC.h"
#include <unistd.h>
#define MASK 0xf

int
bc_bigcharwrite (int fd, int *big, int count)
{
  int size = 4 * sizeof (int), x = 0;
  char data[size];
  for (int i = 0; i < count; i++)
    {
      x = big[i * 2];
      for (int j = size / 2 - 1; j >= 0; j--)
        {
          data[j] = trans (x & MASK);
          x = x >> 4;
        }
      x = big[i * 2 + 1];
      for (int j = size - 1; j >= size / 2; j--)
        {
          data[j] = trans (x & MASK);
          x = x >> 4;
        }
      if (write (fd, data, size) != size)
        return -1;
    }
  return 0;
}