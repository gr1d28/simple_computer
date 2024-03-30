#include "BC.h"
#include <unistd.h>

int
bc_bigcharread (int fd, int *big, int need_count, int *count)
{
  int size = 4 * sizeof (int) * need_count, x = 0;
  char data[size];
  *count = read (fd, data, size);
  if (*count != size)
    return -1;
  for (int i = 0; i < need_count; i++)
    {
      x = 0;
      for (int j = 0; j < 8; j++)
        {
          x = x << 4;
          x += rev_trans (data[i * 16 + j]);
        }
      big[i * 2] = x;
      x = 0;
      for (int j = 8; j < 16; j++)
        {
          x = x << 4;
          x += rev_trans (data[i * 16 + j]);
        }
      big[i * 2 + 1] = x;
    }
  return 0;
}