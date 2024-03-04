#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int
mt_gotoXY (int str, int col)
{
  int setcrs = 12;
  char *buf = malloc (sizeof (char) * setcrs);
  sprintf (buf, "\E[%d;%dH", str, col);
  if (write (1, buf, setcrs) < setcrs)
    {
      free (buf);
      return -1;
    }
  free (buf);
  return 0;
}