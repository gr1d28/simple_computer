#include <stdio.h>

void
printDecodedCommand (int value)
{
  int res = 0;
  int k = value;
  int i = 0;
  printf ("bin: ");
  while (k != 0)
    {
      res = res + (k & 0x1);
      res = res << 1;
      k = k >> 1;
      i++;
    }
  res = res >> 1;
  while (i > 0)
    {
      printf ("%d", res & 0x1);
      res = res >> 1;
      i--;
    }
  printf ("\toct: %o\tdec: %d\thex: %x\n", value, value, value);
}