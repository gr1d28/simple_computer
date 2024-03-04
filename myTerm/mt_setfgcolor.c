#include "MT.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int
mt_setfgcolor (color cl)
{
  int c = 5;
  char *buf = malloc (sizeof (char) * c);
  sprintf (buf, "\E[3%dm", cl);
  if (write (1, buf, c) < c)
    {
      free (buf);
      return -1;
    }
  free (buf);
  return 0;
}