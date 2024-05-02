#include "BC.h"
#include "MT.h"
#include "SC.h"
#include <stdio.h>
#include <unistd.h>

char translate (int value);

void
delline (void)
{
  for (int i = 0; i < 65; i++)
    write (1, " ", 1);
}

void
printCache (void)
{
  int str = 19, col = 1, count = 5, value = 0, shift = 11;
  char address[5] = { ' ', ' ', ':', ' ', ' ' };
  char buf[4] = { ' ', ' ', ' ', ' ' };
  mt_gotoXY (str, col);
  bc_box (str, col, 5, 65, 7, 9, "PROCESSOR CACHE", 2, 7);
  str++;
  col++;
  mt_gotoXY (str, col);
  for (int i = 0; i < 13; i++)
    {
      if (sc_cacheValidate (i) == 0)
        {
          int k = i * 10;
          sprintf (address, "%d", i * 10);
          if (k == 0)
            {
              address[1] = ':';
              address[2] = address[3] = ' ';
            }
          else if (k < 100)
            {
              address[2] = ':';
              address[3] = ' ';
            }
          else
            address[3] = ':';
          address[4] = ' ';
          write (1, address, 5);
          for (int j = 0; j < 10; j++)
            {
              shift = 11;
              sc_cacheGet (k + j, &value, 1);
              if (value >> 14)
                {
                  value = value & 0x3FFF;
                  write (1, "-", 1);
                }
              else
                write (1, "+", 1);
              int f = 0;
              for (int g = 0; g < 4; g++)
                {
                  if (g % 2 == 0)
                    {
                      f = (value >> shift) & 0x7;
                      shift -= 4;
                    }
                  else
                    {
                      f = (value >> shift) & 0xF;
                      shift -= 3;
                    }
                  buf[g] = translate (f);
                }
              write (1, buf, 4);
              write (1, " ", 1);
            }
          count--;
          str++;
          col = 2;
          mt_gotoXY (str, col);
        }
    }

  if (count != 0)
    {
      for (int i = 0; i < count; i++)
        {
          delline ();
          mt_gotoXY (str, col);
          write (1, "-1:", 3);
          str++;
          col = 2;
          mt_gotoXY (str, col);
        }
    }
}