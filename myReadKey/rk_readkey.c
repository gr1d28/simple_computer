#include "MR.h"
#include <string.h>
#include <unistd.h>

int
rk_readkey (keys *k)
{
  char *l = "l\0", *s = "s\0", *i = "i\0", *r = "r\0", *t = "t\0",
       *enter = "\n\0";
  char *ESC = "\E\0", *F5 = "\E[15~\0", *F6 = "\E[17~\0";
  char *UP = "\E[A\0", *DOWN = "\E[B\0", *RIGHT = "\E[C\0", *LEFT = "\E[D\0";
  char buf[6];
  int size = 0;

  size = read (1, buf, 6);
  if (!size)
    return -1;
  buf[size] = '\0';
  if (size == 1)
    {
      if (!strcmp (enter, buf))
        {
          *k = ENTER;
          return 0;
        }
      if (!strcmp (l, buf))
        {
          *k = 0;
          return 0;
        }
      if (!strcmp (s, buf))
        {
          *k = 1;
          return 0;
        }
      if (!strcmp (i, buf))
        {
          *k = 2;
          return 0;
        }
      if (!strcmp (r, buf))
        {
          *k = 3;
          return 0;
        }
      if (!strcmp (t, buf))
        {
          *k = 4;
          return 0;
        }
      if (!strcmp (ESC, buf))
        {
          *k = 5;
          return 0;
        }
      if (!strcmp ("-\0", buf))
        {
          *k = 12;
          return 0;
        }
      if (!strcmp ("+\0", buf))
        {
          *k = 13;
          return 0;
        }
      if (buf[0] >= 48 && buf[0] < 58)
        {
          *k = buf[0];
          return 0;
        }
      if (buf[0] >= 65 && buf[0] < 91)
        {
          *k = buf[0];
          return 0;
        }
      if (buf[0] >= 97 && buf[0] < 123)
        {
          *k = buf[0];
          return 0;
        }
    }
  else if (size == 3)
    {
      if (!strcmp (UP, buf))
        {
          *k = 8;
          return 0;
        }
      if (!strcmp (DOWN, buf))
        {
          *k = 9;
          return 0;
        }
      if (!strcmp (RIGHT, buf))
        {
          *k = 10;
          return 0;
        }
      if (!strcmp (LEFT, buf))
        {
          *k = 11;
          return 0;
        }
    }
  else
    {
      if (!strcmp (F5, buf))
        {
          *k = 6;
          return 0;
        }
      if (!strcmp (F6, buf))
        {
          *k = 7;
          return 0;
        }
    }
  return -1;
}