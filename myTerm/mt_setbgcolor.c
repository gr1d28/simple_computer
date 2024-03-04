#include "MT.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int
mt_setbgcolor (color cl)
{
  int c = 5;
  char *buf = malloc (sizeof (char) * c);
  sprintf (buf, "\E[4%dm", cl);
  if (write (1, buf, c) < c)
    {
      free (buf);
      return -1;
    }
  free (buf);
  return 0;
}