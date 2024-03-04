#include <unistd.h>

int
mt_setdefaultcolor (void)
{
  if ((write (1, "\E[37m", 5)) < 5 || (write (1, "\E[49m", 5)) < 5)
    return -1;
  return 0;
}