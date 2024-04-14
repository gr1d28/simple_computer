#include "MT.h"
#include "SC.h"
#include <stdio.h>
#include <unistd.h>

char translate (int value);

void
printCell (int address, color fg, color bg)
{
  int size = 5, value = 0, str_size = 10, k, shift = 11;
  char buf[4];
  if (address < 0 || address >= 128)
    printf ("Выход за границы\n");
  else
    {
      k = address % str_size;
      mt_setbgcolor (bg);
      mt_setfgcolor (fg);
      mt_gotoXY ((address / str_size) + 2,
                 ((address % str_size) * size) + k + 2);
      sc_memoryGet (address, &value);
      if (value >> 14)
        {
          value = value & 0x3FFF;
          write (1, "-", 1);
        }
      else
        write (1, "+", 1);

      for (int i = 0; i < 4; i++)
        {
          if (i % 2 == 0)
            {
              k = (value >> shift) & 0x7;
              shift -= 4;
            }
          else
            {
              k = (value >> shift) & 0xF;
              shift -= 3;
            }
          buf[i] = translate (k);
          // int c = (value >> (12 - (i * 4))) & 0xF;
          // buf[i] = translate (c);
        }
      write (1, buf, 4);
      mt_setdefaultcolor ();
    }
}