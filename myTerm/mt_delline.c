#include <unistd.h>

int
mt_delline (void)
{
  if (write (1, "\E[M", 3) < 3)
    return -1;
  return 0;
}