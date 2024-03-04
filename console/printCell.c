#include "MT.h"
#include "SC.h"
#include <stdio.h>
#include <unistd.h>

char translate (int value);

void
printCell (int address, color fg, color bg)
{
  int size = 5, value = 0, str_size = 10, k;
  char buf[4];
  if (address < 0 || address >= 128)
    printf ("Выход за границы\n");
  else
    {
      k = address % str_size;
      if (k >= 1)
        k++;
      mt_setbgcolor (bg);
      mt_setfgcolor (fg);
      mt_gotoXY ((address / str_size) + 1, ((address % str_size) * size) + k);
      sc_memoryGet (address, &value);
      write (1, "+", 1);
      for (int i = 0; i < 4; i++)
        {
          int k = (value >> (12 - (i * 4))) & 0xF;
          buf[i] = translate (k);
        }
      write (1, buf, 4);
      mt_setdefaultcolor ();
    }
}