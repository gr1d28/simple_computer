#include <unistd.h>

int
mt_setcursorvisible (int value)
{
  if (value)
    {
      if (write (1, "\E[?25h\E[?8c", 11) < 11)
        return -1;
    }
  else
    {
      if (write (1, "\E[?25l\E[?1c", 11) < 11)
        return -1;
    }
  return 0;
}